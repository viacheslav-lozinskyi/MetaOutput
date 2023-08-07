
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) atom::Trace::s_Mutex = nullptr;
MP_PTR(MP_MAP(MP_PTR(Trace))) atom::Trace::s_Instances = nullptr;
MP_PTR(MP_THREAD) atom::Trace::s_TraceThread = nullptr;
MP_STRING atom::Trace::s_TraceBuffer = nullptr;
#endif

// atom::Trace ################################################################
atom::Trace::Trace()
{
    m_Transaction = 0;
    m_Queue = "";
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

MP_STRING atom::Trace::GetAttribute(MP_STRING value, MP_STRING name)
{
    try
    {
        auto a_Context = value;
        {
            auto a_Index = MP_STRING_INDEXOF(a_Context, CONSTANT::TML::COMMENT);
            if (a_Index >= 0)
            {
                if (a_Index > 0)
                {
                    a_Index = (a_Context[a_Index - 1] == '/') ? -1 : a_Index;
                }
                if (a_Index >= 0)
                {
                    a_Context = MP_STRING_SUBSTRING(a_Context, 0, a_Index);
                }
            }
        }
        if (MP_STRING_CONTAINS(a_Context, "\t"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\t", " ");
        }
        if (MP_STRING_CONTAINS(a_Context, "\r"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\r", " ");
        }
        if (MP_STRING_CONTAINS(a_Context, "\n"))
        {
            a_Context = MP_STRING_REPLACE(a_Context, "\n", " ");
        }
        {
            auto a_Index = MP_STRING_INDEXOF(MP_STRING_UPPER(a_Context), CONSTANT::TML::ATTRIBUTE + MP_STRING_UPPER(name) + " ");
            if (a_Index >= 0)
            {
                auto a_Result = (MP_STRING)"";
                auto a_Size = MP_STRING_SIZE_GET(CONSTANT::TML::ATTRIBUTE + name);
                auto a_Index1 = MP_STRING_INDEXFROM(MP_STRING_UPPER(a_Context), CONSTANT::TML::ATTRIBUTE, a_Index + a_Size);
                if (a_Index1 < 0)
                {
                    a_Result = MP_STRING_TRIM(MP_STRING_SUBSTRING(a_Context, a_Index + a_Size, MP_STRING_SIZE_GET(a_Context) - a_Index - a_Size));
                }
                else
                {
                    a_Result = MP_STRING_TRIM(MP_STRING_SUBSTRING(a_Context, a_Index + a_Size, a_Index1 - a_Index - a_Size));
                }
                if (MP_STRING_CONTAINS(a_Result, CONSTANT::TML::NEW_LINE))
                {
                    a_Result = MP_STRING_REPLACE(a_Result, CONSTANT::TML::NEW_LINE, "\r\n");
                }
                return a_Result;
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
    return "";
}

MP_STRING atom::Trace::GetFirstLine(MP_STRING value, bool isAnyText)
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

MP_STRING atom::Trace::GetMultiLine(MP_STRING value, bool isAnyText)
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

MP_STRING atom::Trace::GetUrlTemp(MP_STRING url)
{
    return GetUrlTemp(url, "");
}

MP_STRING atom::Trace::GetUrlTemp(MP_STRING url, MP_STRING extension)
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
                a_Context = MP_STRING_TRIM(a_Context);
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
        m_Background = "";
        m_Command = "";
        m_Comment = "";
        m_Condition = "";
        m_Content = "";
        m_Control = "";
        m_Count = "";
        m_Date = "";
        m_Flag = "";
        m_Font = "";
        m_Foreground = "";
        m_Progress = "";
        m_Time = "";
        m_Tml = "";
        m_Trace = "";
        m_Url = "";
        m_UrlInfo = "";
        m_UrlPreview = "";
        m_UrlSample = "";
        m_Value = "";
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::BeginTransaction()
{
    if (this != nullptr)
    {
        m_Transaction++;
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::CancelTransaction()
{
    if (this != nullptr)
    {
        m_Transaction = 0;
        m_Queue = "";
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::EndTransaction()
{
    if (this != nullptr)
    {
        {
            m_Transaction--;
        }
        if (m_Transaction <= 0)
        {
            auto a_Context = m_Queue;
            {
                m_Transaction = 0;
                m_Queue = "";
            }
            {
                SendTml(a_Context);
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::Send(MP_STRING source, MP_STRING event, MP_INT level)
{
    if (this != nullptr)
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
                a_Context += m_Comment;
                a_Context += m_Condition;
                a_Context += m_Control;
                a_Context += m_Count;
                a_Context += m_Date;
                a_Context += m_Time;
                a_Context += m_Background;
                a_Context += m_Foreground;
                a_Context += m_Flag;
                a_Context += m_Font;
                a_Context += m_Progress;
                a_Context += m_Trace;
                a_Context += m_Url;
                a_Context += m_UrlInfo;
                a_Context += m_UrlPreview;
                a_Context += m_UrlSample;
                a_Context += m_Value;
                a_Context += m_Tml;
                a_Context += "\n";
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
            if ((level == 0) && (source == NAME::SOURCE::DIAGNOSTIC))
            {
                a_Context += __GetStackTrace(source, level + 1, 2);
            }
            {
                m_Queue += a_Context;
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            // Any exceptions here may be ignored
        }
        {
            MP_THREAD_MUTEX_UNLOCK(__GetMutex());
        }
        if (m_Transaction == 0)
        {
            Clear();
            EndTransaction();
        }
        else
        {
            Clear();
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
        {
            MP_THREAD_MUTEX_LOCK(__GetMutex());
        }
        try
        {
            s_TraceBuffer += value + "\n";
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            // Any exceptions here may be ignored
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

MP_PTR(atom::Trace) atom::Trace::SendTml(MP_STRING value, MP_STRING source)
{
    if ((this != nullptr) && (value != nullptr))
    {
        return atom::Trace::SendTml(__GetTml(value, source));
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
                SetForeground(CONSTANT::UI::PREVIEW::FOREGROUND);
        }
        {
            this->
                SetTrace(url, NAME::STATE::TRACE::RESEND | NAME::STATE::TRACE::EXPAND)->
                Send(NAME::SOURCE::PREVIEW, event, 0);
        }
    }
    return this;
}

// Public ##############
MP_PTR(atom::Trace) atom::Trace::SetAlignment(MP_INT value)
{
    if ((this != nullptr) && (value != NAME::STATE::FONT::NONE))
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            {
                m_Control += " @@ALIGNMENT";
            }
            {
                if ((value & NAME::ALIGNMENT::CLIENT) == NAME::ALIGNMENT::CLIENT) m_Control += " CLIENT";
                if ((value & NAME::ALIGNMENT::CENTER) == NAME::ALIGNMENT::CENTER) m_Control += " CENTER";
                if ((value & NAME::ALIGNMENT::LEFT) == NAME::ALIGNMENT::LEFT) m_Control += " LEFT";
                if ((value & NAME::ALIGNMENT::TOP) == NAME::ALIGNMENT::TOP) m_Control += " TOP";
                if ((value & NAME::ALIGNMENT::RIGHT) == NAME::ALIGNMENT::RIGHT) m_Control += " RIGHT";
                if ((value & NAME::ALIGNMENT::BOTTOM) == NAME::ALIGNMENT::BOTTOM) m_Control += " BOTTOM";
            }
        }
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

MP_PTR(atom::Trace) atom::Trace::SetCommand(MP_STRING name, MP_STRING value)
{
    if ((this != nullptr) && (name != nullptr))
    {
        auto a_Context = GetFirstLine(name, false);
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            if (MP_STRING_EMPTY(value))
            {
                m_Command += " @@@" + a_Context;
            }
            else
            {
                m_Command += " @@@" + a_Context + " " + GetFirstLine(value, false);
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
        {
            m_Comment = " @@@COMMENT " + GetFirstLine(value, true);
        }
        if (hint != nullptr)
        {
            m_Comment += " @@HINT " + GetMultiLine(hint, true);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCondition(MP_STRING name, MP_STRING value1, MP_STRING value2)
{
    if ((this != nullptr) && (name != nullptr))
    {
        {
            auto a_Context = GetFirstLine(name, false);
            if (MP_STRING_EMPTY(a_Context) == false)
            {
                m_Condition += " @@@CONDITION " + a_Context;
            }
        }
        {
            auto a_Context = GetMultiLine(value1, false);
            if (MP_STRING_EMPTY(a_Context) == false)
            {
                m_Condition += " @@VALUE1 " + a_Context;
            }
        }
        {
            auto a_Context = GetMultiLine(value2, false);
            if (MP_STRING_EMPTY(a_Context) == false)
            {
                m_Condition += " @@VALUE2 " + a_Context;
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetContent(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        m_Content = GetMultiLine(value, true);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name)
{
    return SetControl(name, nullptr, nullptr, NAME::STATE::CONTROL::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name, MP_STRING hint)
{
    return SetControl(name, hint, nullptr, NAME::STATE::CONTROL::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name, MP_STRING hint, MP_STRING pipe, MP_INT state)
{
    if ((this != nullptr) && (name != nullptr))
    {
        {
            m_Control = " @@@CONTROL " + GetFirstLine(name, false);
        }
        if (hint != nullptr)
        {
            m_Control += " @@HINT " + GetMultiLine(hint, true);
        }
        if (pipe != nullptr)
        {
            m_Control += " @@PIPE " + GetFirstLine(pipe, false);
        }
        if (state != NAME::STATE::CONTROL::NONE)
        {
            {
                m_Control += " @@STATE";
            }
            {
                if ((state & NAME::STATE::CONTROL::BLINK) == NAME::STATE::CONTROL::BLINK) m_Control += " BLINK";
                if ((state & NAME::STATE::CONTROL::BLUR) == NAME::STATE::CONTROL::BLUR) m_Control += " BLUR";
                if ((state & NAME::STATE::CONTROL::DISABLED) == NAME::STATE::CONTROL::DISABLED) m_Control += " DISABLED";
                if ((state & NAME::STATE::CONTROL::INFINITE) == NAME::STATE::CONTROL::INFINITE) m_Control += " INFINITE";
                if ((state & NAME::STATE::CONTROL::MUTE) == NAME::STATE::CONTROL::MUTE) m_Control += " MUTE";
            }
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

MP_PTR(atom::Trace) atom::Trace::SetFont(MP_STRING name, MP_INT size)
{
    return SetFont(name, size, NAME::STATE::TRACE::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetFont(MP_STRING name, MP_INT size, MP_INT state)
{
    if (this != nullptr)
    {
        {
            m_Font = " @@@FONT";
        }
        if (MP_STRING_EMPTY(name) == false)
        {
            m_Font += " " + GetFirstLine(name, false);
        }
        if (size > 0)
        {
            m_Font += " @@SIZE " + MP_CONVERT_STRING_FROM_INT(size, 0);
        }
        if (state != NAME::STATE::FONT::NONE)
        {
            {
                m_Font += " @@STATE";
            }
            {
                if ((state & NAME::STATE::FONT::BOLD) == NAME::STATE::FONT::BOLD) m_Font += " BOLD";
                if ((state & NAME::STATE::FONT::ITALIC) == NAME::STATE::FONT::ITALIC) m_Font += " ITALIC";
                if ((state & NAME::STATE::FONT::STRIKEOUT) == NAME::STATE::FONT::STRIKEOUT) m_Font += " STRIKEOUT";
                if ((state & NAME::STATE::FONT::UNDERSCORE) == NAME::STATE::FONT::UNDERSCORE) m_Font += " UNDERSCORE";
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

MP_PTR(atom::Trace) atom::Trace::SetMargin(MP_INT x, MP_INT y)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " @@MARGIN.X " + MP_CONVERT_STRING_FROM_INT(x, 0);
            m_Control += " @@MARGIN.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetPadding(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " @@PADDING " + MP_CONVERT_STRING_FROM_INT(value, 0);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetPadding(MP_INT minX, MP_INT minY, MP_INT maxX, MP_INT maxY)
{
    if ((this != nullptr) && ((minX > 0) || (minY > 0) || (maxX > 0) || (maxY > 0)))
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " @@PADDING.MIN.X " + MP_CONVERT_STRING_FROM_INT(minX, 0);
            m_Control += " @@PADDING.MIN.Y " + MP_CONVERT_STRING_FROM_INT(minY, 0);
            m_Control += " @@PADDING.MAX.X " + MP_CONVERT_STRING_FROM_INT(maxX, 0);
            m_Control += " @@PADDING.MAX.Y " + MP_CONVERT_STRING_FROM_INT(maxY, 0);
        }
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
        {
            m_Progress = " @@@PROGRESS " + MP_CONVERT_STRING_FROM_DOUBLE(value);
        }
        if (hint != nullptr)
        {
            m_Progress += " @@HINT " + GetMultiLine(hint, true);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetSize(MP_INT x, MP_INT y)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " @@SIZE.X " + MP_CONVERT_STRING_FROM_INT(x, 0);
            m_Control += " @@SIZE.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond)
{
    if (this != nullptr)
    {
        m_Time = " @@@TIME " +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(hour, 24)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(minute, 60)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(second, 60)), 2) + "." +
            MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(milliSecond, 999)), 3);
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

MP_PTR(atom::Trace) atom::Trace::SetTrace(MP_STRING id, MP_INT state)
{
    if (this != nullptr)
    {
        {
            m_Trace = " @@@TRACE " + id;
        }
        if (state != NAME::STATE::TRACE::NONE)
        {
            {
                m_Trace += " @@STATE";
            }
            {
                if ((state & NAME::STATE::TRACE::BEEP) == NAME::STATE::TRACE::BEEP) m_Trace += " BEEP";
                if ((state & NAME::STATE::TRACE::BLINK) == NAME::STATE::TRACE::BLINK) m_Trace += " BLINK";
                if ((state & NAME::STATE::TRACE::CLEAR) == NAME::STATE::TRACE::CLEAR) m_Trace += " CLEAR";
                if ((state & NAME::STATE::TRACE::COLLAPSE) == NAME::STATE::TRACE::COLLAPSE) m_Trace += " COLLAPSE";
                if ((state & NAME::STATE::TRACE::EXPAND) == NAME::STATE::TRACE::EXPAND) m_Trace += " EXPAND";
                if ((state & NAME::STATE::TRACE::FIX) == NAME::STATE::TRACE::FIX) m_Trace += " FIX";
                if ((state & NAME::STATE::TRACE::FOCUS) == NAME::STATE::TRACE::FOCUS) m_Trace += " FOCUS";
                if ((state & NAME::STATE::TRACE::HIDE) == NAME::STATE::TRACE::HIDE) m_Trace += " HIDE";
                if ((state & NAME::STATE::TRACE::LOCK) == NAME::STATE::TRACE::LOCK) m_Trace += " LOCK";
                if ((state & NAME::STATE::TRACE::MUTE) == NAME::STATE::TRACE::MUTE) m_Trace += " MUTE";
                if ((state & NAME::STATE::TRACE::PIN) == NAME::STATE::TRACE::PIN) m_Trace += " PIN";
                if ((state & NAME::STATE::TRACE::REMOVE) == NAME::STATE::TRACE::REMOVE) m_Trace += " REMOVE";
                if ((state & NAME::STATE::TRACE::RESEND) == NAME::STATE::TRACE::RESEND) m_Trace += " RESEND";
                if ((state & NAME::STATE::TRACE::SHOW) == NAME::STATE::TRACE::SHOW) m_Trace += " SHOW";
                if ((state & NAME::STATE::TRACE::SPEAK) == NAME::STATE::TRACE::SPEAK) m_Trace += " SPEAK";
                if ((state & NAME::STATE::TRACE::UNFIX) == NAME::STATE::TRACE::UNFIX) m_Trace += " UNFIX";
                if ((state & NAME::STATE::TRACE::UNFOCUS) == NAME::STATE::TRACE::UNFOCUS) m_Trace += " UNFOCUS";
                if ((state & NAME::STATE::TRACE::UNLOCK) == NAME::STATE::TRACE::UNLOCK) m_Trace += " UNLOCK";
                if ((state & NAME::STATE::TRACE::UNPIN) == NAME::STATE::TRACE::UNPIN) m_Trace += " UNPIN";
                if ((state & NAME::STATE::TRACE::UPDATE) == NAME::STATE::TRACE::UPDATE) m_Trace += " UPDATE";
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTranslation(MP_STRING culture, MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(culture) == false) && (MP_STRING_EMPTY(value) == false))
    {
        m_Value += " @@@TRANSLATION.APPEND " + culture + " @@VALUE " + GetFirstLine(value, false);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTransparency(MP_DOUBLE value)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " @@TRANSPARENCY " + MP_CONVERT_STRING_FROM_DOUBLE(value);
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
    if (this != nullptr)
    {
        {
            m_Url = " @@@URL " + GetFirstLine(value, false);
        }
        if (line >= 0)
        {
            m_Url += " @@LINE " + MP_CONVERT_STRING_FROM_INT(line, 0);
        }
        if (position >= 0)
        {
            m_Url += " @@POSITION " + MP_CONVERT_STRING_FROM_INT(position, 0);
        }
        if (hint != nullptr)
        {
            m_Url += " @@HINT " + GetMultiLine(hint, true);
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
        {
            m_UrlInfo = " @@@URL.INFO " + GetFirstLine(value, false);
        }
        if (hint != nullptr)
        {
            m_UrlInfo += " @@HINT " + GetMultiLine(hint, true);
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
        {
            m_UrlPreview = " @@@URL.PREVIEW " + GetFirstLine(value, false);
        }
        if (hint != nullptr)
        {
            m_UrlPreview += " @@HINT " + GetMultiLine(hint, true);
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
        {
            m_UrlSample = " @@@URL.SAMPLE " + GetFirstLine(value, false);
        }
        if (hint != nullptr)
        {
            m_UrlSample += " @@HINT " + GetMultiLine(hint, true);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        m_Value = " @@@VALUE " + GetMultiLine(value, true);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_STRING value, MP_STRING type)
{
    if ((this != nullptr) && (value != nullptr))
    {
        if (MP_STRING_EMPTY(type))
        {
            m_Value = " @@@VALUE @@BASE64 " + value;
        }
        else
        {
            m_Value = " @@@VALUE @@TYPE " + type + " @@BASE64 " + value;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_PTR(MP_STREAM) value, MP_STRING type)
{
    if ((this != nullptr) && (value != nullptr))
    {
        if (MP_STRING_EMPTY(type))
        {
            m_Value = " @@@VALUE @@BASE64 " + MP_CONVERT_STREAM_TO_BASE64(value);
        }
        else
        {
            m_Value = " @@@VALUE @@TYPE " + type + " @@BASE64 " + MP_CONVERT_STREAM_TO_BASE64(value);
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
MP_STRING atom::Trace::__GetEvent(MP_STRING value)
{
    if ((MP_STRING_EMPTY(value) == false))
    {
        return " @@@EVENT " + GetFirstLine(value, false);
    }
    return "";
}

MP_STRING atom::Trace::__GetSource(MP_STRING value)
{
    if ((MP_STRING_EMPTY(value) == false))
    {
        return " @@@SOURCE " + GetFirstLine(value, false);
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
        if (value == NAME::COLOR::ALICE_BLUE) return "ALICE.BLUE";
        if (value == NAME::COLOR::ANTIQUE_WHITE) return "ANTIQUE.WHITE";
        if (value == NAME::COLOR::AQUA) return "AQUA";
        if (value == NAME::COLOR::AQUAMARINE) return "AQUAMARINE";
        if (value == NAME::COLOR::AZURE) return "AZURE";
        if (value == NAME::COLOR::BEIGE) return "BEIGE";
        if (value == NAME::COLOR::BISQUE) return "BISQUE";
        if (value == NAME::COLOR::BLACK) return "BLACK";
        if (value == NAME::COLOR::BLANCHED_ALMOND) return "BLANCHED.ALMOND";
        if (value == NAME::COLOR::BLUE_VIOLET) return "BLUE.VIOLET";
        if (value == NAME::COLOR::BLUE) return "BLUE";
        if (value == NAME::COLOR::BROWN) return "BROWN";
        if (value == NAME::COLOR::BURLY_WOOD) return "BURLY.WOOD";
        if (value == NAME::COLOR::CADET_BLUE) return "CADET.BLUE";
        if (value == NAME::COLOR::CHARTREUSE) return "CHARTREUSE";
        if (value == NAME::COLOR::CHOCOLATE) return "CHOCOLATE";
        if (value == NAME::COLOR::CORAL) return "CORAL";
        if (value == NAME::COLOR::CORNFLOWER_BLUE) return "CORNFLOWER.BLUE";
        if (value == NAME::COLOR::CORNSILK) return "CORNSILK";
        if (value == NAME::COLOR::CRIMSON) return "CRIMSON";
        if (value == NAME::COLOR::CYAN) return "CYAN";
        if (value == NAME::COLOR::DARK_BLUE) return "DARK.BLUE";
        if (value == NAME::COLOR::DARK_CYAN) return "DARK.CYAN";
        if (value == NAME::COLOR::DARK_GOLDENROD) return "DARK.GOLDENROD";
        if (value == NAME::COLOR::DARK_GRAY) return "DARK.GRAY";
        if (value == NAME::COLOR::DARK_GREEN) return "DARK.GREEN";
        if (value == NAME::COLOR::DARK_KHAKI) return "DARK.KHAKI";
        if (value == NAME::COLOR::DARK_MAGENTA) return "DARK.MAGENTA";
        if (value == NAME::COLOR::DARK_OLIVE_GREEN) return "DARK.OLIVE.GREEN";
        if (value == NAME::COLOR::DARK_ORANGE) return "DARK.ORANGE";
        if (value == NAME::COLOR::DARK_ORCHID) return "DARK.ORCHID";
        if (value == NAME::COLOR::DARK_RED) return "DARK.RED";
        if (value == NAME::COLOR::DARK_SALMON) return "DARK.SALMON";
        if (value == NAME::COLOR::DARK_SEA_GREEN) return "DARK.SEA.GREEN";
        if (value == NAME::COLOR::DARK_SLATE_BLUE) return "DARK.SLATE.BLUE";
        if (value == NAME::COLOR::DARK_SLATE_GRAY) return "DARK.SLATE.GRAY";
        if (value == NAME::COLOR::DARK_TURQUOISE) return "DARK.TURQUOISE";
        if (value == NAME::COLOR::DARK_VIOLET) return "DARK.VIOLET";
        if (value == NAME::COLOR::DEEP_PINK) return "DEEP.PINK";
        if (value == NAME::COLOR::DEEP_SKY_BLUE) return "DEEP.SKY.BLUE";
        if (value == NAME::COLOR::DIM_GRAY) return "DIM.GRAY";
        if (value == NAME::COLOR::DODGER_BLUE) return "DODGER.BLUE";
        if (value == NAME::COLOR::FIREBRICK) return "FIREBRICK";
        if (value == NAME::COLOR::FLORAL_WHITE) return "FLORAL.WHITE";
        if (value == NAME::COLOR::FOREST_GREEN) return "FOREST.GREEN";
        if (value == NAME::COLOR::FUCHSIA) return "FUCHSIA";
        if (value == NAME::COLOR::GAINSBORO) return "GAINSBORO";
        if (value == NAME::COLOR::GHOST_WHITE) return "GHOST.WHITE";
        if (value == NAME::COLOR::GOLD) return "GOLD";
        if (value == NAME::COLOR::GOLDENROD) return "GOLDENROD";
        if (value == NAME::COLOR::GRAY) return "GRAY";
        if (value == NAME::COLOR::GREEN_YELLOW) return "GREEN.YELLOW";
        if (value == NAME::COLOR::GREEN) return "GREEN";
        if (value == NAME::COLOR::HONEYDEW) return "HONEYDEW";
        if (value == NAME::COLOR::HOT_PINK) return "HOT.PINK";
        if (value == NAME::COLOR::INDIAN_RED) return "INDIAN.RED";
        if (value == NAME::COLOR::INDIGO) return "INDIGO";
        if (value == NAME::COLOR::IVORY) return "IVORY";
        if (value == NAME::COLOR::KHAKI) return "KHAKI";
        if (value == NAME::COLOR::LAVENDER_BLUSH) return "LAVENDER.BLUSH";
        if (value == NAME::COLOR::LAVENDER) return "LAVENDER";
        if (value == NAME::COLOR::LAWN_GREEN) return "LAWN.GREEN";
        if (value == NAME::COLOR::LEMON_CHIFFON) return "LEMON.CHIFFON";
        if (value == NAME::COLOR::LIGHT_BLUE) return "LIGHT.BLUE";
        if (value == NAME::COLOR::LIGHT_CORAL) return "LIGHT.CORAL";
        if (value == NAME::COLOR::LIGHT_CYAN) return "LIGHT.CYAN";
        if (value == NAME::COLOR::LIGHT_GOLDENROD_YELLOW) return "LIGHT.GOLDENROD.YELLOW";
        if (value == NAME::COLOR::LIGHT_GRAY) return "LIGHT.GRAY";
        if (value == NAME::COLOR::LIGHT_GREEN) return "LIGHT.GREEN";
        if (value == NAME::COLOR::LIGHT_PINK) return "LIGHT.PINK";
        if (value == NAME::COLOR::LIGHT_SALMON) return "LIGHT.SALMON";
        if (value == NAME::COLOR::LIGHT_SEA_GREEN) return "LIGHT.SEA.GREEN";
        if (value == NAME::COLOR::LIGHT_SKY_BLUE) return "LIGHT.SKY.BLUE";
        if (value == NAME::COLOR::LIGHT_SLATE_GRAY) return "LIGHT.SLATE.GRAY";
        if (value == NAME::COLOR::LIGHT_STEEL_BLUE) return "LIGHT.STEEL.BLUE";
        if (value == NAME::COLOR::LIGHT_YELLOW) return "LIGHT.YELLOW";
        if (value == NAME::COLOR::LIME_GREEN) return "LIME.GREEN";
        if (value == NAME::COLOR::LIME) return "LIME";
        if (value == NAME::COLOR::LINEN) return "LINEN";
        if (value == NAME::COLOR::MAGENTA) return "MAGENTA";
        if (value == NAME::COLOR::MAROON) return "MAROON";
        if (value == NAME::COLOR::MEDIUM_AQUAMARINE) return "MEDIUM.AQUAMARINE";
        if (value == NAME::COLOR::MEDIUM_BLUE) return "MEDIUM.BLUE";
        if (value == NAME::COLOR::MEDIUM_ORCHID) return "MEDIUM.ORCHID";
        if (value == NAME::COLOR::MEDIUM_PURPLE) return "MEDIUM.PURPLE";
        if (value == NAME::COLOR::MEDIUM_SEA_GREEN) return "MEDIUM.SEA.GREEN";
        if (value == NAME::COLOR::MEDIUM_SLATE_BLUE) return "MEDIUM.SLATE.BLUE";
        if (value == NAME::COLOR::MEDIUM_SPRING_GREEN) return "MEDIUM.SPRING.GREEN";
        if (value == NAME::COLOR::MEDIUM_TURQUOISE) return "MEDIUM.TURQUOISE";
        if (value == NAME::COLOR::MEDIUM_VIOLET_RED) return "MEDIUM.VIOLET.RED";
        if (value == NAME::COLOR::MIDNIGHT_BLUE) return "MIDNIGHT.BLUE";
        if (value == NAME::COLOR::MINT_CREAM) return "MINT.CREAM";
        if (value == NAME::COLOR::MISTY_ROSE) return "MISTY.ROSE";
        if (value == NAME::COLOR::MOCCASIN) return "MOCCASIN";
        if (value == NAME::COLOR::NAVAJO_WHITE) return "NAVAJO.WHITE";
        if (value == NAME::COLOR::NAVY) return "NAVY";
        if (value == NAME::COLOR::OLD_LACE) return "OLD.LACE";
        if (value == NAME::COLOR::OLIVE_DRAB) return "OLIVE.DRAB";
        if (value == NAME::COLOR::OLIVE) return "OLIVE";
        if (value == NAME::COLOR::ORANGE_RED) return "ORANGE.RED";
        if (value == NAME::COLOR::ORANGE) return "ORANGE";
        if (value == NAME::COLOR::ORCHID) return "ORCHID";
        if (value == NAME::COLOR::PALE_GOLDENROD) return "PALE.GOLDENROD";
        if (value == NAME::COLOR::PALE_GREEN) return "PALE.GREEN";
        if (value == NAME::COLOR::PALE_TURQUOISE) return "PALE.TURQUOISE";
        if (value == NAME::COLOR::PALE_VIOLET_RED) return "PALE.VIOLET.RED";
        if (value == NAME::COLOR::PAPAYA_WHIP) return "PAPAYA.WHIP";
        if (value == NAME::COLOR::PEACH_PUFF) return "PEACH.PUFF";
        if (value == NAME::COLOR::PERU) return "PERU";
        if (value == NAME::COLOR::PINK) return "PINK";
        if (value == NAME::COLOR::PLUM) return "PLUM";
        if (value == NAME::COLOR::POWDER_BLUE) return "POWDER.BLUE";
        if (value == NAME::COLOR::PURPLE) return "PURPLE";
        if (value == NAME::COLOR::RED) return "RED";
        if (value == NAME::COLOR::ROSY_BROWN) return "ROSY.BROWN";
        if (value == NAME::COLOR::ROYAL_BLUE) return "ROYAL.BLUE";
        if (value == NAME::COLOR::SADDLE_BROWN) return "SADDLE.BROWN";
        if (value == NAME::COLOR::SALMON) return "SALMON";
        if (value == NAME::COLOR::SANDY_BROWN) return "SANDY.BROWN";
        if (value == NAME::COLOR::SEA_GREEN) return "SEA.GREEN";
        if (value == NAME::COLOR::SEA_SHELL) return "SEA.SHELL";
        if (value == NAME::COLOR::SIENNA) return "SIENNA";
        if (value == NAME::COLOR::SILVER) return "SILVER";
        if (value == NAME::COLOR::SKY_BLUE) return "SKY.BLUE";
        if (value == NAME::COLOR::SLATE_BLUE) return "SLATE.BLUE";
        if (value == NAME::COLOR::SLATE_GRAY) return "SLATE.GRAY";
        if (value == NAME::COLOR::SNOW) return "SNOW";
        if (value == NAME::COLOR::SPRING_GREEN) return "SPRING.GREEN";
        if (value == NAME::COLOR::STEEL_BLUE) return "STEEL.BLUE";
        if (value == NAME::COLOR::TAN) return "TAN";
        if (value == NAME::COLOR::TEAL) return "TEAL";
        if (value == NAME::COLOR::THISTLE) return "THISTLE";
        if (value == NAME::COLOR::TOMATO) return "TOMATO";
        if (value == NAME::COLOR::TURQUOISE) return "TURQUOISE";
        if (value == NAME::COLOR::VIOLET) return "VIOLET";
        if (value == NAME::COLOR::WHEAT) return "WHEAT";
        if (value == NAME::COLOR::WHITE_SMOKE) return "WHITE.SMOKE";
        if (value == NAME::COLOR::WHITE) return "WHITE";
        if (value == NAME::COLOR::YELLOW_GREEN) return "YELLOW.GREEN";
        if (value == NAME::COLOR::YELLOW) return "YELLOW";
    }
    return "#" + MP_CONVERT_STRING_FROM_HEX(value, 8);
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
    if (MP_STRING_CONTAINS(value, "@@"))
    {
        auto a_Result = value;
        if (MP_STRING_CONTAINS(value, "@@@"))
        {
            a_Result = MP_STRING_REPLACE(a_Result, "@@@", "[[[64]]][[[64]]][[[64]]]");
        }
        if (MP_STRING_CONTAINS(value, "@@"))
        {
            a_Result = MP_STRING_REPLACE(a_Result, "@@", "[[[64]]][[[64]]]");
        }
        return a_Result;
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

MP_STRING atom::Trace::__GetStackTrace(MP_STRING source, int level, int skip)
{
    auto a_Result = (MP_STRING)"";
    {
        MP_STACKTRACE a_Context;
        {
            MP_STACKTRACE_INITIALIZE(a_Context);
        }
        try
        {
            auto a_Size = MP_STACKTRACE_FRAME_COUNT_GET(a_Context);
            auto a_Count = extension::AnyPreview::GetProperty(NAME::PROPERTY::DEBUGGING_STACK_SIZE, true);
            for (auto i = skip; (i < a_Size) && (a_Count > 0); i++)
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
                        a_Result += __GetLevel(level) + MP_STACKFRAME_METHOD_NAME_GET(a_Context1) + "(";
                    }
                    {
                        auto a_Size1 = MP_STACKFRAME_METHOD_PARAM_COUNT_GET(a_Context1);
                        for (auto ii = 0; ii < a_Size1; ii++)
                        {
                            auto a_Context2 = MP_STACKFRAME_METHOD_PARAM_GET(a_Context1, ii);
                            {
                                a_Result += ((ii == 0) ? "" : ", ") + MP_STACKPARAM_TYPE_NAME_GET(a_Context2) + " " + MP_STACKPARAM_NAME_GET(a_Context2);
                            }
                        }
                    }
                    {
                        a_Result += ")" +
                            __GetSource(source) +
                            " @@@EVENT " + NAME::EVENT::FUNCTION +
                            " @@@COMMENT <" + MP_STACKFRAME_MODULE_NAME_GET(a_Context1) + "> @@HINT <[[[Module Name]]]>" +
                            " @@@URL " + MP_STACKFRAME_FILE_NAME_GET(a_Context1) + " @@LINE " + MP_STACKFRAME_FILE_LINE_GET(a_Context1) + " @@POSITION " + MP_STACKFRAME_FILE_POSITION_GET(a_Context1) + "\n";
                    }
                }
            }
        }
        catch (MP_PTR(MP_EXCEPTION))
        {
            // Any exceptions here may be ignored
        }
        {
            MP_STACKTRACE_FINALIZE(a_Context);
        }
    }
    return a_Result;
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
                MP_THREAD_SLEEP(10);
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
                extension::AnyPipe::Execute("", a_Context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION))
    {
        // Any exceptions here may be ignored
    }
    {
        s_TraceThread = nullptr;
    }
}
