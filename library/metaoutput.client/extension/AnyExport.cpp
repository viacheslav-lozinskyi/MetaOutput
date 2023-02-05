
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnyExport)) extension::AnyExport::s_Items = nullptr;
#endif

// extension::AnyExport #######################################################
void extension::AnyExport::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyExport);
        }
        {
            SetState(NAME::STATE::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyExport::Disconnect()
{
    try
    {
        if ((s_Items != nullptr) && (MP_VECTOR_EMPTY(s_Items) == false))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context = MP_VECTOR_GET(s_Items, 0);
                {
                    MP_VECTOR_DELETE(s_Items, 0);
                }
                {
                    extension::AnyPipe::Send(a_Context->m_Name, CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnyExport::Register(MP_STRING extension, MP_PTR(AnyExport) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            {
                context->m_From = "";
                context->m_Name = "urn:metaoutput:export:" + MP_STRING_LOWER(extension);
                context->m_Context = MP_NEW atom::Trace();
                context->m_Thread = nullptr;
            }
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == context->m_Name)
                {
                    return false;
                }
            }
            {
                MP_THREAD_MUTEX_INITIALIZE(context->m_Mutex, CONSTANT::OUTPUT::MUTEX, false);
                MP_THREAD_INITIALIZE(context->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(context->m_Thread, context->m_Name);
                MP_THREAD_APARTMENT_SET(context->m_Thread, MP_THREAD_APARTMENT_STA);
                MP_THREAD_START(context->m_Thread, context);
            }
            {
                MP_VECTOR_APPEND(s_Items, context);
            }
            return true;
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return false;
}

bool extension::AnyExport::Execute(MP_STRING url, MP_STRING from)
{
    try
    {
        if ((GetState() != NAME::STATE::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            auto a_Name = "urn:metaoutput:export:" + MP_STRING_LOWER(extension::AnyPreview::GetExtension(url));
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == a_Name)
                {
                    s_Items[i]->m_From = from;
                    extension::AnyPipe::Send(a_Name, url);
                    return true;
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetUrl(url)->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

// Public ##############
MP_STRING extension::AnyExport::GetState()
{
    return extension::AnyPreview::GetState();
}

void extension::AnyExport::SetState(MP_STRING value)
{
    extension::AnyPreview::SetState(value);
}

// Protected ###########
void extension::AnyExport::_Execute(MP_PTR(atom::Trace), MP_STRING, MP_STRING)
{
}

// Private #############
void extension::AnyExport::__Execute(MP_PTR(AnyExport) sender, MP_PTR(atom::Trace) context, MP_STRING url, MP_STRING from)
{
    try
    {
        {
            SetState(NAME::STATE::EXECUTE);
        }
        {
            sender->_Execute(context, url, from);
        }
        if (GetState() == NAME::STATE::CANCEL)
        {
            context->
                Clear()->
                SetUrl(url)->
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::WARNING, 0, "[[[Execution is terminated]]]...");
        }
        {
            SetState(NAME::STATE::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        {
            SetState(NAME::STATE::WAIT);
        }
        {
            context->
                Clear()->
                SetUrl(url)->
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
        }
    }
}

// Private #############
void extension::AnyExport::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyExport)>(sender);
    while (a_Context != nullptr)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            {
                MP_PIPE_SERVER_INITIALIZE(a_Context1, extension::AnyPipe::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
                MP_PIPE_READSTREAM_INITIALIZE(a_Context2, a_Context1);
            }
            while (a_Context != nullptr)
            {
                try
                {
                    {
                        MP_PIPE_SERVER_CONNECT(a_Context1);
                    }
                    if (MP_PIPE_SERVER_CONNECTED(a_Context1))
                    {
                        {
                            SetState(NAME::STATE::CANCEL);
                        }
                        {
                            auto a_Context3 = MP_PIPE_READSTREAM_READ(a_Context2);
                            {
                                MP_PIPE_SERVER_DISCONNECT(a_Context1);
                            }
                            if (a_Context3 == CONSTANT::PIPE::TERMINATE_REQUEST)
                            {
                                a_Context = nullptr;
                                break;
                            }
                            try
                            {
                                {
                                    MP_THREAD_MUTEX_LOCK(a_Context->m_Mutex);
                                }
                                {
                                    __Execute(a_Context, a_Context->m_Context, a_Context3, a_Context->m_From);
                                }
                                {
                                    MP_THREAD_MUTEX_UNLOCK(a_Context->m_Mutex);
                                }
                            }
                            catch (MP_PTR(MP_EXCEPTION) ex)
                            {
                                MP_THREAD_MUTEX_UNLOCK(a_Context->m_Mutex);
                                MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
                            }
                        }
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
                    break;
                }
            }
            {
                MP_PIPE_READSTREAM_FINALIZE(a_Context2);
                MP_PIPE_SERVER_FINALIZE(a_Context1);
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
        }
    }
}
