
#include "../All.hpp"

// extension::AnyPreview ######################################################
void extension::AnyPreview::Connect(MP_STRING application, MP_STRING extension)
{
    try
    {
        {
            extension::AnyTool::Connect(application, extension);
        }
        {
            SetState(STATE::WORK::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
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
                    extension::AnyTool::Execute(a_Context->m_Name, pattern::data::Message::CONSTANT::PIPE::TERMINATE_REQUEST);
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
}

bool extension::AnyPreview::Register(MP_STRING extension, MP_PTR(AnyPreview) context)
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyPreview);
        }
        if ((s_Items != nullptr) && (context != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            auto a_Name = GetExtension(extension);
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
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyPreview::Unregister(MP_STRING extension)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(extension) == false))
        {
            auto a_Name = GetExtension(extension);
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
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyPreview::Execute(MP_STRING url)
{
    try
    {
        auto a_Context1 = (MP_PTR(MP_PIPE_CLIENT))nullptr;
        auto a_Context2 = (MP_PTR(MP_PIPE_WRITESTREAM))nullptr;
        {
            MP_PIPE_CLIENT_INITIALIZE(a_Context1, GetPipeName(GetExtension(url)), MP_PIPE_DIRECTION_OUT);
            MP_PIPE_CLIENT_CONNECT(a_Context1, pattern::data::Message::CONSTANT::PIPE::TIMEOUT);
            MP_PIPE_WRITESTREAM_INITIALIZE(a_Context2, a_Context1);
        }
        if (MP_PIPE_CLIENT_CONNECTED(a_Context1))
        {
            MP_PIPE_WRITESTREAM_WRITE(a_Context2, url);
        }
        {
            MP_PIPE_WRITESTREAM_FINALIZE(a_Context2);
            MP_PIPE_CLIENT_FINALIZE(a_Context1);
        }
        return true;
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

// Public ##############
MP_STRING extension::AnyPreview::GetExtension(MP_STRING url)
{
    if (MP_STRING_EMPTY(url))
    {
        return "";
    }
    else
    {
        auto a_Index = MP_STRING_LASTINDEXOF(url, ".");
        if (a_Index > 0)
        {
            return MP_STRING_LOWER(MP_STRING_SUBSTRINGEND(url, a_Index));
        }
    }
    return MP_STRING_LOWER(url);
}

MP_STRING extension::AnyPreview::GetFinalText(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_TextBuffer = MP_STRING_BUFFER_GET(value);
        auto a_TextSize = MP_STRING_SIZE_GET(value);
        auto a_Result = MP_NEW System::Text::StringBuilder(a_TextSize);
        auto a_IsFound = false;
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
                    a_Result->Append(" ");
                    a_IsFound = true;
                }
                break;
            default:
                if (a_TextBuffer[i] > 20)
                {
                    a_Result->Append(a_TextBuffer[i]);
                    a_IsFound = false;
                }
                break;
            }
        }
        return MP_STRING_TRIM(a_Result->ToString());
    }
    return "";
}

