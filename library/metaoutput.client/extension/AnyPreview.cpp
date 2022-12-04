
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) extension::AnyPreview::s_Mutex = nullptr;
MP_PTR(MP_VECTOR(extension::AnyPreview::Item)) extension::AnyPreview::s_Items = nullptr;
#endif

// extension::AnyPreview ######################################################
void extension::AnyPreview::Connect()
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
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyPreview::Disconnect()
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
                    Send(a_Context->m_Name, atom::Trace::CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyPreview::Register(MP_STRING extension, MP_PTR(AnyPreview) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            auto a_Context = MP_NEW Item();
            {
                a_Context->m_Name = "PREVIEW." + GetName(extension);
                a_Context->m_Context = MP_NEW atom::Trace();
                a_Context->m_Extension = context;
                a_Context->m_Thread = nullptr;
            }
            {
                MP_THREAD_INITIALIZE(a_Context->m_Thread, __ThreadExecute);
                MP_THREAD_NAME_SET(a_Context->m_Thread, "METAOUTPUT.PREVIEW: " + extension);
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
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnyPreview::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            return Send("PREVIEW" + MP_STRING_UPPER(GetExtension(url)), url);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Send(NAME::SOURCE::STATUS, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
            SendPreview(NAME::EVENT::EXCEPTION, url);
    }
    return false;
}

bool extension::AnyPreview::Send(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        return Send("", value);
    }
    return false;
}

bool extension::AnyPreview::Send(MP_STRING pipeName, MP_STRING value)
{
    auto a_Result = false;
    try
    {
        auto a_Context1 = (MP_PTR(MP_PIPE_CLIENT))nullptr;
        auto a_Context2 = (MP_PTR(MP_PIPE_WRITESTREAM))nullptr;
        {
            MP_PIPE_CLIENT_INITIALIZE(a_Context1, GetPipeName(pipeName), MP_PIPE_DIRECTION_OUT);
            MP_PIPE_CLIENT_CONNECT(a_Context1, atom::Trace::CONSTANT::PIPE::TIMEOUT);
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
MP_STRING extension::AnyPreview::GetExtension(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Result = atom::Trace::GetUrlFinal(url);
        {
            auto a_Index = MP_STRING_LASTINDEXOF(a_Result, ".");
            if (a_Index > 0)
            {
                return MP_STRING_SUBSTRING(a_Result, a_Index, MP_STRING_SIZE_GET(a_Result) - a_Index);
            }
        }
    }
    return "";
}

MP_STRING extension::AnyPreview::GetName(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = "." + MP_STRING_UPPER(value);
        {
            a_Result = MP_STRING_REPLACE(a_Result, "..", ".");
        }
        return a_Result;
    }
    return "";
}

MP_STRING extension::AnyPreview::GetPipeName(MP_STRING name)
{
    auto a_Result = atom::Trace::CONSTANT::PIPE::NAME;
    {
        a_Result += "." + MP_CONVERT_STRING_FROM_INT(MP_PROCESS_ID_GET(MP_PROCESS_CURRENT_GET()), 0);
    }
    if (MP_STRING_EMPTY(name) == false)
    {
        a_Result += GetName(name);
    }
    return a_Result;
}

MP_STRING extension::AnyPreview::GetFinalText(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = (MP_STRING)"";
        auto a_TextBuffer = MP_STRING_BUFFER_GET(value);
        auto a_TextSize = MP_STRING_SIZE_GET(value);
        auto a_IsFound = false;
        {
            MP_STRING_RESERVE_SET(a_Result, a_TextSize);
        }
        for (auto i = 0; i < a_TextSize; i++)
        {
            switch (a_TextBuffer[i])
            {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                if (a_IsFound == false)
                {
                    a_Result += " ";
                    a_IsFound = true;
                }
                break;
            default:
                if (a_TextBuffer[i] > 20)
                {
                    a_Result += a_TextBuffer[i];
                    a_IsFound = false;
                }
                break;
            }
        }
        return MP_STRING_TRIM(a_Result);
    }
    return "";
}

MP_STRING extension::AnyPreview::GetProperty(MP_STRING name)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(name) == false)
    {
        auto a_Name = "Software\\MetaPlatform\\" + MP_STRING_REPLACE(name, "/", "\\");
        try
        {
            auto a_Index = MP_STRING_LASTINDEXOF(a_Name, "\\");
            if (a_Index > 0)
            {
                MP_REGISTRY a_Context;
                {
                    MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, MP_STRING_SUBSTRING(a_Name, 0, a_Index), false);
                }
                {
                    a_Result = MP_REGISTRY_GET(a_Context, MP_STRING_SUBSTRING(a_Name, a_Index + 1, MP_STRING_SIZE_GET(a_Name) - a_Index - 1), "");
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
    return a_Result;
}

MP_INT extension::AnyPreview::GetProperty(MP_STRING name, bool isVerified)
{
    if (MP_STRING_EMPTY(name) == false)
    {
        auto a_Result = __GetInteger(extension::AnyPreview::GetProperty(name));
        if (isVerified)
        {
            if (name == NAME::PROPERTY::PREVIEW_DOCUMENT_SIZE)
            {
                return MP_MAX(a_Result, 1);
            }
            if (name == NAME::PROPERTY::PREVIEW_MEDIA_SIZE)
            {
                return MP_MAX(a_Result, atom::Trace::CONSTANT::OUTPUT::PREVIEW_MIN_SIZE);
            }
            if (name == NAME::PROPERTY::PREVIEW_TABLE_SIZE)
            {
                return MP_MAX(a_Result, 1);
            }
            if (name == NAME::PROPERTY::PREVIEW_WIDTH)
            {
                return MP_MAX(a_Result, atom::Trace::CONSTANT::OUTPUT::PREVIEW_MIN_WIDTH);
            }
        }
        return a_Result;
    }
    return 0;
}

MP_STRING extension::AnyPreview::GetState()
{
    return extension::AnyPreview::GetProperty(NAME::PROPERTY::PREVIEW_STATUS);
}

void extension::AnyPreview::SetState(MP_STRING value)
{
    MP_REGISTRY a_Context;
    try
    {
        MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, "Software\\MetaPlatform\\METAOUTPUT\\PREVIEW", false);
        MP_REGISTRY_SET(a_Context, "STATUS", value);
        MP_REGISTRY_FINALIZE(a_Context);
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

// Protected ###########
void extension::AnyPreview::_Execute(MP_PTR(atom::Trace), MP_INT, MP_STRING, MP_STRING)
{
}

// Private #############
MP_PTR(MP_THREAD_MUTEX) extension::AnyPreview::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, atom::Trace::CONSTANT::OUTPUT::MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
MP_INT extension::AnyPreview::__GetInteger(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        try
        {
            return MP_CONVERT_STRING_TO_INT(value);
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
        }
    }
    return 0;
}

// Private #############
void extension::AnyPreview::__Execute(MP_PTR(AnyPreview) sender, MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url)
{
    try
    {
        auto a_Context = atom::Trace::GetUrlFinal(url);
        {
            SetState(NAME::STATE::EXECUTE);
        }
        try
        {
            if ((MP_FILE_FOUND(a_Context) == false) && (MP_FOLDER_FOUND(a_Context) == false))
            {
                auto a_Context1 = (MP_PTR(MP_WEB_CLIENT))nullptr;
                {
                    a_Context = atom::Trace::GetUrlPreview(url);
                }
                {
                    MP_WEB_CLIENT_INITIALIZE(a_Context1);
                    MP_WEB_CLIENT_DOWNLOAD_FILE_ASYNC(a_Context1, url, a_Context, __DownloadCompleted);
                    MP_WEB_CLIENT_ONPROGRESS_SET(a_Context1, __DownloadProgress);
                }
                while ((GetState() != NAME::STATE::CANCEL) && MP_WEB_CLIENT_ISWORKING(a_Context1))
                {
                    MP_THREAD_SLEEP(50);
                }
                {
                    MP_WEB_CLIENT_CANCEL_ASYNC(a_Context1);
                    MP_WEB_CLIENT_FINALIZE(a_Context1);
                }
                if (MP_FILE_SIZE_GET(a_Context) == 0)
                {
                    {
                        MP_FILE_DELETE(a_Context);
                    }
                    {
                        a_Context = atom::Trace::GetUrlFinal(url);
                    }
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            a_Context = atom::Trace::GetUrlFinal(url);
        }
        if (MP_FILE_FOUND(a_Context) || MP_FOLDER_FOUND(a_Context) || MP_STRING_CONTAINS(url, "://") || MP_STRING_CONTAINS(url, ":\\\\"))
        {
            if (GetState() != NAME::STATE::CANCEL)
            {
                context->
                    SetUrlPreview(a_Context)->
                    SendPreview(NAME::EVENT::INFO, url);
            }
            if (GetState() != NAME::STATE::CANCEL)
            {
                try
                {
                    sender->_Execute(context, level, url, a_Context);
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    context->
                        Send(NAME::SOURCE::STATUS, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_TYPE_NAME_OBJECT(ex) + " [" + MP_EXCEPTION_MESSAGE_GET(ex) + "]")->
                        SendPreview(NAME::EVENT::WARNING, url);
                }
            }
            if (GetState() == NAME::STATE::CANCEL)
            {
                context->
                    Send(NAME::SOURCE::STATUS, NAME::EVENT::WARNING, 0, "[[[PREVIEW.FAILED]]]: [[[Execution is terminated]]], [" + url + "]")->
                    SendPreview(NAME::EVENT::WARNING, url);
            }
        }
        else
        {
            context->
                Send(NAME::SOURCE::STATUS, NAME::EVENT::ERROR, 0, "[[[PREVIEW.FAILED]]]: [[[File not found]]], [" + url + "]");
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
                Send(NAME::SOURCE::STATUS, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
                SendPreview(NAME::EVENT::EXCEPTION, url);
        }
    }
}

// Private #############
void extension::AnyPreview::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(Item)>(sender);
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
                                    __Execute(
                                        a_Context->m_Extension,
                                        a_Context->m_Context,
                                        1,
                                        a_Context3);
                                }
                                {
                                    MP_THREAD_MUTEX_UNLOCK(__GetMutex());
                                }
                            }
                            catch (MP_PTR(MP_EXCEPTION) ex)
                            {
                                MP_THREAD_MUTEX_UNLOCK(__GetMutex());
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

void extension::AnyPreview::MP_WEB_CLIENT_CALLBACK_DOWNLOAD_COMPLETED(__DownloadCompleted, sender, params)
{
    MP_UNUSED(sender);
    MP_UNUSED(params);
}

void extension::AnyPreview::MP_WEB_CLIENT_CALLBACK_PROGRESS(__DownloadProgress, sender, params)
{
    auto a_Context = dynamic_cast<MP_PTR(MP_WEB_CLIENT)>(sender);
    if (a_Context != nullptr)
    {
        if (MP_WEB_CLIENT_CALLBACK_PROGRESS_RECEIVED_PERSENT_GET(params) < 100)
        {
            atom::Trace::GetInstance()->
                SetProgress(MP_WEB_CLIENT_CALLBACK_PROGRESS_RECEIVED_PERSENT_GET(params))->
                SendPreview(NAME::EVENT::INFO, MP_WEB_CLIENT_CALLBACK_DOWNLOAD_URL_GET(a_Context));
        }
        if ((MP_WEB_CLIENT_CALLBACK_PROGRESS_RECEIVED_PERSENT_GET(params) <= 3) && (MP_WEB_CLIENT_CALLBACK_PROGRESS_TOTAL_SIZE_GET(params) > 10000000))
        {
            SetState(NAME::STATE::CANCEL);
        }
    }
}
