
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

// Public ##############
MP_PTR(atom::Trace) atom::Trace::Clear()
{
    if (this != nullptr)
    {
        try
        {
            m_Alignment = "";
            m_Background = "";
            m_Command = "";
            m_Comment = "";
            m_Condition = "";
            m_Content = "";
            m_ContentHint = "";
            m_Control = "";
            m_Date = "";
            m_FontName = "";
            m_FontSize = "";
            m_FontState = "";
            m_Foreground = "";
            m_Progress = "";
            m_Size = "";
            m_StackTrace = "";
            m_Time = "";
            m_Url = "";
            m_UrlInfo = "";
            m_UrlPipe = "";
            m_UrlPreview = "";
            m_UrlSample = "";
            m_Value = "";
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING type, MP_INT level)
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
                    auto a_Count = extension::AnyPreview::GetProperty(extension::AnyPreview::NAME::PROPERTY::DEBUGGING_STACK_SIZE, true);
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
                                    " @@@TYPE " + NAME::TYPE::FUNCTION +
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
            catch (MP_PTR(MP_EXCEPTION))
            {
                m_StackTrace += "\n" + __GetLevel(level) + "[[[Stack trace not calculated correctly]]] @@@SOURCE DIAGNOSTIC @@@TYPE WARNING";
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
                    a_Context += __GetType(type);
                    a_Context += m_Command;
                    a_Context += m_ContentHint;
                    a_Context += m_Comment;
                    a_Context += m_Condition;
                    a_Context += m_Control;
                    a_Context += m_Date;
                    a_Context += m_Time;
                    a_Context += m_Background;
                    a_Context += m_Foreground;
                    a_Context += m_FontName;
                    a_Context += m_FontSize;
                    a_Context += m_FontState;
                    a_Context += m_Progress;
                    a_Context += m_Alignment;
                    a_Context += m_Size;
                    a_Context += m_Url;
                    a_Context += m_UrlInfo;
                    a_Context += m_UrlPipe;
                    a_Context += m_UrlPreview;
                    a_Context += m_UrlSample;
                    a_Context += m_Value;
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

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING type, MP_INT level, MP_STRING content)
{
    if ((this != nullptr) && (level >= 0))
    {
        return
            SetContent(content)->
            Send(source, type, level);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING type, MP_INT level, MP_STRING content, MP_STRING value)
{
    if ((this != nullptr) && (level >= 0))
    {
        return
            SetContent(content)->
            SetValue(value)->
            Send(source, type, level);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendTml(MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(value) == false))
    {
        return __SendTml(MP_STRING_TRIMEND(value) + "\n");
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendTml(MP_STRING value, MP_STRING source)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(value) == false))
    {
        return __SendTml(__GetTml(value, source));
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendPreview(MP_STRING type, MP_STRING url)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Foreground))
        {
            this->
                SetForeground(NAME::COLOR::TEAL);
        }
        {
            this->
                SetCommand(NAME::COMMAND::MESSAGE_RESEND, url)->
                Send(NAME::SOURCE::PREVIEW, type, 0);
        }
    }
    return this;
}

// Public ##############
MP_PTR(atom::Trace) atom::Trace::SetAlignment(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_Alignment = " @@@ALIGNMENT " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetBackground(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Background = " @@@BACKGROUND #" + MP_CONVERT_STRING_FROM_HEX(value, 8);
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
            m_Condition += " @@@CONDITION." + a_Name + " " + CONSTANT::VARIABLE_BEGIN + a_Context + CONSTANT::VARIABLE_END;
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
    if ((this != nullptr) && (value != 0))
    {
        m_FontSize = " @@@FONT.SIZE " + MP_CONVERT_STRING_FROM_INT(value, 0);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetFontState(MP_STRING name)
{
    if (this != nullptr)
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
        m_Foreground = " @@@FOREGROUND #" + MP_CONVERT_STRING_FROM_HEX(value, 8);
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
    if (this != nullptr)
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

MP_PTR(atom::Trace) atom::Trace::SetTransform(MP_STRING name, MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(name) == false))
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

MP_PTR(atom::Trace) atom::Trace::SetUrlPipe(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlPipe = " @@@PIPE " + a_Context;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetUrlPreview(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        auto a_Context = __GetFirstLine(value, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            m_UrlPreview = " @@@URL.PREVIEW " + a_Context;
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
            m_Value = " @@@VALUE.ZIP " + atom::Trace::CONSTANT::GROUP_BEGIN + format + atom::Trace::CONSTANT::GROUP_END + " " + MP_CONVERT_STREAM_TO_BASE64(a_Context);
        }
    }
    return this;
}

// Private #############
MP_PTR(atom::Trace) atom::Trace::__SendTml(MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(value) == false))
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
                MP_THREAD_START(s_TraceThread, nullptr);
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
        }
    }
    return this;
}

// Private #############
MP_PTR(MP_THREAD_MUTEX) atom::Trace::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, extension::AnyPreview::CONSTANT::OUTPUT_PIPE_MUTEX, false);
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
            a_Result = MP_STRING_REPLACE(a_Result, "\r\n", CONSTANT::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\r", CONSTANT::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\n", CONSTANT::NEW_LINE);
            a_Result = MP_STRING_TRIM(a_Result);
        }
        return a_Result;
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

MP_STRING atom::Trace::__GetType(MP_STRING value)
{
    if ((MP_STRING_EMPTY(value) == false))
    {
        return " @@@TYPE " + __GetFirstLine(value, false);
    }
    return "";
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
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\r\n", "\n");
            a_Context = MP_STRING_REPLACE(a_Context, "\r", "\n");
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
                {
                    MP_STRING_RESERVE_SET(a_Context1, a_TextSize);
                }
                for (auto i = 0; i < a_TextSize; i++)
                {
                    if ((a_TextBuffer[i] == '\n') || ((i + 1) == a_TextSize))
                    {
                        if (MP_STRING_EMPTY(a_Context1))
                        {
                            continue;
                        }
                        if (a_TextBuffer[i] != '\n')
                        {
                            a_Result += a_TextBuffer[i];
                        }
                        if (MP_STRING_CONTAINS(a_Context1, "@@@SOURCE ") == false)
                        {
                            a_Result += " @@@SOURCE " + source;
                        }
                        if (a_TextBuffer[i] == '\n')
                        {
                            a_Result += a_TextBuffer[i];
                        }
                        {
                            a_Context1 = "";
                        }
                    }
                    else
                    {
                        a_Result += a_TextBuffer[i];
                        a_Context1 += a_TextBuffer[i];
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
    if (MP_STRING_CONTAINS(value, CONSTANT::ATTRIBUTE))
    {
        return MP_STRING_REPLACE(value, CONSTANT::ATTRIBUTE, "@" + CONSTANT::GROUP_BEGIN + "@" + CONSTANT::GROUP_END + "@");
    }
    return value;
}

// Private #############
void atom::Trace::MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender)
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
    if (MP_STRING_EMPTY(a_Context) == false)
    {
        try
        {
            if (extension::AnyPreview::Send(a_Context) == false)
            {
                {
                    MP_THREAD_MUTEX_LOCK(__GetMutex());
                }
                {
                    s_TraceBuffer = a_Context + s_TraceBuffer;
                }
                {
                    MP_THREAD_MUTEX_UNLOCK(__GetMutex());
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
        }
    }
    {
        s_TraceThread = nullptr;
    }
}
