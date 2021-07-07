
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) extension::AnyImport::s_Mutex = nullptr;
MP_PTR(MP_VECTOR(extension::AnyImport::Item)) extension::AnyImport::s_Items = nullptr;
MP_PTR(MP_VECTOR(extension::AnyImport::Item)) extension::AnyImport::s_Pipes = nullptr;
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
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
                    __SendRequest(a_Context->m_Name, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_TERMINATE_REQUEST);
                }
            }
        }
        if ((s_Pipes != nullptr) && (MP_VECTOR_EMPTY(s_Pipes) == false))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Pipes);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context = MP_VECTOR_GET(s_Pipes, 0);
                {
                    MP_PIPE_CLIENT_FINALIZE(a_Context->m_Pipe);
                }
                {
                    MP_VECTOR_DELETE(s_Pipes, 0);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
                MP_THREAD_START(a_Context->m_Thread, a_Context);
            }
            {
                MP_VECTOR_APPEND(s_Items, a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
    }
}

void extension::AnyImport::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            __SendRequest("IMPORT." + extension::AnyPreview::GetExtension(url), url);
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

bool extension::AnyImport::Send(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        try
        {
            MP_PIPE_CLIENT a_Context;
            if (s_Pipes == nullptr)
            {
                s_Pipes = MP_NEW MP_VECTOR(Item)();
            }
            {
                auto a_Name = extension::AnyPreview::GetPipeName("");
                if (MP_STRING_EMPTY(a_Name))
                {
                    return false;
                }
                {
                    auto a_Size = MP_VECTOR_SIZE_GET(s_Pipes);
                    for (auto i = 0; i < a_Size; i++)
                    {
                        if (s_Pipes[i]->m_Name == a_Name)
                        {
                            a_Context = s_Pipes[i]->m_Pipe;
                        }
                    }
                }
                if (a_Context == nullptr)
                {
                    auto a_Context1 = MP_NEW Item();
                    {
                        MP_PIPE_CLIENT_INITIALIZE(a_Context, a_Name, MP_PIPE_DIRECTION_OUT);
                    }
                    {
                        a_Context1->m_Name = a_Name;
                        a_Context1->m_Pipe = a_Context;
                    }
                    {
                        MP_VECTOR_APPEND(s_Pipes, a_Context1);
                    }
                }
            }
            for (auto i = 1; i <= extension::AnyPreview::CONSTANT::OUTPUT_PIPE_CONNECT_COUNT; i++)
            {
                try
                {
                    if (MP_PIPE_CLIENT_CONNECTED(a_Context))
                    {
                        break;
                    }
                    else
                    {
                        MP_PIPE_CLIENT_CONNECT(a_Context, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_TIMEOUT);
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    if (i == extension::AnyPreview::CONSTANT::OUTPUT_PIPE_CONNECT_COUNT)
                    {
                        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
                    }
                }
            }
            if (MP_PIPE_CLIENT_CONNECTED(a_Context))
            {
                MP_PIPE_BUFFER a_Context1;
                {
                    MP_PIPE_BUFFER_INITIALIZE(a_Context1, 0);
                    MP_PIPE_BUFFER_UTF8_SET(a_Context1, value);
                    MP_PIPE_CLIENT_SEND(a_Context, a_Context1, 0, MP_PIPE_BUFFER_SIZE_GET(a_Context1));
                    MP_PIPE_BUFFER_FINALIZE(a_Context1);
                }
                {
                    return true;
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
        }
        {
            MP_TRACE_DEBUG(value);
        }
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
MP_PTR(MP_THREAD_MUTEX) extension::AnyImport::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, extension::AnyPreview::CONSTANT::OUTPUT_EXECUTE_MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
bool extension::AnyImport::__SendRequest(MP_STRING name, MP_STRING value)
{
    auto a_Result = false;
    if (MP_STRING_EMPTY(name) == false)
    {
        try
        {
            MP_PIPE_CLIENT a_Context;
            {
                MP_PIPE_CLIENT_INITIALIZE(a_Context, extension::AnyPreview::GetPipeName(name), MP_PIPE_DIRECTION_OUT);
                MP_PIPE_CLIENT_CONNECT(a_Context, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_TIMEOUT);
            }
            if (MP_PIPE_CLIENT_CONNECTED(a_Context))
            {
                MP_PIPE_BUFFER a_Context1;
                {
                    MP_PIPE_BUFFER_INITIALIZE(a_Context1, 0);
                    MP_PIPE_BUFFER_UTF8_SET(a_Context1, value);
                    MP_PIPE_CLIENT_SEND(a_Context, a_Context1, 0, MP_PIPE_BUFFER_SIZE_GET(a_Context1));
                    MP_PIPE_BUFFER_FINALIZE(a_Context1);
                }
                {
                    a_Result = true;
                }
            }
            {
                MP_PIPE_CLIENT_FINALIZE(a_Context);
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_UNUSED(ex);
            a_Result = false;
        }
    }
    return a_Result;
}

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
    if (a_Context != nullptr)
    {
        while (a_Context->m_Context != nullptr)
        {
            try
            {
                MP_PIPE_SERVER a_Context1;
                {
                    MP_PIPE_SERVER_INITIALIZE(a_Context1, extension::AnyPreview::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 16);
                    MP_PIPE_SERVER_WAIT(a_Context1);
                }
                while (MP_PIPE_SERVER_CONNECTED(a_Context1))
                {
                    try
                    {
                        MP_PIPE_BUFFER a_Context2;
                        auto a_Size = 0;
                        {
                            MP_PIPE_BUFFER_INITIALIZE(a_Context2, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_BUFFER_SIZE + 1);
                        }
                        {
                            a_Size = MP_PIPE_SERVER_RECEIVE(a_Context1, a_Context2, 0, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_BUFFER_SIZE);
                        }
                        if (a_Size > 0)
                        {
                            {
                                SetState(NAME::STATE::CANCEL);
                            }
                            {
                                a_Context2[a_Size] = 0;
                            }
                            {
                                auto a_Context3 = MP_PIPE_BUFFER_UTF8_GET(a_Context2, 0, a_Size);
                                if (a_Context3 == extension::AnyPreview::CONSTANT::OUTPUT_PIPE_TERMINATE_REQUEST)
                                {
                                    {
                                        a_Context->m_Context = nullptr;
                                    }
                                    {
                                        MP_PIPE_BUFFER_FINALIZE(a_Context2);
                                    }
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
                                    {
                                        MP_THREAD_MUTEX_UNLOCK(__GetMutex());
                                    }
                                    {
                                        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
                                    }
                                }
                            }
                        }
                        {
                            MP_PIPE_BUFFER_FINALIZE(a_Context2);
                        }
                    }
                    catch (MP_PTR(MP_EXCEPTION) ex)
                    {
                        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
                    }
                }
                {
                    MP_PIPE_SERVER_FINALIZE(a_Context1);
                }
            }
            catch (MP_PTR(MP_EXCEPTION) ex)
            {
                MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
            }
        }
    }
}
