
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) extension::AnyPreview::s_Mutex = nullptr;
MP_PTR(MP_VECTOR(extension::AnyPreview::Item)) extension::AnyPreview::s_Items = nullptr;
MP_PTR(MP_VECTOR(extension::AnyPreview::Item)) extension::AnyPreview::s_Pipes = nullptr;
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
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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

void extension::AnyPreview::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            if (__SendRequest("PREVIEW" + MP_STRING_UPPER(GetExtension(url)), url) == false)
            {
                __SendRequest("PREVIEW" + CONSTANT::OUTPUT_PIPE_GENERIC, url);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Send(NAME::SOURCE::STATUS, NAME::TYPE::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
            SendPreview(NAME::TYPE::EXCEPTION, url);
    }
}

bool extension::AnyPreview::Send(MP_STRING value)
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
                auto a_Name = GetPipeName("");
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
            for (auto i = 1; i <= CONSTANT::OUTPUT_PIPE_CONNECT_COUNT; i++)
            {
                try
                {
                    if (MP_PIPE_CLIENT_CONNECTED(a_Context))
                    {
                        break;
                    }
                    else
                    {
                        MP_PIPE_CLIENT_CONNECT(a_Context, CONSTANT::OUTPUT_PIPE_TIMEOUT);
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    if (i == CONSTANT::OUTPUT_PIPE_CONNECT_COUNT)
                    {
                        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
                    }
                }
            }
            if (MP_PIPE_CLIENT_CONNECTED(a_Context))
            {
                MP_PIPE_BUFFER a_Context1;
                {
                    MP_PIPE_BUFFER_INITIALIZE(a_Context1, MP_STRING_SIZE_GET(value) * 4);
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
MP_STRING extension::AnyPreview::GetExtension(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Result = __GetFileUrl(url);
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
    auto a_Result = CONSTANT::OUTPUT_PIPE_NAME;
    if (MP_STRING_EMPTY(name) == false)
    {
        a_Result += GetName(name);
    }
    {
        a_Result += "." + MP_CONVERT_STRING_FROM_INT(MP_PROCESS_ID_GET(MP_PROCESS_CURRENT_GET()), 0);
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

MP_STRING extension::AnyPreview::GetUrlPreview(MP_STRING url)
{
    return GetUrlPreview(url, "");
}

MP_STRING extension::AnyPreview::GetUrlPreview(MP_STRING url, MP_STRING extension)
{
    try
    {
        if (MP_STRING_EMPTY(url) == false)
        {
            auto a_Context = __GetFileUrl(url);
            {
                a_Context = MP_STRING_REPLACE(a_Context, "\\", "-");
                a_Context = MP_STRING_REPLACE(a_Context, "/", "-");
                a_Context = MP_STRING_REPLACE(a_Context, ":", "-");
                a_Context = MP_STRING_REPLACE(a_Context, " ", "_");
                a_Context = MP_STRING_LOWER(a_Context);
            }
            {
                auto a_Context1 = __GetProxyFolder();
                if (MP_FOLDER_FOUND(a_Context1) == false)
                {
                    MP_FOLDER_CREATE(a_Context1);
                }
                if (MP_STRING_EMPTY(extension))
                {
                    return a_Context1 + "\\" + a_Context;
                }
                else
                {
                    return a_Context1 + "\\" + a_Context + ((extension[0] != '.') ? "." : "") + MP_STRING_LOWER(extension);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
            MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
                return MP_MAX(a_Result, CONSTANT::OUTPUT_PREVIEW_MIN_SIZE);
            }
            if (name == NAME::PROPERTY::PREVIEW_TABLE_SIZE)
            {
                return MP_MAX(a_Result, 1);
            }
            if (name == NAME::PROPERTY::PREVIEW_WIDTH)
            {
                return MP_MAX(a_Result, CONSTANT::OUTPUT_PREVIEW_MIN_WIDTH);
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
        MP_TRACE_DEBUG(MP_EXCEPTION_MESSAGE_GET(ex) + " @@@SOURCE DIAGNOSTIC @@@TYPE EXCEPTION");
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
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, extension::AnyPreview::CONSTANT::OUTPUT_EXECUTE_MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
MP_STRING extension::AnyPreview::__GetFileName(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Result = __GetFileUrl(url);
        {
            auto a_Index = MP_STRING_LASTINDEXOF(MP_STRING_REPLACE(a_Result, "\\", "/"), "/");
            if (a_Index > 0)
            {
                return MP_STRING_SUBSTRING(a_Result, a_Index, MP_STRING_SIZE_GET(a_Result) - a_Index);
            }
        }
    }
    return "";
}

MP_STRING extension::AnyPreview::__GetFileUrl(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Result = url;
        {
            auto a_Index = MP_STRING_LASTINDEXOF(a_Result, "?");
            if (a_Index > 0)
            {
                a_Result = MP_STRING_SUBSTRING(a_Result, 0, a_Index);
            }
        }
        {
            auto a_Index = MP_STRING_LASTINDEXOF(a_Result, "#");
            if (a_Index > 0)
            {
                a_Result = MP_STRING_SUBSTRING(a_Result, 0, a_Index);
            }
        }
        return MP_STRING_TRIM(a_Result);
    }
    return "";
}

MP_STRING extension::AnyPreview::__GetProxyFolder()
{
    auto a_Result = MP_FOLDER_SYSTEM_TEMP + ".metaoutput\\";
    {
        auto a_Context = MP_TIME_CURRENT;
        {
            a_Result += MP_CONVERT_STRING_FROM_INT(MP_TIME_YEAR_GET(&a_Context), 4);
            a_Result += "-";
            a_Result += MP_CONVERT_STRING_FROM_INT(MP_TIME_MONTH_GET(&a_Context), 2);
            a_Result += "-";
            a_Result += MP_CONVERT_STRING_FROM_INT(MP_TIME_DAY_GET(&a_Context), 2);
        }
    }
    return a_Result;
}

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
bool extension::AnyPreview::__SendRequest(MP_STRING name, MP_STRING value)
{
    auto a_Result = false;
    if (MP_STRING_EMPTY(name) == false)
    {
        try
        {
            MP_PIPE_CLIENT a_Context;
            {
                MP_PIPE_CLIENT_INITIALIZE(a_Context, GetPipeName(name), MP_PIPE_DIRECTION_OUT);
                MP_PIPE_CLIENT_CONNECT(a_Context, CONSTANT::OUTPUT_PIPE_TIMEOUT);
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

void extension::AnyPreview::__Execute(MP_PTR(AnyPreview) sender, MP_PTR(atom::Trace) context, MP_INT level, MP_STRING url)
{
    try
    {
        auto a_Context = __GetFileUrl(url);
        {
            SetState(NAME::STATE::EXECUTE);
        }
        try
        {
            if ((MP_FILE_FOUND(a_Context) == false) && (MP_FOLDER_FOUND(a_Context) == false))
            {
                auto a_Context1 = (MP_PTR(MP_WEB_CLIENT))nullptr;
                {
                    a_Context = GetUrlPreview(url);
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
                        a_Context = __GetFileUrl(url);
                    }
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            a_Context = __GetFileUrl(url);
        }
        if (MP_FILE_FOUND(a_Context) || MP_FOLDER_FOUND(a_Context) || MP_STRING_CONTAINS(url, "://") || MP_STRING_CONTAINS(url, ":\\\\"))
        {
            if (GetState() != NAME::STATE::CANCEL)
            {
                context->
                    SetUrlPreview(a_Context)->
                    SendPreview(NAME::TYPE::INFO, url);
            }
            if (GetState() != NAME::STATE::CANCEL)
            {
                sender->_Execute(context, level, url, a_Context);
            }
            if (GetState() == NAME::STATE::CANCEL)
            {
                context->
                    Send(NAME::SOURCE::STATUS, NAME::TYPE::WARNING, 0, "[[[PREVIEW.FAILED]]]: [[[Execution is terminated]]], [" + url + "]")->
                    SendPreview(NAME::TYPE::WARNING, url);
            }
        }
        else
        {
            context->
                Send(NAME::SOURCE::STATUS, NAME::TYPE::ERROR, 0, "[[[PREVIEW.FAILED]]]: [[[File not found]]], [" + url + "]");
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
                Send(NAME::SOURCE::STATUS, NAME::TYPE::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
                SendPreview(NAME::TYPE::EXCEPTION, url);
        }
    }
}

// Private #############
void extension::AnyPreview::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
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
                    MP_PIPE_SERVER_INITIALIZE(a_Context1, GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 16);
                    MP_PIPE_SERVER_WAIT(a_Context1);
                }
                while (MP_PIPE_SERVER_CONNECTED(a_Context1))
                {
                    try
                    {
                        MP_PIPE_BUFFER a_Context2;
                        auto a_Size = 0;
                        {
                            MP_PIPE_BUFFER_INITIALIZE(a_Context2, CONSTANT::OUTPUT_PIPE_BUFFER_SIZE + 1);
                        }
                        {
                            a_Size = MP_PIPE_SERVER_RECEIVE(a_Context1, a_Context2, 0, CONSTANT::OUTPUT_PIPE_BUFFER_SIZE);
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
                SendPreview(NAME::TYPE::INFO, MP_WEB_CLIENT_CALLBACK_DOWNLOAD_URL_GET(a_Context));
        }
        if ((MP_WEB_CLIENT_CALLBACK_PROGRESS_RECEIVED_PERSENT_GET(params) <= 3) && (MP_WEB_CLIENT_CALLBACK_PROGRESS_TOTAL_SIZE_GET(params) > 10000000))
        {
            SetState(NAME::STATE::CANCEL);
        }
    }
}
