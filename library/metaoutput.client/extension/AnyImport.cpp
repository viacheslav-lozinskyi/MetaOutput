
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) extension::AnyImport::s_Mutex = nullptr;
MP_PTR(MP_VECTOR(extension::AnyImport::Item)) extension::AnyImport::s_Items = nullptr;
#endif

// extension::AnyImport #######################################################
void extension::AnyImport::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(Item);
        }
        {
            SetState(NAME::STATE::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
                    extension::AnyPreview::Send(a_Context->m_Name, atom::Trace::CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
    }
}

void extension::AnyImport::Register(MP_STRING extension, MP_PTR(AnyImport) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            auto a_Context = MP_NEW Item();
            {
                a_Context->m_Name = "IMPORT" + MP_STRING_UPPER(extension::AnyPreview::GetName(extension));
                a_Context->m_Context = MP_NEW atom::Trace();
                a_Context->m_Extension = context;
                a_Context->m_Thread = nullptr;
            }
            {
                MP_THREAD_INITIALIZE(a_Context->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(a_Context->m_Thread, "METAOUTPUT.IMPORT: " + extension);
                MP_THREAD_APARTMENT_SET(a_Context->m_Thread, MP_THREAD_APARTMENT_STA);
                MP_THREAD_START(a_Context->m_Thread, a_Context);
            }
            {
                MP_VECTOR_APPEND(s_Items, a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
    }
}

void extension::AnyImport::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            extension::AnyPreview::Send("IMPORT." + extension::AnyPreview::GetExtension(url), url);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetUrl(url)->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::TYPE::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
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
MP_PTR(MP_THREAD_MUTEX) extension::AnyImport::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, atom::Trace::CONSTANT::OUTPUT::MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
void extension::AnyImport::__Execute(MP_PTR(AnyImport) sender, MP_PTR(atom::Trace) context, MP_STRING url)
{
    try
    {
        {
            SetState(NAME::STATE::EXECUTE);
        }
        {
            sender->_Execute(context, url);
        }
        if (GetState() == NAME::STATE::CANCEL)
        {
            context->
                Clear()->
                SetUrl(url)->
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::TYPE::WARNING, 0, "[[[Execution is terminated]]]...");
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
                Send(NAME::SOURCE::DIAGNOSTIC, NAME::TYPE::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
        }
    }
}

// Private #############
void extension::AnyImport::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(Item)>(sender);
    while (a_Context != nullptr)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            {
                MP_PIPE_SERVER_INITIALIZE(a_Context1, extension::AnyPreview::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
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
                            if (a_Context3 == atom::Trace::CONSTANT::PIPE::TERMINATE_REQUEST)
                            {
                                a_Context = nullptr;
                                break;
                            }
                            try
                            {
                                {
                                    MP_THREAD_MUTEX_LOCK(__GetMutex());
                                }
                                {
                                    __Execute(a_Context->m_Extension, a_Context->m_Context, a_Context3);
                                }
                                {
                                    MP_THREAD_MUTEX_UNLOCK(__GetMutex());
                                }
                            }
                            catch (MP_PTR(MP_EXCEPTION) ex)
                            {
                                MP_THREAD_MUTEX_UNLOCK(__GetMutex());
                                MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
                            }
                        }
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
        }
    }
}
