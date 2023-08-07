
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) extension::AnyPipe::s_Mutex = nullptr;
MP_PTR(MP_PIPE_WRITESTREAM) extension::AnyPipe::s_Default = nullptr;
MP_PTR(MP_VECTOR(extension::AnyPipe)) extension::AnyPipe::s_Items = nullptr;
#endif

// extension::AnyPipe ######################################################
void extension::AnyPipe::Connect(MP_STRING application, MP_STRING extension)
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyPipe);
        }
        {
            extension::AnyPipe::Validate(application, extension);
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
                    Execute(a_Context->m_Name, CONSTANT::PIPE::TERMINATE_REQUEST);
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
            auto a_Name = (MP_STRING_INDEXOF(name, "urn:") == 0 ? "" : "urn:metaoutput:pipe:") + MP_STRING_LOWER(name);
            {
                context->m_Name = a_Name;
                context->m_Thread = nullptr;
            }
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == a_Name)
                {
                    return false;
                }
            }
            {
                MP_THREAD_INITIALIZE(context->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(context->m_Thread, a_Name);
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

bool extension::AnyPipe::Unregister(MP_STRING name)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            auto a_Name = (MP_STRING_INDEXOF(name, "urn:") == 0 ? "" : "urn:metaoutput:pipe:") + MP_STRING_LOWER(name);
            for (auto i = MP_VECTOR_SIZE_GET(s_Items) - 1; i >= 0; i--)
            {
                if (s_Items[i]->m_Name == a_Name)
                {
                    MP_VECTOR_DELETE(s_Items, i);
                    return true;
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return false;
}

bool extension::AnyPipe::Execute(MP_STRING name, MP_STRING value)
{
    MP_THREAD_MUTEX_LOCK(__GetMutex());
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
        }
        {
            MP_PIPE_WRITESTREAM_FINALIZE(a_Context2);
            MP_PIPE_CLIENT_FINALIZE(a_Context1);
        }
        MP_THREAD_MUTEX_UNLOCK(__GetMutex());
        return true;
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_THREAD_MUTEX_UNLOCK(__GetMutex());
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return false;
}

void extension::AnyPipe::Validate(MP_STRING application, MP_STRING extension)
{
    try
    {
        if (MP_STRING_EMPTY(application) == false)
        {
            MP_REGISTRY a_Context;
            {
                MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, "Software\\MetaPlatform\\APPLICATION\\", false);
            }
            if (MP_STRING_EMPTY(MP_REGISTRY_GET(a_Context, "USER.ID", "")))
            {
                MP_FILE_EXECUTE("https://www.metaoutput.net/requirements?application=" + application + "&extension=" + extension);
            }
            {
                MP_REGISTRY_FINALIZE(a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

// Public ##############
bool extension::AnyPipe::IsButtonPressed(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Context = GetAttribute(value, NAME::ATTRIBUTE::MOUSE);
        if (MP_STRING_CONTAINS(a_Context, value))
        {
            return true;
        }
    }
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Context = GetAttribute(value, NAME::ATTRIBUTE::KEYBOARD);
        if (MP_STRING_CONTAINS(a_Context, value))
        {
            return true;
        }
    }
    return false;
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

MP_STRING extension::AnyPipe::GetAttribute(MP_STRING value, MP_STRING name)
{
    return atom::Trace::GetAttribute(value, name);
}

// Protected ###########
void extension::AnyPipe::_Execute(MP_PTR(atom::Trace), MP_STRING, MP_STRING)
{
}

// Private #############
MP_PTR(MP_THREAD_MUTEX) extension::AnyPipe::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, CONSTANT::PIPE::MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
void extension::AnyPipe::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyPipe)>(sender);
    auto a_IsFound = a_Context == nullptr;
    while (a_IsFound == false)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            auto a_Context3 = MP_NEW atom::Trace();
            {
                MP_PIPE_SERVER_INITIALIZE(a_Context1, extension::AnyPipe::GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
                MP_PIPE_READSTREAM_INITIALIZE(a_Context2, a_Context1);
            }
            while (a_IsFound == false)
            {
                try
                {
                    {
                        MP_PIPE_SERVER_CONNECT(a_Context1);
                    }
                    if (MP_PIPE_SERVER_CONNECTED(a_Context1))
                    {
                        auto a_Context4 = MP_PIPE_READSTREAM_READ(a_Context2);
                        {
                            MP_PIPE_SERVER_DISCONNECT(a_Context1);
                        }
                        if (a_Context4 == CONSTANT::PIPE::TERMINATE_REQUEST)
                        {
                            a_IsFound = true;
                            break;
                        }
                        else
                        {
                            a_Context->_Execute(a_Context3->Clear(), a_Context->m_Name, a_Context4);
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
                MP_PIPE_READSTREAM_FINALIZE(a_Context2);
                MP_PIPE_SERVER_FINALIZE(a_Context1);
            }
            {
                MP_DELETE a_Context3;
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
            break;
        }
    }
}
