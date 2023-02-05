
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnyPipe)) extension::AnyPipe::s_Items = nullptr;
#endif

// extension::AnyPipe ######################################################
void extension::AnyPipe::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyPipe);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyPipe::Disconnect()
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
                    Send(a_Context->m_Name, CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnyPipe::Register(MP_STRING name, MP_PTR(AnyPipe) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            {
                context->m_Name = (MP_STRING_INDEXOF(name, "urn:") == 0 ? "" : "urn:metaoutput:pipe:") + MP_STRING_LOWER(name);
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

bool extension::AnyPipe::Send(MP_STRING name, MP_STRING value)
{
    auto a_Result = false;
    try
    {
        auto a_Context1 = (MP_PTR(MP_PIPE_CLIENT))nullptr;
        auto a_Context2 = (MP_PTR(MP_PIPE_WRITESTREAM))nullptr;
        {
            MP_PIPE_CLIENT_INITIALIZE(a_Context1, GetPipeName(name), MP_PIPE_DIRECTION_OUT);
            MP_PIPE_CLIENT_CONNECT(a_Context1, CONSTANT::PIPE::TIMEOUT);
            MP_PIPE_WRITESTREAM_INITIALIZE(a_Context2, a_Context1);
        }
        if (MP_PIPE_CLIENT_CONNECTED(a_Context1))
        {
            MP_PIPE_WRITESTREAM_WRITE(a_Context2, value);
            a_Result = true;
        }
        {
            MP_PIPE_WRITESTREAM_FINALIZE(a_Context2);
            MP_PIPE_CLIENT_FINALIZE(a_Context1);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
        a_Result = false;
    }
    return a_Result;
}

// Public ##############
MP_STRING extension::AnyPipe::GetPipeName(MP_STRING name)
{
    auto a_Context = "-" + MP_CONVERT_STRING_FROM_INT(MP_PROCESS_ID_GET(MP_PROCESS_CURRENT_GET()), 0);
    if (MP_STRING_CONTAINS(name, a_Context))
    {
        return name;
    }
    else
    {
        return name + a_Context;
    }
}

// Protected ###########
void extension::AnyPipe::_Execute(MP_PTR(atom::Trace), MP_STRING, MP_STRING)
{
}

// Private #############
void extension::AnyPipe::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyPipe)>(sender);
    while (a_Context != nullptr)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            {
                MP_PIPE_SERVER_INITIALIZE(a_Context1, GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
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
                            if (a_Context != nullptr)
                            {
                                a_Context->_Execute(a_Context->m_Context, a_Context->m_Name, a_Context3);
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
