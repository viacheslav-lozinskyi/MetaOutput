
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnyImport)) extension::AnyImport::s_Items = nullptr;
#endif

// extension::AnyImport #######################################################
void extension::AnyImport::Connect(MP_STRING application, MP_STRING extension)
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyImport);
        }
        {
            extension::AnyPipe::Validate(application, extension);
        }
        {
            SetState(NAME::STATE::WORK::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyImport::Disconnect()
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
                    extension::AnyPipe::Execute(a_Context->m_Name, CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnyImport::Register(MP_STRING extension, MP_PTR(AnyImport) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            {
                context->m_Name = "urn:metaoutput:import:" + MP_STRING_LOWER(extension);
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

bool extension::AnyImport::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::WORK::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            auto a_Name = "urn:metaoutput:import:" + MP_STRING_LOWER(extension::AnyPreview::GetExtension(url));
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == a_Name)
                {
                    extension::AnyPipe::Execute(a_Name, url);
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
MP_STRING extension::AnyImport::GetState()
{
    return extension::AnyPreview::GetState();
}

void extension::AnyImport::SetState(MP_STRING value)
{
    extension::AnyPreview::SetState(value);
}

// Protected ###########
void extension::AnyImport::_Execute(MP_PTR(atom::Trace), MP_STRING)
{
}

// Private #############
void extension::AnyImport::__Execute(MP_PTR(AnyImport) sender, MP_PTR(atom::Trace) trace, MP_STRING url)
{
    try
    {
        {
            SetState(NAME::STATE::WORK::EXECUTE);
        }
        if (sender != nullptr)
        {
            sender->_Execute(trace, url);
        }
        if (GetState() == NAME::STATE::WORK::CANCEL)
        {
            trace->
                Clear()->
                SetUrl(url)->
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::WARNING, 0, "[[[Execution is terminated]]]...");
        }
        {
            SetState(NAME::STATE::WORK::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        {
            SetState(NAME::STATE::WORK::WAIT);
        }
        {
            trace->
                Clear()->
                SetUrl(url)->
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
        }
    }
}

// Private #############
void extension::AnyImport::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyImport)>(sender);
    auto a_IsFound = a_Context == nullptr;
    while (a_IsFound == false)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_THREAD_MUTEX))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context3 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            auto a_Context4 = MP_NEW atom::Trace();
            {
                MP_THREAD_MUTEX_INITIALIZE(a_Context1, CONSTANT::OUTPUT::MUTEX, false);
                MP_PIPE_SERVER_INITIALIZE(a_Context2, extension::AnyPipe::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
                MP_PIPE_READSTREAM_INITIALIZE(a_Context3, a_Context2);
            }
            while (a_IsFound == false)
            {
                try
                {
                    {
                        MP_PIPE_SERVER_CONNECT(a_Context2);
                    }
                    if (MP_PIPE_SERVER_CONNECTED(a_Context2))
                    {
                        auto a_Context5 = MP_PIPE_READSTREAM_READ(a_Context3);
                        {
                            MP_PIPE_SERVER_DISCONNECT(a_Context2);
                        }
                        if (a_Context5 == CONSTANT::PIPE::TERMINATE_REQUEST)
                        {
                            a_IsFound = true;
                            break;
                        }
                        try
                        {
                            MP_THREAD_MUTEX_LOCK(a_Context1);
                            {
                                __Execute(a_Context, a_Context4->Clear(), a_Context5);
                            }
                            MP_THREAD_MUTEX_UNLOCK(a_Context1);
                        }
                        catch (MP_PTR(MP_EXCEPTION) ex)
                        {
                            MP_THREAD_MUTEX_UNLOCK(a_Context1);
                            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
                            MP_THREAD_SLEEP(CONSTANT::PIPE::TIMEOUT);
                            break;
                        }
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
                    MP_THREAD_SLEEP(CONSTANT::PIPE::TIMEOUT);
                    break;
                }
            }
            {
                MP_PIPE_READSTREAM_FINALIZE(a_Context3);
                MP_PIPE_SERVER_FINALIZE(a_Context2);
                MP_THREAD_MUTEX_FINALIZE(a_Context1);
            }
            {
                MP_DELETE a_Context4;
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
            break;
        }
    }
}