MP_STRING extension::AnyPreview::GetPipeName(MP_STRING name)
{
    auto a_Context = ":" + MP_CONVERT_STRING_FROM_INT(MP_PROCESS_ID_GET(MP_PROCESS_CURRENT_GET()), 0);
    if (MP_STRING_CONTAINS(name, a_Context))
    {
        return "urn:metaoutput:preview:" + MP_STRING_LOWER(name);
    }
    else
    {
        return "urn:metaoutput:preview:" + MP_STRING_LOWER(name) + a_Context;
    }
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
            (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
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
            if (name == extension::AnyPreview::VARIABLE::PREVIEW::DOCUMENT_SIZE)
            {
                return MP_MAX(a_Result, 2);
            }
            if (name == extension::AnyPreview::VARIABLE::PREVIEW::BROWSER_SIZE)
            {
                return MP_MAX(a_Result, 10);
            }
            if (name == extension::AnyPreview::VARIABLE::PREVIEW::MEDIA_SIZE)
            {
                return MP_MAX(a_Result, 2);
            }
            if (name == extension::AnyPreview::VARIABLE::PREVIEW::TABLE_SIZE)
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
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
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
            SetState(STATE::WORK::EXECUTE);
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
                while ((GetState() != STATE::WORK::CANCEL) && MP_WEB_CLIENT_ISWORKING(a_Context1))
                {
                    MP_THREAD_SLEEP(50);
                }
                {
                    MP_WEB_CLIENT_CANCEL_ASYNC(a_Context1);
                    MP_WEB_CLIENT_FINALIZE(a_Context1);
                }
                if (MP_FILE_SIZE_GET(a_Context) == 0)
                {
                    a_Context = atom::Trace::GetUrlFinal(url);
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            a_Context = atom::Trace::GetUrlFinal(url);
        }
        if (MP_FILE_FOUND(a_Context) || MP_FOLDER_FOUND(a_Context) || MP_STRING_CONTAINS(url, "://") || MP_STRING_CONTAINS(url, ":\\\\"))
        {
            {
                trace->SendPreviewMessage(level, NAME::SOURCE::PREVIEW, NAME::EVENT::INFO, url, STATE::MESSAGE::RESEND | pattern::data::Message::STATE::CLEAR | pattern::data::Message::STATE::EXPAND, 0);
            }
            if ((GetState() != STATE::WORK::CANCEL) && (sender != nullptr))
            {
                sender->_Execute(trace, level, url, a_Context);
            }
            if (GetState() == STATE::WORK::CANCEL)
            {
                trace->SendPreviewMessage(level, NAME::SOURCE::PREVIEW, NAME::EVENT::WARNING, url, STATE::MESSAGE::UPDATE, 0);
                trace->SendTraceMessage(0, NAME::SOURCE::ALERT, NAME::EVENT::WARNING, "[[[PREVIEW]]].[[[FAILED]]]: [[[Execution is terminated]]], [" + url + "]");
            }
        }
        else
        {
            trace->SendTraceMessage(0, NAME::SOURCE::ALERT, NAME::EVENT::ERROR, "[[[PREVIEW]]].[[[FAILED]]]: [[[File not found]]], [" + url + "]");
        }
        {
            SetState(STATE::WORK::WAIT);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        {
            SetState(STATE::WORK::WAIT);
        }
        {
            trace->SendTraceMessage(0, NAME::SOURCE::ALERT, NAME::EVENT::ERROR, "[[[PREVIEW]]].[[[FAILED]]]: " + MP_EXCEPTION_MESSAGE_GET(ex));
            trace->SendPreviewMessage(level, NAME::SOURCE::PREVIEW, NAME::EVENT::ERROR, url, STATE::MESSAGE::UPDATE, 0);
        }
    }
}

// Private #############
void extension::AnyPreview::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    auto a_Context = dynamic_cast<MP_PTR(AnyPreview)>(sender);
    auto a_Trace = MP_NEW atom::Trace();
    auto a_IsFound = a_Context == nullptr;
    while (a_IsFound == false)
    {
        try
        {
            auto a_Context1 = (MP_PTR(MP_THREAD_MUTEX))nullptr;
            auto a_Context2 = (MP_PTR(MP_PIPE_SERVER))nullptr;
            auto a_Context3 = (MP_PTR(MP_PIPE_READSTREAM))nullptr;
            {
                MP_THREAD_MUTEX_INITIALIZE(a_Context1, pattern::data::Message::CONSTANT::OUTPUT::MUTEX, false);
                MP_PIPE_SERVER_INITIALIZE(a_Context2, GetPipeName(a_Context->m_Name), MP_PIPE_DIRECTION_IN, 128);
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
                        auto a_Context4 = MP_PIPE_READSTREAM_READ(a_Context3);
                        {
                            MP_PIPE_SERVER_DISCONNECT(a_Context2);
                        }
                        if (a_Context4 == pattern::data::Message::CONSTANT::PIPE::TERMINATE_REQUEST)
                        {
                            a_IsFound = true;
                            break;
                        }
                        try
                        {
                            MP_THREAD_MUTEX_LOCK(a_Context1);
                            {
                                __Execute(a_Context, a_Trace->Clear(), 1, a_Context4);
                            }
                            {
                                a_Trace->CommitTransaction();
                                a_Trace->CancelTransaction();
                            }
                            MP_THREAD_MUTEX_UNLOCK(a_Context1);
                        }
                        catch (MP_PTR(MP_EXCEPTION) ex)
                        {
                            MP_THREAD_MUTEX_UNLOCK(a_Context1);
                            a_Trace->CommitTransaction();
                            a_Trace->CancelTransaction();
                            a_Trace->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
                            MP_THREAD_SLEEP(pattern::data::Message::CONSTANT::PIPE::TIMEOUT);
                            break;
                        }
                    }
                }
                catch (MP_PTR(MP_EXCEPTION) ex)
                {
                    a_Trace->CommitTransaction();
                    a_Trace->CancelTransaction();
                    a_Trace->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
                    MP_THREAD_SLEEP(pattern::data::Message::CONSTANT::PIPE::TIMEOUT);
                    break;
                }
            }
            {
                MP_PIPE_READSTREAM_FINALIZE(a_Context3);
                MP_PIPE_SERVER_FINALIZE(a_Context2);
                MP_THREAD_MUTEX_FINALIZE(a_Context1);
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            a_Trace->CommitTransaction();
            a_Trace->CancelTransaction();
            a_Trace->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
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
        auto a_Context1 = MP_WEB_CLIENT_CALLBACK_PROGRESS_RECEIVED_PERSENT_GET(params);
        if (a_Context1 < 100)
        {
            (MP_NEW atom::Trace())->SendPreviewMessage(0, NAME::SOURCE::PREVIEW, NAME::EVENT::INFO, MP_WEB_CLIENT_CALLBACK_DOWNLOAD_URL_GET(a_Context), STATE::MESSAGE::UPDATE, a_Context1);
        }
        if ((a_Context1 <= 3) && (MP_WEB_CLIENT_CALLBACK_PROGRESS_TOTAL_SIZE_GET(params) > 10000000))
        {
            SetState(STATE::WORK::CANCEL);
        }
    }
}
