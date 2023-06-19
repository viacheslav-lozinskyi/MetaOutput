
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnyPreview)) extension::AnyPreview::s_Items = nullptr;
#endif

// extension::AnyPreview ######################################################
void extension::AnyPreview::Connect(MP_STRING application, MP_STRING extension)
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyPreview);
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

bool extension::AnyPreview::Register(MP_STRING extension, MP_PTR(AnyPreview) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            {
                context->m_Name = "urn:metaoutput:preview:" + MP_STRING_LOWER(extension);
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

bool extension::AnyPreview::Execute(MP_STRING url)
{
    try
    {
        if ((GetState() != NAME::STATE::WORK::EXECUTE) && (MP_STRING_EMPTY(url) == false))
        {
            return extension::AnyPipe::Execute("urn:metaoutput:preview:" + MP_STRING_LOWER(GetExtension(url)), url);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Send(NAME::SOURCE::ALERT, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
            SendPreview(NAME::EVENT::EXCEPTION, url);
    }
    return false;
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
        auto a_Result = 0;
        auto a_Context = extension::AnyPreview::GetProperty(name);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            try
            {
                a_Result = MP_CONVERT_STRING_TO_INT(a_Context);
            }
            catch (MP_PTR(MP_EXCEPTION))
            {
                // This exception can be ignored
            }
        }
        if (isVerified)
        {
            if (name == NAME::PROPERTY::PREVIEW_DOCUMENT_SIZE)
            {
                return MP_MAX(a_Result, 2);
            }
            if (name == NAME::PROPERTY::PREVIEW_BROWSER_SIZE)
            {
                return MP_MAX(a_Result, 10);
            }
            if (name == NAME::PROPERTY::PREVIEW_MEDIA_SIZE)
            {
                return MP_MAX(a_Result, 2);
            }
            if (name == NAME::PROPERTY::PREVIEW_TABLE_SIZE)
            {
                return MP_MAX(a_Result, 100);
            }
        }
        return a_Result;
    }
    return 0;
}

MP_STRING extension::AnyPreview::GetState()
{
    return extension::AnyPreview::GetProperty("METAOUTPUT/PREVIEW/STATE");
}

void extension::AnyPreview::SetState(MP_STRING value)
{
    MP_REGISTRY a_Context;
    try
    {
        MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, "Software\\MetaPlatform\\METAOUTPUT\\PREVIEW", false);
        MP_REGISTRY_SET(a_Context, "STATE", value);
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
void extension::AnyPreview::__Execute(MP_PTR(AnyPreview) sender, MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING url)
{
    try
    {
        auto a_Context = atom::Trace::GetUrlFinal(url);
        {
            SetState(NAME::STATE::WORK::EXECUTE);
        }
        try
        {
            if ((MP_FILE_FOUND(a_Context) == false) && (MP_FOLDER_FOUND(a_Context) == false))
            {
                auto a_Context1 = (MP_PTR(MP_WEB_CLIENT))nullptr;
                {
                    a_Context = atom::Trace::GetUrlTemp(url);
                }
                {
                    MP_WEB_CLIENT_INITIALIZE(a_Context1);
                    MP_WEB_CLIENT_DOWNLOAD_FILE_ASYNC(a_Context1, url, a_Context, __DownloadCompleted);
                    MP_WEB_CLIENT_ONPROGRESS_SET(a_Context1, __DownloadProgress);
                }
                while ((GetState() != NAME::STATE::WORK::CANCEL) && MP_WEB_CLIENT_ISWORKING(a_Context1))
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
            if (GetState() != NAME::STATE::WORK::CANCEL)
            {
                trace->
                    SetUrlPreview(a_Context)->
                    SendPreview(NAME::EVENT::INFO, url);
            }
            if (GetState() != NAME::STATE::WORK::CANCEL)
            {
                try
                {
                    if (sender != nullptr)
                    {
                        sender->_Execute(trace, level, url, a_Context);
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    trace->
                        Send(NAME::SOURCE::ALERT, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_TYPE_NAME_OBJECT(ex) + " [" + MP_EXCEPTION_MESSAGE_GET(ex) + "]")->
                        SendPreview(NAME::EVENT::WARNING, url);
                }
            }
            if (GetState() == NAME::STATE::WORK::CANCEL)
            {
                trace->
                    Send(NAME::SOURCE::ALERT, NAME::EVENT::WARNING, 0, "[[[PREVIEW.FAILED]]]: [[[Execution is terminated]]], [" + url + "]")->
                    SendPreview(NAME::EVENT::WARNING, url);
            }
        }
        else
        {
            trace->
                Send(NAME::SOURCE::ALERT, NAME::EVENT::ERROR, 0, "[[[PREVIEW.FAILED]]]: [[[File not found]]], [" + url + "]");
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
                Send(NAME::SOURCE::ALERT, NAME::EVENT::EXCEPTION, 0, "[[[PREVIEW.FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex))->
                SendPreview(NAME::EVENT::EXCEPTION, url);
        }
    }
}

// Private #############
void extension::AnyPreview::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyPreview)>(sender);
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
                                __Execute(a_Context, a_Context4->Clear(), 1, a_Context5);
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
            SetState(NAME::STATE::WORK::CANCEL);
        }
    }
}
