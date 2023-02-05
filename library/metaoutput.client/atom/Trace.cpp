
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) atom::Trace::s_Mutex = nullptr;
MP_PTR(MP_MAP(MP_PTR(atom::Trace))) atom::Trace::s_Instances = nullptr;
MP_PTR(MP_THREAD) atom::Trace::s_TraceThread = nullptr;
MP_STRING atom::Trace::s_TraceBuffer = "";
#endif

// atom::Trace ################################################################
atom::Trace::Trace()
{
    Clear();
}

// Public ##############
MP_PTR(atom::Trace) atom::Trace::GetInstance()
{
    if (s_Instances == nullptr)
    {
        s_Instances = MP_NEW MP_MAP(MP_PTR(Trace))();
    }
    if (s_Instances != nullptr)
    {
        auto a_Context = MP_CONVERT_STRING_FROM_DOUBLE(MP_THREAD_ID_GET(MP_THREAD_CURRENT_GET));
        if (MP_MAP_CONTAINS(s_Instances, a_Context) == false)
        {
            MP_MAP_APPEND(s_Instances, a_Context, MP_NEW atom::Trace());
        }
        return MP_MAP_GET(s_Instances, a_Context);
    }
    return nullptr;
}

MP_STRING atom::Trace::GetFailState(MP_STRING applicationName)
{
    auto a_Result = (MP_STRING)"";
    auto a_Name = applicationName;
    try
    {
        if (MP_STRING_EMPTY(a_Name) == false)
        {
            a_Name = MP_STRING_TRIM(a_Name);
            a_Name = MP_STRING_LOWER(a_Name);
            a_Name = MP_STRING_REPLACE(a_Name, " ", "-");
        }
        if (MP_STRING_EMPTY(a_Name) == false)
        {
            MP_REGISTRY a_Context;
            {
                MP_REGISTRY_INITIALIZE(a_Context, MP_REGISTRY_ROOT_CURRENT_USER, "Software\\MetaPlatform\\APPLICATION\\", false);
            }
            if (MP_STRING_EMPTY(MP_REGISTRY_GET(a_Context, "USER.ID", "")))
            {
                a_Result = "https://www.metaoutput.net/download" + a_Name;
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
    return a_Result;
}

MP_STRING atom::Trace::GetUrlFinal(MP_STRING url)
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

MP_STRING atom::Trace::GetUrlPreview(MP_STRING url)
{
    return GetUrlPreview(url, "");
}

MP_STRING atom::Trace::GetUrlPreview(MP_STRING url, MP_STRING extension)
{
    try
    {
        if (MP_STRING_EMPTY(url) == false)
        {
            auto a_Context = GetUrlFinal(url);
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
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return "";
}

// Public ##############
MP_PTR(atom::Trace) atom::Trace::Clear()
{
    if (this != nullptr)
    {
        try
        {
            m_Alignment = "";
            m_Background = "";
            m_Border = "";
            m_Command = "";
            m_Comment = "";
            m_Condition = "";
            m_Content = "";
            m_ContentHint = "";
            m_Control = "";
            m_Count = "";
            m_Date = "";
            m_FontName = "";
            m_FontSize = "";
            m_FontState = "";
            m_Foreground = "";
            m_Padding = "";
            m_Pipe = "";
            m_Position = "";
            m_Progress = "";
            m_Size = "";
            m_StackTrace = "";
            m_Time = "";
            m_Tml = "";
            m_Url = "";
            m_UrlInfo = "";
            m_UrlPreview = "";
            m_UrlSample = "";
            m_Value = "";
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            // Any exceptions here may be ignored
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING event, MP_INT level)
{
    if (this != nullptr)
    {
        if ((level == 0) && (MP_STRING_EMPTY(m_StackTrace) == false))
        {
            {
                m_StackTrace = "";
            }
            try
            {
                MP_STACKTRACE a_Context;
                {
                    MP_STACKTRACE_INITIALIZE(a_Context);
                }
                {
                    auto a_Size = MP_STACKTRACE_FRAME_COUNT_GET(a_Context);
                    auto a_Count = extension::AnyPreview::GetProperty(NAME::PROPERTY::DEBUGGING_STACK_SIZE, true);
                    for (auto i = 1; (i < a_Size) && (a_Count > 0); i++)
                    {
                        auto a_Context1 = MP_STACKTRACE_FRAME_GET(a_Context, i);
                        if (a_Context1 != nullptr)
                        {
                            if (MP_STRING_EMPTY(MP_STACKFRAME_FILE_NAME_GET(a_Context1)))
                            {
                                continue;
                            }
                            {
                                a_Count--;
                            }
                            {
                                m_StackTrace += __GetLevel(level) + " " + MP_STACKFRAME_METHOD_NAME_GET(a_Context1) + "(";
                            }
                            {
                                auto a_Size1 = MP_STACKFRAME_METHOD_PARAM_COUNT_GET(a_Context1);
                                for (auto ii = 0; ii < a_Size1; ii++)
                                {
                                    auto a_Context2 = MP_STACKFRAME_METHOD_PARAM_GET(a_Context1, ii);
                                    {
                                        m_StackTrace += ((ii == 0) ? "" : ", ") + MP_STACKPARAM_TYPE_NAME_GET(a_Context2) + " " + MP_STACKPARAM_NAME_GET(a_Context2);
                                    }
                                }
                            }
                            {
                                m_StackTrace += ")" +
                                    __GetSource(source) +
                                    " @@@EVENT " + NAME::EVENT::FUNCTION +
                                    " @@@COMMENT <" + MP_STACKFRAME_MODULE_NAME_GET(a_Context1) + ">" +
                                    " @@@COMMENT.HINT <[[[Module Name]]]>" +
                                    " @@@URL <<<" + MP_STACKFRAME_FILE_LINE_GET(a_Context1) + ":" + MP_STACKFRAME_FILE_POSITION_GET(a_Context1) + ">>> " + MP_STACKFRAME_FILE_NAME_GET(a_Context1) + "\n";
                            }
                        }
                    }
                }
                {
                    MP_STACKTRACE_FINALIZE(a_Context);
                }
            }
            catch (MP_PTR(MP_EXCEPTION) ex)
            {
                m_StackTrace += "\n" + __GetLevel(level) + ex->Message + " @@@SOURCE DIAGNOSTIC @@@EVENT WARNING";
            }
            {
                m_StackTrace += "\n";
            }
        }
        {
            auto a_Context = (MP_STRING)"";
            {
                MP_THREAD_MUTEX_LOCK(__GetMutex());
            }
            try
            {
                {
                    a_Context += __GetSource(source);
                    a_Context += __GetEvent(event);
                    a_Context += m_Command;
                    a_Context += m_ContentHint;
                    a_Context += m_Comment;
                    a_Context += m_Condition;
                    a_Context += m_Control;
                    a_Context += m_Count;
                    a_Context += m_Date;
                    a_Context += m_Time;
                    a_Context += m_Border;
                    a_Context += m_Background;
                    a_Context += m_Foreground;
                    a_Context += m_FontName;
                    a_Context += m_FontSize;
                    a_Context += m_FontState;
                    a_Context += m_Padding;
                    a_Context += m_Pipe;
                    a_Context += m_Position;
                    a_Context += m_Progress;
                    a_Context += m_Alignment;
                    a_Context += m_Size;
                    a_Context += m_Url;
                    a_Context += m_UrlInfo;
                    a_Context += m_UrlPreview;
                    a_Context += m_UrlSample;
                    a_Context += m_Value;
                    a_Context += m_Tml;
                    a_Context += "\n";
                    a_Context += m_StackTrace;
                }
                if (MP_STRING_EMPTY(m_Content) && (MP_STRING_EMPTY(a_Context) == false))
                {
                    a_Context =
                        __GetLevel(level) +
                        m_Content +
                        MP_STRING_SUBSTRING(a_Context, 1, MP_STRING_SIZE_GET(a_Context) - 1);
                }
                else
                {
                    a_Context =
                        __GetLevel(level) +
                        m_Content +
                        a_Context;
                }
                {
                    Clear();
                }
            }
            catch (MP_PTR(MP_EXCEPTION))
            {
                Clear();
            }
            {
                MP_THREAD_MUTEX_UNLOCK(__GetMutex());
            }
            {
                SendTml(a_Context);
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content)
{
    if ((this != nullptr) && (level >= 0))
    {
        return
            SetContent(content)->
            Send(source, event, level);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content, MP_STRING value)
{
    if ((this != nullptr) && (level >= 0))
    {
        return
            SetContent(content)->
            SetValue(value)->
            Send(source, event, level);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendTml(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        return __SendTml(MP_STRING_TRIMEND(value) + "\n");
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendTml(MP_STRING value, MP_STRING source)
{
    if ((this != nullptr) && (value != nullptr))
    {
        return __SendTml(__GetTml(value, source));
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendPreview(MP_STRING event, MP_STRING url)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Foreground))
        {
            this->
                SetForeground(CONSTANT::OUTPUT::PREVIEW_FOREGROUND);
        }
        {
            this->
                SetCommand(NAME::COMMAND::MESSAGE_RESEND, url)->
                Send(NAME::SOURCE::PREVIEW, event, 0);
        }
    }
    return this;
}

// Public ##############
MP_PTR(atom::Trace) atom::Trace::SetAlignment(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        m_Alignment = " @@@ALIGNMENT " + __GetFirstLine(value, false);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetAlignment(MP_STRING value1, MP_STRING value2)
{
    if ((this != nullptr) && (value1 != nullptr) && (value2 != nullptr))
    {
        m_Alignment = " @@@ALIGNMENT " + __GetFirstLine(value1, false) + " " + __GetFirstLine(value2, false);
        return this;
    }
    if ((this != nullptr) && (value1 != nullptr))
    {
        m_Alignment = " @@@ALIGNMENT " + __GetFirstLine(value1, false);
        return this;
    }
    if ((this != nullptr) && (value2 != nullptr))
    {
        m_Alignment = " @@@ALIGNMENT " + __GetFirstLine(value2, false);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetBackground(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Background = " @@@BACKGROUND " + __GetColor(value);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetBorder(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        m_Border = " @@@BORDER " + __GetColor(value);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCommand(MP_STRING name)
{
    if ((this != nullptr) && (name != nullptr))
    {
        auto a_Context = MP_STRING_UPPER(__GetFirstLine(name, false));
        if (a_Context == NAME::COMMAND::MESSAGE_STACKTRACE)
        {
            m_StackTrace = " ";
            return this;
        }
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Command += " @@@" + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCommand(MP_STRING name, MP_STRING value)
{
    if ((this != nullptr) && (name != nullptr))
    {
        auto a_Context = MP_STRING_UPPER(__GetFirstLine(name, false));
        if (a_Context == NAME::COMMAND::MESSAGE_STACKTRACE)
        {
            m_StackTrace = " ";
            return this;
        }
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            if (MP_STRING_EMPTY(value))
            {
                m_Command += " @@@" + a_Context;
            }
            else
            {
                m_Command += " @@@" + a_Context + " " + __GetFirstLine(value, false);
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetComment(MP_STRING value)
{
    return SetComment(value, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetComment(MP_STRING value, MP_STRING hint)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Comment = " @@@COMMENT " + a_Context;
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Comment += " @@@COMMENT.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCondition(MP_STRING name, MP_STRING variable, MP_STRING value)
{
    if ((this != nullptr) && (name != nullptr) && (variable != nullptr))
    {
        auto a_Name = __GetFirstLine(name, false);
        auto a_Context = __GetFirstLine(variable, false);
        if ((MP_STRING_EMPTY(a_Name) == false) && (MP_STRING_EMPTY(a_Context) == false))
        {
            m_Condition += " @@@CONDITION." + a_Name + " " + CONSTANT::TML::VARIABLE_BEGIN + a_Context + CONSTANT::TML::VARIABLE_END;
        }
        if (MP_STRING_EMPTY(value) == false)
        {
            m_Condition += " " + __GetMultiLine(value, false);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetContent(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetMultiLine(value, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Content = a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name)
{
    return SetControl(name, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name, MP_STRING hint)
{
    if ((this != nullptr) && (name != nullptr))
    {
        auto a_Context = __GetFirstLine(name, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Control = " @@@CONTROL " + a_Context;
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Control += " @@@CONTROL.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCount(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        m_Count = " @@@COUNT " + MP_CONVERT_STRING_FROM_INT(value, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetDate(MP_INT year, MP_INT month, MP_INT day)
{
    if (this != nullptr)
    {
        m_Date = " @@@DATE " +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(year, 2100)), 4) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(month, 12)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(day, 31)), 2);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetFontName(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_FontName = " @@@FONT.NAME " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetFontSize(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        m_FontSize = " @@@FONT.SIZE " + MP_CONVERT_STRING_FROM_INT(value, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetFontState(MP_STRING name)
{
    if ((this != nullptr) && (name != nullptr))
    {
        auto a_Context = __GetFirstLine(name, false);
        if (MP_STRING_EMPTY(a_Context))
        {
            m_FontState += " @@@FONT.STATE";
        }
        else
        {
            if (MP_STRING_CONTAINS(m_FontState, " " + a_Context) == false)
            {
                if (MP_STRING_EMPTY(m_FontState))
                {
                    m_FontState += " @@@FONT.STATE";
                }
                {
                    m_FontState += " " + a_Context;
                }
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetForeground(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Foreground = " @@@FOREGROUND " + __GetColor(value);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetPadding(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        m_Padding = " @@@PADDING " + value;
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetPipe(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Pipe = " @@@PIPE " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetPosition(MP_INT x, MP_INT y)
{
    if (this != nullptr)
    {
        m_Position = " @@@POSITION.X " + MP_CONVERT_STRING_FROM_INT(x, 0) + " @@@POSITION.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetProgress(MP_DOUBLE value)
{
    return SetProgress(value, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetProgress(MP_DOUBLE value, MP_STRING hint)
{
    if (this != nullptr)
    {
        m_Progress = " @@@PROGRESS " + MP_CONVERT_STRING_FROM_DOUBLE(value);
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        m_Progress += " @@@PROGRESS.HINT " + __GetMultiLine(hint, true);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetSize(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Size = " @@@SIZE " + MP_CONVERT_STRING_FROM_INT(value, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetSize(MP_INT x, MP_INT y)
{
    if (this != nullptr)
    {
        m_Size = " @@@SIZE.X " + MP_CONVERT_STRING_FROM_INT(x, 0) + " @@@SIZE.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT miliSecond)
{
    if (this != nullptr)
    {
        m_Time = " @@@TIME " +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(hour, 24)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(minute, 60)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(second, 60)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(miliSecond, 999)), 3);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTml(MP_STRING value)
{
    if (this != nullptr)
    {
        m_Tml = value != nullptr ? value : "";
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTransform(MP_STRING name, MP_STRING value)
{
    if ((this != nullptr) && (name != nullptr))
    {
        if (MP_STRING_EMPTY(m_Value))
        {
            m_Value = " @@@VALUE";
        }
        {
            m_Value = " @@" + name;
        }
        if (MP_STRING_EMPTY(value) == false)
        {
            m_Value = " " + __GetFirstLine(value, false);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTranslation(MP_STRING culture, MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(culture) == false) && (MP_STRING_EMPTY(value) == false))
    {
        if (MP_STRING_EMPTY(m_Value))
        {
            m_Value = " @@@VALUE";
        }
        {
            m_Value = " <<<" + culture + ">>> " + __GetFirstLine(value, false);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetUrl(MP_STRING value)
{
    return SetUrl(value, nullptr, -1, -1);
}

MP_PTR(atom::Trace) atom::Trace::SetUrl(MP_STRING value, MP_INT line, MP_INT position)
{
    return SetUrl(value, nullptr, line, position);
}

MP_PTR(atom::Trace) atom::Trace::SetUrl(MP_STRING value, MP_STRING hint)
{
    return SetUrl(value, hint, -1, -1);
}

MP_PTR(atom::Trace) atom::Trace::SetUrl(MP_STRING value, MP_STRING hint, MP_INT line, MP_INT position)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            {
                m_Url = " @@@URL ";
            }
            if ((line >= 0) && (position >= 0))
            {
                m_Url += "<<<" + MP_CONVERT_STRING_FROM_INT(line, 0) + ":" + MP_CONVERT_STRING_FROM_INT(position, 0) + ">>> ";
            }
            {
                m_Url += a_Context;
            }
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Url += " @@@URL.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetUrlInfo(MP_STRING value)
{
    return SetUrlInfo(value, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetUrlInfo(MP_STRING value, MP_STRING hint)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlInfo = " @@@URL.INFO " + a_Context;
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlInfo += " @@@URL.INFO.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetUrlPreview(MP_STRING value)
{
    return SetUrlPreview(value, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetUrlPreview(MP_STRING value, MP_STRING hint)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlInfo = " @@@URL.PREVIEW " + a_Context;
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlInfo += " @@@URL.PREVIEW.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetUrlSample(MP_STRING value)
{
    return SetUrlSample(value, nullptr);
}

MP_PTR(atom::Trace) atom::Trace::SetUrlSample(MP_STRING value, MP_STRING hint)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlSample = " @@@URL.SAMPLE " + a_Context;
        }
    }
    if ((this != nullptr) && (hint != nullptr))
    {
        auto a_Context = __GetMultiLine(hint, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlSample += " @@@URL.SAMPLE.HINT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetMultiLine(value, true);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Value = " @@@VALUE " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_PTR(MP_STREAM) value, MP_STRING format)
{
    if ((this != nullptr) && (value != nullptr))
    {
        MP_PTR(MP_STREAM) a_Context;
        {
            MP_STREAM_INITIALIZE(a_Context);
            MP_CONVERT_STREAM_TO_ZIP_STREAM(value, a_Context);
        }
        if (MP_STRING_EMPTY(format))
        {
            m_Value = " @@@VALUE.ZIP " + MP_CONVERT_STREAM_TO_BASE64(a_Context);
        }
        else
        {
            m_Value = " @@@VALUE.ZIP " + CONSTANT::TML::GROUP_BEGIN + format + CONSTANT::TML::GROUP_END + " " + MP_CONVERT_STREAM_TO_BASE64(a_Context);
        }
    }
    return this;
}

// Private #############
MP_PTR(atom::Trace) atom::Trace::__SendTml(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        {
            MP_THREAD_MUTEX_LOCK(__GetMutex());
        }
        try
        {
            s_TraceBuffer += value;
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
        }
        {
            MP_THREAD_MUTEX_UNLOCK(__GetMutex());
        }
        try
        {
            if (s_TraceThread == nullptr)
            {
                MP_THREAD_INITIALIZE(s_TraceThread, __ThreadExecute);
                MP_THREAD_NAME_SET(s_TraceThread, "METAOUTPUT.SEND");
                MP_THREAD_APARTMENT_SET(s_TraceThread, MP_THREAD_APARTMENT_STA);
                MP_THREAD_START(s_TraceThread, nullptr);
            }
        }
        catch (MP_PTR(MP_EXCEPTION) ex)
        {
            MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
        }
    }
    return this;
}

// Private #############
MP_PTR(MP_THREAD_MUTEX) atom::Trace::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, CONSTANT::PIPE::MUTEX, false);
    }
    return s_Mutex;
}

// Private #############
MP_STRING atom::Trace::__GetFirstLine(MP_STRING value, bool isAnyText)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = (MP_STRING)"";
        if ((MP_STRING_INDEXOF(value, "\r") >= 0) || (MP_STRING_INDEXOF(value, "\n") >= 0))
        {
            {
                MP_STRING_RESERVE_SET(a_Result, MP_STRING_SIZE_GET(value));
            }
            MP_FOREACH(auto, a_Context, value)
            {
                switch (a_Context)
                {
                case '\r':
                case '\n':
                    break;
                default:
                    a_Result += a_Context;
                    continue;
                }
                break;
            }
        }
        else
        {
            a_Result = value;
        }
        {
            a_Result = MP_STRING_TRIM(a_Result);
        }
        if (isAnyText)
        {
            return __GetText(a_Result);
        }
        return a_Result;
    }
    return "";
}

MP_STRING atom::Trace::__GetMultiLine(MP_STRING value, bool isAnyText)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = value;
        if (isAnyText)
        {
            return __GetText(a_Result);
        }
        if (MP_STRING_CONTAINS(a_Result, "\r") || MP_STRING_CONTAINS(a_Result, "\n"))
        {
            a_Result = MP_STRING_REPLACE(a_Result, "\r\n", CONSTANT::TML::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\r", CONSTANT::TML::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\n", CONSTANT::TML::NEW_LINE);
            a_Result = MP_STRING_TRIM(a_Result);
        }
        return a_Result;
    }
    return "";
}

MP_STRING atom::Trace::__GetEvent(MP_STRING value)
{
    if ((MP_STRING_EMPTY(value) == false))
    {
        return " @@@EVENT " + __GetFirstLine(value, false);
    }
    return "";
}

MP_STRING atom::Trace::__GetSource(MP_STRING value)
{
    if ((MP_STRING_EMPTY(value) == false))
    {
        return " @@@SOURCE " + __GetFirstLine(value, false);
    }
    return "";
}

MP_STRING atom::Trace::__GetColor(MP_INT value)
{
    if ((value & 0xFF000000) == 0)
    {
        return "TRANSPARENT";
    }
    else
    {
        auto a_Context = (MP_INT32)((value & 0x00FFFFFF) | 0xFF000000);
        {
            if (a_Context == NAME::COLOR::ALICE_BLUE) return "ALICE.BLUE";
            if (a_Context == NAME::COLOR::ANTIQUE_WHITE) return "ANTIQUE.WHITE";
            if (a_Context == NAME::COLOR::AQUA) return "AQUA";
            if (a_Context == NAME::COLOR::AQUAMARINE) return "AQUAMARINE";
            if (a_Context == NAME::COLOR::AZURE) return "AZURE";
            if (a_Context == NAME::COLOR::BEIGE) return "BEIGE";
            if (a_Context == NAME::COLOR::BISQUE) return "BISQUE";
            if (a_Context == NAME::COLOR::BLACK) return "BLACK";
            if (a_Context == NAME::COLOR::BLANCHED_ALMOND) return "BLANCHED.ALMOND";
            if (a_Context == NAME::COLOR::BLUE_VIOLET) return "BLUE.VIOLET";
            if (a_Context == NAME::COLOR::BLUE) return "BLUE";
            if (a_Context == NAME::COLOR::BROWN) return "BROWN";
            if (a_Context == NAME::COLOR::BURLY_WOOD) return "BURLY.WOOD";
            if (a_Context == NAME::COLOR::CADET_BLUE) return "CADET.BLUE";
            if (a_Context == NAME::COLOR::CHARTREUSE) return "CHARTREUSE";
            if (a_Context == NAME::COLOR::CHOCOLATE) return "CHOCOLATE";
            if (a_Context == NAME::COLOR::CORAL) return "CORAL";
            if (a_Context == NAME::COLOR::CORNFLOWER_BLUE) return "CORNFLOWER.BLUE";
            if (a_Context == NAME::COLOR::CORNSILK) return "CORNSILK";
            if (a_Context == NAME::COLOR::CRIMSON) return "CRIMSON";
            if (a_Context == NAME::COLOR::CYAN) return "CYAN";
            if (a_Context == NAME::COLOR::DARK_BLUE) return "DARK.BLUE";
            if (a_Context == NAME::COLOR::DARK_CYAN) return "DARK.CYAN";
            if (a_Context == NAME::COLOR::DARK_GOLDENROD) return "DARK.GOLDENROD";
            if (a_Context == NAME::COLOR::DARK_GRAY) return "DARK.GRAY";
            if (a_Context == NAME::COLOR::DARK_GREEN) return "DARK.GREEN";
            if (a_Context == NAME::COLOR::DARK_KHAKI) return "DARK.KHAKI";
            if (a_Context == NAME::COLOR::DARK_MAGENTA) return "DARK.MAGENTA";
            if (a_Context == NAME::COLOR::DARK_OLIVE_GREEN) return "DARK.OLIVE.GREEN";
            if (a_Context == NAME::COLOR::DARK_ORANGE) return "DARK.ORANGE";
            if (a_Context == NAME::COLOR::DARK_ORCHID) return "DARK.ORCHID";
            if (a_Context == NAME::COLOR::DARK_RED) return "DARK.RED";
            if (a_Context == NAME::COLOR::DARK_SALMON) return "DARK.SALMON";
            if (a_Context == NAME::COLOR::DARK_SEA_GREEN) return "DARK.SEA.GREEN";
            if (a_Context == NAME::COLOR::DARK_SLATE_BLUE) return "DARK.SLATE.BLUE";
            if (a_Context == NAME::COLOR::DARK_SLATE_GRAY) return "DARK.SLATE.GRAY";
            if (a_Context == NAME::COLOR::DARK_TURQUOISE) return "DARK.TURQUOISE";
            if (a_Context == NAME::COLOR::DARK_VIOLET) return "DARK.VIOLET";
            if (a_Context == NAME::COLOR::DEEP_PINK) return "DEEP.PINK";
            if (a_Context == NAME::COLOR::DEEP_SKY_BLUE) return "DEEP.SKY.BLUE";
            if (a_Context == NAME::COLOR::DIM_GRAY) return "DIM.GRAY";
            if (a_Context == NAME::COLOR::DODGER_BLUE) return "DODGER.BLUE";
            if (a_Context == NAME::COLOR::FIREBRICK) return "FIREBRICK";
            if (a_Context == NAME::COLOR::FLORAL_WHITE) return "FLORAL.WHITE";
            if (a_Context == NAME::COLOR::FOREST_GREEN) return "FOREST.GREEN";
            if (a_Context == NAME::COLOR::FUCHSIA) return "FUCHSIA";
            if (a_Context == NAME::COLOR::GAINSBORO) return "GAINSBORO";
            if (a_Context == NAME::COLOR::GHOST_WHITE) return "GHOST.WHITE";
            if (a_Context == NAME::COLOR::GOLD) return "GOLD";
            if (a_Context == NAME::COLOR::GOLDENROD) return "GOLDENROD";
            if (a_Context == NAME::COLOR::GRAY) return "GRAY";
            if (a_Context == NAME::COLOR::GREEN_YELLOW) return "GREEN.YELLOW";
            if (a_Context == NAME::COLOR::GREEN) return "GREEN";
            if (a_Context == NAME::COLOR::HONEYDEW) return "HONEYDEW";
            if (a_Context == NAME::COLOR::HOT_PINK) return "HOT.PINK";
            if (a_Context == NAME::COLOR::INDIAN_RED) return "INDIAN.RED";
            if (a_Context == NAME::COLOR::INDIGO) return "INDIGO";
            if (a_Context == NAME::COLOR::IVORY) return "IVORY";
            if (a_Context == NAME::COLOR::KHAKI) return "KHAKI";
            if (a_Context == NAME::COLOR::LAVENDER_BLUSH) return "LAVENDER.BLUSH";
            if (a_Context == NAME::COLOR::LAVENDER) return "LAVENDER";
            if (a_Context == NAME::COLOR::LAWN_GREEN) return "LAWN.GREEN";
            if (a_Context == NAME::COLOR::LEMON_CHIFFON) return "LEMON.CHIFFON";
            if (a_Context == NAME::COLOR::LIGHT_BLUE) return "LIGHT.BLUE";
            if (a_Context == NAME::COLOR::LIGHT_CORAL) return "LIGHT.CORAL";
            if (a_Context == NAME::COLOR::LIGHT_CYAN) return "LIGHT.CYAN";
            if (a_Context == NAME::COLOR::LIGHT_GOLDENROD_YELLOW) return "LIGHT.GOLDENROD.YELLOW";
            if (a_Context == NAME::COLOR::LIGHT_GRAY) return "LIGHT.GRAY";
            if (a_Context == NAME::COLOR::LIGHT_GREEN) return "LIGHT.GREEN";
            if (a_Context == NAME::COLOR::LIGHT_PINK) return "LIGHT.PINK";
            if (a_Context == NAME::COLOR::LIGHT_SALMON) return "LIGHT.SALMON";
            if (a_Context == NAME::COLOR::LIGHT_SEA_GREEN) return "LIGHT.SEA.GREEN";
            if (a_Context == NAME::COLOR::LIGHT_SKY_BLUE) return "LIGHT.SKY.BLUE";
            if (a_Context == NAME::COLOR::LIGHT_SLATE_GRAY) return "LIGHT.SLATE.GRAY";
            if (a_Context == NAME::COLOR::LIGHT_STEEL_BLUE) return "LIGHT.STEEL.BLUE";
            if (a_Context == NAME::COLOR::LIGHT_YELLOW) return "LIGHT.YELLOW";
            if (a_Context == NAME::COLOR::LIME_GREEN) return "LIME.GREEN";
            if (a_Context == NAME::COLOR::LIME) return "LIME";
            if (a_Context == NAME::COLOR::LINEN) return "LINEN";
            if (a_Context == NAME::COLOR::MAGENTA) return "MAGENTA";
            if (a_Context == NAME::COLOR::MAROON) return "MAROON";
            if (a_Context == NAME::COLOR::MEDIUM_AQUAMARINE) return "MEDIUM.AQUAMARINE";
            if (a_Context == NAME::COLOR::MEDIUM_BLUE) return "MEDIUM.BLUE";
            if (a_Context == NAME::COLOR::MEDIUM_ORCHID) return "MEDIUM.ORCHID";
            if (a_Context == NAME::COLOR::MEDIUM_PURPLE) return "MEDIUM.PURPLE";
            if (a_Context == NAME::COLOR::MEDIUM_SEA_GREEN) return "MEDIUM.SEA.GREEN";
            if (a_Context == NAME::COLOR::MEDIUM_SLATE_BLUE) return "MEDIUM.SLATE.BLUE";
            if (a_Context == NAME::COLOR::MEDIUM_SPRING_GREEN) return "MEDIUM.SPRING.GREEN";
            if (a_Context == NAME::COLOR::MEDIUM_TURQUOISE) return "MEDIUM.TURQUOISE";
            if (a_Context == NAME::COLOR::MEDIUM_VIOLET_RED) return "MEDIUM.VIOLET.RED";
            if (a_Context == NAME::COLOR::MIDNIGHT_BLUE) return "MIDNIGHT.BLUE";
            if (a_Context == NAME::COLOR::MINT_CREAM) return "MINT.CREAM";
            if (a_Context == NAME::COLOR::MISTY_ROSE) return "MISTY.ROSE";
            if (a_Context == NAME::COLOR::MOCCASIN) return "MOCCASIN";
            if (a_Context == NAME::COLOR::NAVAJO_WHITE) return "NAVAJO.WHITE";
            if (a_Context == NAME::COLOR::NAVY) return "NAVY";
            if (a_Context == NAME::COLOR::OLD_LACE) return "OLD.LACE";
            if (a_Context == NAME::COLOR::OLIVE_DRAB) return "OLIVE.DRAB";
            if (a_Context == NAME::COLOR::OLIVE) return "OLIVE";
            if (a_Context == NAME::COLOR::ORANGE_RED) return "ORANGE.RED";
            if (a_Context == NAME::COLOR::ORANGE) return "ORANGE";
            if (a_Context == NAME::COLOR::ORCHID) return "ORCHID";
            if (a_Context == NAME::COLOR::PALE_GOLDENROD) return "PALE.GOLDENROD";
            if (a_Context == NAME::COLOR::PALE_GREEN) return "PALE.GREEN";
            if (a_Context == NAME::COLOR::PALE_TURQUOISE) return "PALE.TURQUOISE";
            if (a_Context == NAME::COLOR::PALE_VIOLET_RED) return "PALE.VIOLET.RED";
            if (a_Context == NAME::COLOR::PAPAYA_WHIP) return "PAPAYA.WHIP";
            if (a_Context == NAME::COLOR::PEACH_PUFF) return "PEACH.PUFF";
            if (a_Context == NAME::COLOR::PERU) return "PERU";
            if (a_Context == NAME::COLOR::PINK) return "PINK";
            if (a_Context == NAME::COLOR::PLUM) return "PLUM";
            if (a_Context == NAME::COLOR::POWDER_BLUE) return "POWDER.BLUE";
            if (a_Context == NAME::COLOR::PURPLE) return "PURPLE";
            if (a_Context == NAME::COLOR::RED) return "RED";
            if (a_Context == NAME::COLOR::ROSY_BROWN) return "ROSY.BROWN";
            if (a_Context == NAME::COLOR::ROYAL_BLUE) return "ROYAL.BLUE";
            if (a_Context == NAME::COLOR::SADDLE_BROWN) return "SADDLE.BROWN";
            if (a_Context == NAME::COLOR::SALMON) return "SALMON";
            if (a_Context == NAME::COLOR::SANDY_BROWN) return "SANDY.BROWN";
            if (a_Context == NAME::COLOR::SEA_GREEN) return "SEA.GREEN";
            if (a_Context == NAME::COLOR::SEA_SHELL) return "SEA.SHELL";
            if (a_Context == NAME::COLOR::SIENNA) return "SIENNA";
            if (a_Context == NAME::COLOR::SILVER) return "SILVER";
            if (a_Context == NAME::COLOR::SKY_BLUE) return "SKY.BLUE";
            if (a_Context == NAME::COLOR::SLATE_BLUE) return "SLATE.BLUE";
            if (a_Context == NAME::COLOR::SLATE_GRAY) return "SLATE.GRAY";
            if (a_Context == NAME::COLOR::SNOW) return "SNOW";
            if (a_Context == NAME::COLOR::SPRING_GREEN) return "SPRING.GREEN";
            if (a_Context == NAME::COLOR::STEEL_BLUE) return "STEEL.BLUE";
            if (a_Context == NAME::COLOR::TAN) return "TAN";
            if (a_Context == NAME::COLOR::TEAL) return "TEAL";
            if (a_Context == NAME::COLOR::THISTLE) return "THISTLE";
            if (a_Context == NAME::COLOR::TOMATO) return "TOMATO";
            if (a_Context == NAME::COLOR::TURQUOISE) return "TURQUOISE";
            if (a_Context == NAME::COLOR::VIOLET) return "VIOLET";
            if (a_Context == NAME::COLOR::WHEAT) return "WHEAT";
            if (a_Context == NAME::COLOR::WHITE_SMOKE) return "WHITE.SMOKE";
            if (a_Context == NAME::COLOR::WHITE) return "WHITE";
            if (a_Context == NAME::COLOR::YELLOW_GREEN) return "YELLOW.GREEN";
            if (a_Context == NAME::COLOR::YELLOW) return "YELLOW";
        }
    }
    return "#" + MP_CONVERT_STRING_FROM_HEX(value & 0x00FFFFFF, 8);
}

MP_STRING atom::Trace::__GetLevel(MP_INT value)
{
    switch (value)
    {
    case 0: return "";
    case 1: return " ";
    case 2: return "  ";
    case 3: return "   ";
    case 4: return "    ";
    case 5: return "     ";
    case 6: return "      ";
    case 7: return "       ";
    case 8: return "        ";
    case 9: return "         ";
    }
    if (value >= 0)
    {
        auto a_Result = (MP_STRING)"";
        for (auto i = 0; i < value; i++)
        {
            a_Result += " ";
        }
        {
            return a_Result;
        }
    }
    return "";
}

MP_STRING atom::Trace::__GetTml(MP_STRING value, MP_STRING source)
{
    if ((MP_STRING_EMPTY(value) == false) && (MP_STRING_EMPTY(source) == false))
    {
        auto a_Context = value;
        if (MP_STRING_CONTAINS(a_Context, "\r\n"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\r\n", "\n");
        }
        if (MP_STRING_CONTAINS(a_Context, "\r"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\r", "\n");
        }
        if (MP_STRING_CONTAINS(a_Context, "\t"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\t", " ");
        }
        if (source == NAME::SOURCE::CONSOLE)
        {
            return MP_STRING_REPLACE(a_Context, "\n", " @@@SOURCE CONSOLE\n");
        }
        else
        {
            auto a_Result = (MP_STRING)"";
            {
                auto a_TextBuffer = MP_STRING_BUFFER_GET(a_Context);
                auto a_TextSize = MP_STRING_SIZE_GET(a_Context);
                auto a_Context1 = (MP_STRING)"";
                if (a_TextSize > CONSTANT::OUTPUT::MAX_BUFFER_SIZE)
                {
                    return "[[[Too big input]]] TML @@@SOURCE METAOUTPUT @@@EVENT CRITICAL";
                }
                if (a_TextSize > 0)
                {
                    MP_STRING_RESERVE_SET(a_Result, (a_TextSize * 2) + 1);
                    MP_STRING_RESERVE_SET(a_Context1, a_TextSize);
                }
                for (auto i = 0; i < a_TextSize; i++)
                {
                    auto a_Context2 = a_TextBuffer[i];
                    if ((a_Context2 == '\n') || ((i + 1) == a_TextSize))
                    {
                        if (MP_STRING_EMPTY(a_Context1))
                        {
                            continue;
                        }
                        if (a_Context2 != '\n')
                        {
                            a_Result += a_Context2;
                            a_Context1 += a_Context2;
                        }
                        if (MP_STRING_CONTAINS(a_Context1, "@@@SOURCE ") == false)
                        {
                            a_Result += " @@@SOURCE " + source;
                        }
                        if (a_Context2 == '\n')
                        {
                            a_Result += a_Context2;
                        }
                        {
                            a_Context1 = "";
                        }
                    }
                    else
                    {
                        a_Result += a_Context2;
                        a_Context1 += a_Context2;
                    }
                }
            }
            return a_Result;
        }
    }
    return value;
}

MP_STRING atom::Trace::__GetText(MP_STRING value)
{
    if (MP_STRING_CONTAINS(value, CONSTANT::TML::ATTRIBUTE))
    {
        return MP_STRING_REPLACE(value, CONSTANT::TML::ATTRIBUTE, "@" + CONSTANT::TML::GROUP_BEGIN + "@" + CONSTANT::TML::GROUP_END + "@");
    }
    return value;
}

MP_STRING atom::Trace::__GetFileName(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Result = GetUrlFinal(url);
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

MP_STRING atom::Trace::__GetProxyFolder()
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

// Private #############
void atom::Trace::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
{
    try
    {
        while (s_TraceThread != nullptr)
        {
            auto a_Context = (MP_STRING)"";
            {
                MP_UNUSED(sender);
            }
            {
                MP_THREAD_SLEEP(50);
                MP_THREAD_MUTEX_LOCK(__GetMutex());
            }
            {
                a_Context = s_TraceBuffer;
                s_TraceBuffer = "";
            }
            {
                MP_THREAD_MUTEX_UNLOCK(__GetMutex());
            }
            if (MP_STRING_EMPTY(a_Context))
            {
                break;
            }
            else
            {
                extension::AnyPipe::Send("", a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION))
    {
    }
    {
        s_TraceThread = nullptr;
    }
}
