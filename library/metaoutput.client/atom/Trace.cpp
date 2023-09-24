
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_THREAD_MUTEX) atom::Trace::s_Mutex = nullptr;
MP_PTR(MP_MAP(MP_PTR(Trace))) atom::Trace::s_Instances = nullptr;
MP_PTR(MP_THREAD) atom::Trace::s_TraceThread = nullptr;
MP_STRING atom::Trace::s_TraceBuffer = nullptr;
#endif

// atom::Trace::TML::CONTROL::PARAM ###########################################
MP_STRING atom::Trace::TML::CONTROL::PARAM::GetBackground(MP_INT value)
{
    return "&&&BACKGROUND " + pattern::data::Color::GetValue(value) + " ";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetBackground(MP_STRING value)
{
    return "&&&BACKGROUND " + GetFirstLine(value, false) + " ";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetCount(MP_INT value)
{
    auto a_Result = (MP_STRING)"";
    if (value > 0)
    {
        a_Result += "&&&COUNT " + MP_CONVERT_STRING_FROM_INT(value, 0) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetFont(MP_STRING name, MP_INT size)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(name) == false)
    {
        a_Result += "&&&FONT.NAME " + GetFirstLine(name, false) + " ";
    }
    if (size > 0)
    {
        a_Result += "&&&FONT.SIZE " + MP_CONVERT_STRING_FROM_INT(size, 0) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetFont(MP_STRING name, MP_INT size, MP_INT state)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(name) == false)
    {
        a_Result += "&&&FONT.NAME " + GetFirstLine(name, false) + " ";
    }
    if (size > 0)
    {
        a_Result += "&&&FONT.SIZE " + MP_CONVERT_STRING_FROM_INT(size, 0) + " ";
    }
    if (state != pattern::data::Font::STATE::NONE)
    {
        {
            a_Result += "&&&FONT.STATE";
        }
        {
            if ((state & pattern::data::Font::STATE::BOLD) == pattern::data::Font::STATE::BOLD) a_Result += " BOLD";
            if ((state & pattern::data::Font::STATE::ITALIC) == pattern::data::Font::STATE::ITALIC) a_Result += " ITALIC";
            if ((state & pattern::data::Font::STATE::STRIKEOUT) == pattern::data::Font::STATE::STRIKEOUT) a_Result += " STRIKEOUT";
            if ((state & pattern::data::Font::STATE::UNDERLINE) == pattern::data::Font::STATE::UNDERLINE) a_Result += " UNDERLINE";
        }
        {
            a_Result += " ";
        }
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetForeground(MP_INT value)
{
    return "&&&FOREGROUND " + pattern::data::Color::GetValue(value) + " ";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetForeground(MP_STRING value)
{
    return "&&&FOREGROUND " + GetFirstLine(value, false) + " ";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetHandler(MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(tool) == false)
    {
        extension::AnyTool::Register(tool, id, handler);
    }
    else
    {
        return a_Result;
    }
    {
        a_Result = "&&&TOOL " + GetFirstLine(tool, false);
    }
    if (MP_STRING_EMPTY(id) == false)
    {
        a_Result += " &&&ID " + GetFirstLine(id, false);
    }
    return a_Result + " ";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetHint(MP_STRING value)
{
    auto a_Result = GetMultiLine(value);
    if (MP_STRING_EMPTY(a_Result) == false)
    {
        return "&&&HINT " + a_Result + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetMargin(MP_INT x, MP_INT y)
{
    auto a_Result = (MP_STRING)"";
    if (x != 0)
    {
        a_Result += "&&&MARGIN.X " + MP_CONVERT_STRING_FROM_INT(x, 0) + " ";
    }
    if (y != 0)
    {
        a_Result += "&&&MARGIN.Y " + MP_CONVERT_STRING_FROM_INT(y, 0) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetState(MP_INT state)
{
    auto a_Result = (MP_STRING)"";
    if (state != pattern::data::Font::STATE::NONE)
    {
        {
            a_Result += "&&&STATE";
        }
        {
            if ((state & pattern::data::Control::STATE::BLINK) == pattern::data::Control::STATE::BLINK) a_Result += " BLINK";
            if ((state & pattern::data::Control::STATE::BLUR) == pattern::data::Control::STATE::BLUR) a_Result += " BLUR";
            if ((state & pattern::data::Control::STATE::DISABLED) == pattern::data::Control::STATE::DISABLED) a_Result += " DISABLED";
            if ((state & pattern::data::Control::STATE::INFINITE) == pattern::data::Control::STATE::INFINITE) a_Result += " INFINITE";
            if ((state & pattern::data::Control::STATE::MUTE) == pattern::data::Control::STATE::MUTE) a_Result += " MUTE";
        }
        {
            a_Result += " ";
        }
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetPadding(MP_INT value)
{
    if (value != 0)
    {
        return "&&&PADDING " + MP_CONVERT_STRING_FROM_INT(value, 0) + " ";
    }
    return "";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetPadding(MP_INT minX, MP_INT minY, MP_INT maxX, MP_INT maxY)
{
    auto a_Result = (MP_STRING)"";
    if (minX != 0)
    {
        a_Result += "&&&PADDING.MIN.X " + MP_CONVERT_STRING_FROM_INT(minX, 0) + " ";
    }
    if (minY != 0)
    {
        a_Result += "&&&PADDING.MIN.Y " + MP_CONVERT_STRING_FROM_INT(minY, 0) + " ";
    }
    if (maxX != 0)
    {
        a_Result += "&&&PADDING.MAX.X " + MP_CONVERT_STRING_FROM_INT(maxX, 0) + " ";
    }
    if (maxY != 0)
    {
        a_Result += "&&&PADDING.MAX.Y " + MP_CONVERT_STRING_FROM_INT(maxY, 0) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetTransparency(MP_INT value)
{
    if (value >= 0)
    {
        return "&&&TRANSPARENCY " + MP_CONVERT_STRING_FROM_INT(value, 0) + " ";
    }
    return "";
}

MP_STRING atom::Trace::TML::CONTROL::PARAM::GetUrl(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        return "&&&URL " + GetFirstLine(value, false) + " ";
    }
    return "";
}

// atom::Trace::TML::CONTROL ##################################################
MP_STRING atom::Trace::TML::CONTROL::GetAudio(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("AUDIO", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetBrowser(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("BROWSER", level, source, "", alignment, sizeX, sizeY, params) + "&&&URL " + content + " ";
}

MP_STRING atom::Trace::TML::CONTROL::GetButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("BUTTON", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetCanvas(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("CANVAS", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetChart(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("CHART", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetCheckBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("CHECKBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetComboBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("COMBOBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetEditBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("EDITBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetGallery(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("GALLERY", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetGauge(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("GAUGE", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("ITEM", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("LABEL", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetLink(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("LINK", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetPanel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("PANEL", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("PICTURE", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetProgressBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("PROGRESSBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetRadioBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("RADIOBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetScrollBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("SCROLLBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetSlideBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("SLIDEBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetSplitter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("SPLITTER", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetTabBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("TABBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetTable(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("TABLE", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetTextBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("TEXTBOX", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetTree(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("TREE", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetVideo(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("VIDEO", level, source, content, alignment, sizeX, sizeY, params);
}

MP_STRING atom::Trace::TML::CONTROL::GetWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    return __GetTml("WINDOW", level, source, content, alignment, sizeX, sizeY, params);
}

// Private #############
MP_STRING atom::Trace::TML::CONTROL::__GetTml(MP_STRING control, MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params)
{
    auto a_Result = GetLevel(level) + "@@@SOURCE " + GetFirstLine(source, false) + " @@@CONTROL " + control;
    if (alignment != pattern::data::Alignment::NAME::NONE)
    {
        {
            a_Result += " &&&ALIGNMENT";
        }
        if ((alignment & pattern::data::Alignment::NAME::CLIENT) == pattern::data::Alignment::NAME::CLIENT)
        {
            a_Result += " CLIENT";
        }
        else
        {
            if ((alignment & pattern::data::Alignment::NAME::CENTER) == pattern::data::Alignment::NAME::CENTER) a_Result += " CENTER";
            if ((alignment & pattern::data::Alignment::NAME::CONTENT) == pattern::data::Alignment::NAME::CONTENT) a_Result += " CONTENT";
            if ((alignment & pattern::data::Alignment::NAME::LEFT) == pattern::data::Alignment::NAME::LEFT) a_Result += " LEFT";
            if ((alignment & pattern::data::Alignment::NAME::TOP) == pattern::data::Alignment::NAME::TOP) a_Result += " TOP";
            if ((alignment & pattern::data::Alignment::NAME::RIGHT) == pattern::data::Alignment::NAME::RIGHT) a_Result += " RIGHT";
            if ((alignment & pattern::data::Alignment::NAME::BOTTOM) == pattern::data::Alignment::NAME::BOTTOM) a_Result += " BOTTOM";
        }
    }
    if (sizeX != 0)
    {
        a_Result += " &&&SIZE.X " + MP_CONVERT_STRING_FROM_INT(sizeX, 0);
    }
    if (sizeY != 0)
    {
        a_Result += " &&&SIZE.Y " + MP_CONVERT_STRING_FROM_INT(sizeY, 0);
    }
    if (MP_STRING_EMPTY(params) == false)
    {
        a_Result += " " + MP_STRING_TRIM(params);
    }
    {
        auto a_Context = MP_STRING_TRIM(GetMultiLine(content));
        if (MP_STRING_EMPTY(a_Context) == false)
        {
            a_Result += " &&&VALUE " + a_Context;
        }
    }
    return a_Result + " ";
}

// atom::Trace::TML::EVENT ####################################################
MP_STRING atom::Trace::TML::EVENT::GetAppend(MP_STRING name, MP_STRING picture)
{
    return "@@@EVENT.APPEND " + GetFirstLine(name, false) + " &&&VALUE " + GetFirstLine(picture, false) + " ";
}

MP_STRING atom::Trace::TML::EVENT::GetRemove(MP_STRING name)
{
    return "@@@EVENT.REMOVE " + GetFirstLine(name, false) + " ";
}

// atom::Trace::TML::EXTENSION ################################################
MP_STRING atom::Trace::TML::EXTENSION::GetActionBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(background)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(background)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::ACTION::TRANSPARENCY)) + MESSAGE::GetNextTrace() +
        CONTROL::GetScrollBox(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::RIGHT, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, content, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2), pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2),
            CONTROL::PARAM::GetHandler(tool, id, handler));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING url)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::RIGHT, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, content, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2), pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2),
            CONTROL::PARAM::GetUrl(url));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionCanvas(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    return
        CONTROL::GetCanvas(level, source, content, alignment, sizeX, sizeX,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetHandler(tool, id, handler));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionEditBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    MP_UNUSED(background);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::WINDOW::PADDING * 4, pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::WINDOW::PADDING * 4)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(pattern::data::Control::CONSTANT::ACTION::FOREGROUND) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y)) + MESSAGE::GetNextTrace() +
        CONTROL::GetEditBox(level + 2, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(foreground) +
            CONTROL::PARAM::GetForeground(pattern::data::Control::CONSTANT::ACTION::FOREGROUND) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::ACTION::FONT_NAME, pattern::data::Control::CONSTANT::ACTION::FONT_SIZE, pattern::data::Font::STATE::NONE) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0) +
            CONTROL::PARAM::GetHandler(tool, id, handler));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionIndent(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeY)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", alignment, sizeY <= 0 ? pattern::data::Control::CONSTANT::WINDOW::PADDING : sizeY, sizeY <= 0 ? pattern::data::Control::CONSTANT::WINDOW::PADDING : sizeY,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionGallery(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetGallery(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionGalleryItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING picture, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    return
        CONTROL::GetItem(level, source, picture, pattern::data::Alignment::NAME::NONE, sizeX, sizeX,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetHint(content) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING) +
            CONTROL::PARAM::GetHandler(tool, id, handler) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::TOOL::TRANSPARENCY));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionGalleryItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING picture, MP_INT sizeX, MP_STRING url)
{
    return
        CONTROL::GetItem(level, source, picture, pattern::data::Alignment::NAME::NONE, sizeX, sizeX,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetHint(content) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING) +
            CONTROL::PARAM::GetUrl(url) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::TOOL::TRANSPARENCY));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionGalleryTitle(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    return
        CONTROL::GetItem(level, source, content, pattern::data::Alignment::NAME::NONE, 0, pattern::data::Control::CONSTANT::TITLE::SIZE_Y,
            CONTROL::PARAM::GetBackground((background & 0x00FFFFFF) | ((0xFF - ((pattern::data::Control::CONSTANT::HEADER::TRANSPARENCY * 0xFF) / 100)) << 24)) +
            CONTROL::PARAM::GetForeground(foreground));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_BOOL isHighlighted)
{
    MP_UNUSED(foreground);
    return
        CONTROL::GetLabel(level, source, content, alignment, 0, 0,
            CONTROL::PARAM::GetForeground(isHighlighted ? pattern::data::Control::CONSTANT::ACTION::FOREGROUND : background) +
            CONTROL::PARAM::GetTransparency(isHighlighted ? 0 : pattern::data::Control::CONSTANT::HEADER::TRANSPARENCY) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::ACTION::FONT_NAME, pattern::data::Control::CONSTANT::ACTION::FONT_SIZE, isHighlighted ? pattern::data::Font::STATE::BOLD : pattern::data::Font::STATE::NONE));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionParameter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING value, MP_INT sizeX, MP_BOOL isHighlighted)
{
    auto a_Result =
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::TITLE::SIZE_Y,
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0)) + MESSAGE::GetNextTrace();
    if (isHighlighted)
    {
        a_Result +=
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
                CONTROL::PARAM::GetBackground(foreground)) + MESSAGE::GetNextTrace();
    }
    if (MP_STRING_EMPTY(content) == false)
    {
        a_Result +=
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::LEFT, sizeX > 0 ? sizeX : pattern::data::Control::CONSTANT::TITLE::SIZE_X, 0, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetLabel(level + 2, source, content, pattern::data::Alignment::NAME::RIGHT | pattern::data::Alignment::NAME::CONTENT, 0, 0,
                CONTROL::PARAM::GetForeground(background)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetLabel(level + 1, source, ":", pattern::data::Alignment::NAME::LEFT | pattern::data::Alignment::NAME::CONTENT, 0, 0,
                CONTROL::PARAM::GetForeground(pattern::data::Color::NAME::GRAY)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetLabel(level + 1, source, GetFirstLine(value, true), pattern::data::Alignment::NAME::CLIENT, 0, 0,
                CONTROL::PARAM::GetForeground(pattern::data::Control::CONSTANT::ACTION::FOREGROUND) +
                CONTROL::PARAM::GetFont(nullptr, 0, pattern::data::Font::STATE::BOLD));
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    if (sizeX == 0)
    {
        sizeX = pattern::data::Control::CONSTANT::ACTION::SIZE_Y;
    }
    if (MP_STRING_EMPTY(content) == false)
    {
        return
            CONTROL::GetPanel(level, source, "", alignment, 0, sizeX, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetPicture(level + 1, source, content, pattern::data::Alignment::NAME::CENTER, sizeX, sizeX, "");
    }
    return "";
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionPreview(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    auto a_Name = GetControl(content);
    if (a_Name == pattern::data::Control::NAME::PICTURE)
    {
        return
            CONTROL::GetPanel(level, source, "", alignment, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetPicture(level + 1, source, content, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2), pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2),
                CONTROL::PARAM::GetHint("[[[Preview]]]"));
    }
    if (a_Name == pattern::data::Control::NAME::VIDEO)
    {
        return
            CONTROL::GetPanel(level, source, "", alignment, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetVideo(level + 1, source, content, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2), pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2),
                CONTROL::PARAM::GetHint("[[[Preview]]]"));
    }
    return
        CONTROL::GetPanel(level, source, "", alignment, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, pattern::data::Control::CONSTANT::RESOURCE::PICTURE_FILE, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2), pattern::data::Control::CONSTANT::ACTION::SIZE_Y - (pattern::data::Control::CONSTANT::WINDOW::PADDING * 2),
            CONTROL::PARAM::GetHint("[[[Preview]]]"));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionRedirect(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    return
        CONTROL::GetPanel(level, source, "", alignment, pattern::data::Control::CONSTANT::ACTION::SIZE_Y / 2, pattern::data::Control::CONSTANT::ACTION::SIZE_Y,
            CONTROL::PARAM::GetBackground(foreground)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/EXTENSION/ARROW}}}", pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y / 2, pattern::data::Control::CONSTANT::ACTION::SIZE_Y / 2, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionSlideBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    return
        CONTROL::GetSlideBox(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionSlideItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(background));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionSplitter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetSplitter(level, source, "", alignment, pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::WINDOW::PADDING,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionTabBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    return
        CONTROL::GetTabBox(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::FOOTER::TRANSPARENCY));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionTabItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(background);
    return
        CONTROL::GetPanel(level, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(foreground)) + MESSAGE::GetNextTrace() +
        CONTROL::GetScrollBox(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionTable(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetTable(level, source, "", pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, pattern::data::Control::CONSTANT::ACTION::SIZE_Y, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionTextBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(background)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(background)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::ACTION::TRANSPARENCY)) + MESSAGE::GetNextTrace() +
        CONTROL::GetTextBox(level, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(background));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionTitle(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::TITLE::SIZE_Y,
            CONTROL::PARAM::GetBackground(background)) + MESSAGE::GetNextTrace() +
        CONTROL::GetLabel(level + 1, source, content, pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::TITLE::FONT_NAME, pattern::data::Control::CONSTANT::TITLE::FONT_SIZE, pattern::data::Font::STATE::NONE)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(foreground));
}

MP_STRING atom::Trace::TML::EXTENSION::GetActionViewerBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX)
{
    MP_UNUSED(foreground);
    if ((MP_STRING_EMPTY(content) == false) && (MP_STRING_CONTAINS(content, "\r") == false) && (MP_STRING_CONTAINS(content, "\n") == false))
    {
        auto a_Name = GetControl(content);
        if (a_Name == pattern::data::Control::NAME::AUDIO)
        {
            return CONTROL::GetAudio(level, source, content, alignment, sizeX, sizeX, "");
        }
        if (a_Name == pattern::data::Control::NAME::PICTURE)
        {
            return CONTROL::GetPicture(level, source, content, alignment, sizeX, sizeX, "");
        }
        if (a_Name == pattern::data::Control::NAME::VIDEO)
        {
            return CONTROL::GetVideo(level, source, content, alignment, sizeX, sizeX, "");
        }
        if (a_Name == pattern::data::Control::NAME::BROWSER)
        {
            return CONTROL::GetBrowser(level, source, MP_STRING_REPLACE(content, "\\\\", "\\"), alignment, sizeX, sizeX, "");
        }
    }
    {
        return
            CONTROL::GetTextBox(level, source, content, alignment, sizeX, sizeX,
                CONTROL::PARAM::GetForeground(background));
    }
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::FOOTER::SIZE_Y + pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::FOOTER::TRANSPARENCY)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_BOOL isBlink, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    if (MP_STRING_EMPTY(content) == false)
    {
        return
            CONTROL::GetButton(level, source, content, pattern::data::Alignment::NAME::RIGHT, sizeX <= 0 ? pattern::data::Control::CONSTANT::BUTTON::SIZE_X : sizeX, 0,
                CONTROL::PARAM::GetBackground(background) +
                CONTROL::PARAM::GetForeground(foreground) +
                CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::BUTTON::FONT_NAME, pattern::data::Control::CONSTANT::BUTTON::FONT_SIZE, pattern::data::Font::STATE::BOLD) +
                CONTROL::PARAM::GetState(isBlink ? pattern::data::Control::STATE::BLINK : pattern::data::Control::STATE::NONE) +
                CONTROL::PARAM::GetHandler(tool, id, handler) +
                CONTROL::PARAM::GetHint(hint)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::RIGHT, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0,
                CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND));
    }
    return "";
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_BOOL isBlink, MP_STRING url)
{
    if (MP_STRING_EMPTY(content) == false)
    {
        return
            CONTROL::GetButton(level, source, content, pattern::data::Alignment::NAME::RIGHT, sizeX <= 0 ? pattern::data::Control::CONSTANT::BUTTON::SIZE_X : sizeX, 0,
                CONTROL::PARAM::GetState(pattern::data::Control::STATE::BLINK) +
                CONTROL::PARAM::GetBackground(background) +
                CONTROL::PARAM::GetForeground(foreground) +
                CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::BUTTON::FONT_NAME, pattern::data::Control::CONSTANT::BUTTON::FONT_SIZE, pattern::data::Font::STATE::BOLD) +
                CONTROL::PARAM::GetState(isBlink ? pattern::data::Control::STATE::BLINK : pattern::data::Control::STATE::NONE) +
                CONTROL::PARAM::GetUrl(url) +
                CONTROL::PARAM::GetHint(hint)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::RIGHT, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0,
                CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND));
    }
    return "";
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterComboBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::RIGHT, sizeX <= 0 ? pattern::data::Control::CONSTANT::COMBOBOX::SIZE_X : sizeX, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::TOOL::PADDING)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetComboBox(level + 1, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetHandler(tool, id, handler) +
            CONTROL::PARAM::GetHint(hint) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::COMBOBOX::FONT_NAME, pattern::data::Control::CONSTANT::COMBOBOX::FONT_SIZE, pattern::data::Font::STATE::BOLD));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterComboItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    return
        CONTROL::GetItem(level + 1, source, content, pattern::data::Alignment::NAME::NONE, 0, pattern::data::Control::CONSTANT::PREVIEW::ITEM_SIZE_Y,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::COMBOBOX::FONT_NAME, pattern::data::Control::CONSTANT::COMBOBOX::FONT_SIZE, pattern::data::Font::STATE::BOLD));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterIndent(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX)
{
    MP_UNUSED(content);
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", alignment, sizeX <= 0 ? pattern::data::Control::CONSTANT::WINDOW::PADDING : sizeX, 0,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterInfo(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint)
{
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::TOOL::PADDING)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y * 2, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y * 2, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/OTHER/INFO}}}", pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
            CONTROL::PARAM::GetHint(hint)) + MESSAGE::GetNextTrace() +
        CONTROL::GetEditBox(level + 1, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(background) +
            CONTROL::PARAM::GetHint(hint));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterFind(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::TOOL::PADDING)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y,
            CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/OTHER/FIND}}}", pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
            CONTROL::PARAM::GetHint("[[[Search text]]]")) + MESSAGE::GetNextTrace() +
        CONTROL::GetEditBox(level + 1, source, content, pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetHandler(tool, id, handler) +
            CONTROL::PARAM::GetHint("[[[Search text]]]"));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT alignment, MP_BOOL isHighlighted)
{
    MP_UNUSED(background);
    return
        CONTROL::GetPanel(level, source, "", alignment, 0, 0, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetLabel(level + 1, source, content, pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
            CONTROL::PARAM::GetHint(hint) +
            CONTROL::PARAM::GetForeground(isHighlighted ? pattern::data::Control::CONSTANT::ACTION::FOREGROUND : foreground) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::FOOTER::FONT_NAME, pattern::data::Control::CONSTANT::FOOTER::FONT_SIZE, isHighlighted ? pattern::data::Font::STATE::BOLD : pattern::data::Font::STATE::NONE));
}

MP_STRING atom::Trace::TML::EXTENSION::GetFooterPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPicture(level, source, content, pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::FOOTER::SIZE_Y, 0,
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::FOOTER::TRANSPARENCY) +
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING));
}

MP_STRING atom::Trace::TML::EXTENSION::GetHeaderBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(content);
    MP_UNUSED(foreground);
    return
        CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING + pattern::data::Control::CONSTANT::HEADER::SIZE_Y, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::BOTTOM, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetBackground(background) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::HEADER::TRANSPARENCY)) + MESSAGE::GetNextTrace() +
        CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
            CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0));
}

MP_STRING atom::Trace::TML::EXTENSION::GetHeaderLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground)
{
    MP_UNUSED(background);
    MP_UNUSED(foreground);
    return
        CONTROL::GetLabel(level + 1, source, content, pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
            CONTROL::PARAM::GetForeground(pattern::data::Control::CONSTANT::HEADER::FOREGROUND) +
            CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::HEADER::FONT_NAME, pattern::data::Control::CONSTANT::HEADER::FONT_SIZE, pattern::data::Font::STATE::NONE));
}

MP_STRING atom::Trace::TML::EXTENSION::GetPreviewWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture)
{
    MP_UNUSED(source);
    if (MP_STRING_EMPTY(logoPicture))
    {
        logoPicture = "{{{RESOURCE:METAOUTPUT/OTHER/PREVIEW}}}";
    }
    return
        EXTENSION::GetWindow(level, pattern::data::Source::NAME::PREVIEW, "[[[PREVIEW]]]: " + GetFirstLine(content, false), background, foreground, pattern::data::Control::CONSTANT::COUNT::NORMAL, logoPicture, "", "");
}

MP_STRING atom::Trace::TML::EXTENSION::GetToolWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture, MP_STRING headerText, MP_STRING actionPicture, MP_STRING actionText, MP_STRING buttonText, MP_STRING infoText, MP_STRING params, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler)
{
    return
        MESSAGE::GetToolMessage(level, source, pattern::data::Event::NAME::INFO, content, id, pattern::data::Message::STATE::RESEND) + MESSAGE::GetNextTrace() +
        EXTENSION::GetWindow(level + 1, source, content, background, foreground, pattern::data::Control::CONSTANT::COUNT::NORMAL, MP_STRING_EMPTY(logoPicture) ? "{{{RESOURCE:METAOUTPUT/LOGO/ICON}}}" : logoPicture, "", "") + MESSAGE::GetNextTrace() +
        EXTENSION::GetHeaderBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetHeaderLabel(level + 3, source, headerText, background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetFooterBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetFooterButton(level + 3, source, buttonText, background, foreground, "", 300, false, tool, id, handler) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionPicture(level + 3, source, actionPicture, background, foreground, pattern::data::Alignment::NAME::CONTENT_LEFT, 0) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionLabel(level + 3, source, actionText, background, foreground, pattern::data::Alignment::NAME::CLIENT, true);
}

MP_STRING atom::Trace::TML::EXTENSION::GetToolWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture, MP_STRING headerText, MP_STRING actionPicture, MP_STRING actionText, MP_STRING buttonText, MP_STRING infoText, MP_STRING params, MP_STRING url, MP_STRING id)
{
    return
        MESSAGE::GetToolMessage(level, source, pattern::data::Event::NAME::INFO, content, id, pattern::data::Message::STATE::RESEND) + MESSAGE::GetNextTrace() +
        EXTENSION::GetWindow(level + 1, source, content, background, foreground, pattern::data::Control::CONSTANT::COUNT::NORMAL, MP_STRING_EMPTY(logoPicture) ? "{{{RESOURCE:METAOUTPUT/LOGO/ICON}}}" : logoPicture, "", "") + MESSAGE::GetNextTrace() +
        EXTENSION::GetHeaderBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetHeaderLabel(level + 3, source, headerText, background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetFooterBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetFooterButton(level + 3, source, buttonText, background, foreground, "", 300, false, url) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionBox(level + 2, source, "", background, foreground) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionPicture(level + 3, source, actionPicture, background, foreground, pattern::data::Alignment::NAME::CONTENT_LEFT, 0) + MESSAGE::GetNextTrace() +
        EXTENSION::GetActionLabel(level + 3, source, actionText, background, foreground, pattern::data::Alignment::NAME::CLIENT, true);
}

MP_STRING atom::Trace::TML::EXTENSION::GetWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT rowCount, MP_STRING logoPicture, MP_STRING params, MP_STRING hint)
{
    if (MP_STRING_CONTAINS(params, pattern::data::Message::TML::ATTRIBUTE) == false)
    {
        params = CONTROL::GetLabel(level + 3, source, GetFirstLine(params, false), pattern::data::Alignment::NAME::CONTENT_RIGHT, 0, 0,
            CONTROL::PARAM::GetHint(hint) +
            CONTROL::PARAM::GetForeground(foreground) +
            CONTROL::PARAM::GetTransparency(pattern::data::Control::CONSTANT::TOOL::TRANSPARENCY / 2));
    }
    {
        return
            CONTROL::GetPanel(level, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0,
                CONTROL::PARAM::GetBackground(pattern::data::Control::CONSTANT::WINDOW::BACKGROUND) +
                CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING) +
                CONTROL::PARAM::GetCount(rowCount)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::HEADER::SIZE_Y,
                CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::HEADER::FONT_NAME, pattern::data::Control::CONSTANT::HEADER::FONT_SIZE, pattern::data::Font::STATE::BOLD) +
                CONTROL::PARAM::GetBackground(background) +
                CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::TOOL::PADDING, pattern::data::Control::CONSTANT::WINDOW::PADDING, pattern::data::Control::CONSTANT::TOOL::PADDING)) + MESSAGE::GetNextTrace() +
            CONTROL::GetLabel(level + 2, source, content, pattern::data::Alignment::NAME::CONTENT_LEFT, 0, 0,
                CONTROL::PARAM::GetFont(pattern::data::Control::CONSTANT::HEADER::FONT_NAME, pattern::data::Control::CONSTANT::HEADER::FONT_SIZE, pattern::data::Font::STATE::BOLD) +
                CONTROL::PARAM::GetForeground(foreground) +
                CONTROL::PARAM::GetCount(pattern::data::Control::CONSTANT::COUNT::NORMAL)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 2, source, "", pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::WINDOW::PADDING * 10, 0, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 2, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "") + MESSAGE::GetNextTrace() + params + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::TOP, 0, pattern::data::Control::CONSTANT::WINDOW::PADDING, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::LOGO::SIZE_X, 0,
                CONTROL::PARAM::GetForeground(background) +
                CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::DELIMITER::SIZE_Y)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPicture(level + 2, source, logoPicture, pattern::data::Alignment::NAME::CENTER, pattern::data::Control::CONSTANT::LOGO::SIZE_X, pattern::data::Control::CONSTANT::LOGO::SIZE_X,
                CONTROL::PARAM::GetPadding(pattern::data::Control::CONSTANT::WINDOW::PADDING)) + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::LEFT, pattern::data::Control::CONSTANT::WINDOW::PADDING, 0, "") + MESSAGE::GetNextTrace() +
            CONTROL::GetPanel(level + 1, source, "", pattern::data::Alignment::NAME::CLIENT, 0, 0, "");
    }
}

// atom::Trace::TML::FILE #####################################################
MP_STRING atom::Trace::TML::FILE::GetImport(MP_STRING source, MP_STRING url)
{
    return "@@@IMPORT " + url +
        (MP_STRING_EMPTY(source) ? "" : " &&&SOURCE " + GetFirstLine(source, false)) + " ";
}

MP_STRING atom::Trace::TML::FILE::GetExport(MP_STRING source, MP_STRING url)
{
    return "@@@EXPORT " + url +
        (MP_STRING_EMPTY(source) ? "" : " &&&SOURCE " + GetFirstLine(source, false)) + " ";
}

// atom::Trace::TML::MESSAGE::CONDITION #######################################
MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetAnd(MP_STRING condition1, MP_STRING condition2)
{
    return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
        " &&&CONDITION " + GetFirstLine(condition2, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3)
{
    return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
        " &&&CONDITION " + GetFirstLine(condition2, false) +
        " &&&CONDITION " + GetFirstLine(condition3, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4)
{
    return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
        " &&&CONDITION " + GetFirstLine(condition2, false) +
        " &&&CONDITION " + GetFirstLine(condition3, false) +
        " &&&CONDITION " + GetFirstLine(condition4, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4, MP_STRING condition5)
{
    return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
        " &&&CONDITION " + GetFirstLine(condition2, false) +
        " &&&CONDITION " + GetFirstLine(condition3, false) +
        " &&&CONDITION " + GetFirstLine(condition4, false) +
        " &&&CONDITION " + GetFirstLine(condition5, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetOr(MP_STRING condition1, MP_STRING condition2)
{
    return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) + " &&&CONDITION " + GetFirstLine(condition2, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3)
{
    return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) + " &&&CONDITION " + GetFirstLine(condition2, false) + " &&&CONDITION " + GetFirstLine(condition3, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4)
{
    return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) + " &&&CONDITION " + GetFirstLine(condition2, false) + " &&&CONDITION " + GetFirstLine(condition3, false) + " &&&CONDITION " + GetFirstLine(condition4, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4, MP_STRING condition5)
{
    return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) + " &&&CONDITION " + GetFirstLine(condition2, false) + " &&&CONDITION " + GetFirstLine(condition3, false) + " &&&CONDITION " + GetFirstLine(condition4, false) + " &&&CONDITION " + GetFirstLine(condition5, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetEmpty(MP_STRING attribute)
{
    return "(((COMPARE.EMPTY &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetNotEmpty(MP_STRING attribute)
{
    return "(((COMPARE.NOT.EMPTY &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetEqual(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetNotEqual(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.NOT.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetContains(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.CONTAINS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetNotContains(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.NOT.CONTAINS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetMore(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.MORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetMoreEqual(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.MORE.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetLess(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.LESS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

MP_STRING atom::Trace::TML::MESSAGE::CONDITION::GetLessEqual(MP_STRING attribute, MP_STRING find)
{
    return "(((COMPARE.NOT.LESS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
}

// atom::Trace::TML::MESSAGE::PARAM #############################################
MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetBackground(MP_INT value)
{
    return CONTROL::PARAM::GetBackground(value);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetBackground(MP_STRING value)
{
    return CONTROL::PARAM::GetBackground(value);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetDate(MP_INT year, MP_INT month, MP_INT day)
{
    return "&&&DATE " +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(year, 2100)), 4) + "." +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(month, 12)), 2) + "." +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(day, 31)), 2) + " ";
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetCount(MP_INT value)
{
    return CONTROL::PARAM::GetCount(value);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetId(MP_STRING id)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(id) == false)
    {
        a_Result += "&&&ID " + GetFirstLine(id, false) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetFont(MP_STRING name)
{
    return CONTROL::PARAM::GetFont(name, 0);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetFont(MP_STRING name, MP_INT state)
{
    return CONTROL::PARAM::GetFont(name, 0, state);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetForeground(MP_INT value)
{
    return CONTROL::PARAM::GetForeground(value);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetForeground(MP_STRING value)
{
    return CONTROL::PARAM::GetForeground(value);
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetProgress(MP_DOUBLE value, MP_STRING hint)
{
    auto a_Result = (MP_STRING)"";
    if (value != 0)
    {
        a_Result += "&&&PROGRESS " + MP_CONVERT_STRING_FROM_DOUBLE(value) + " ";
    }
    if ((value != 0) && (MP_STRING_EMPTY(hint) == false))
    {
        a_Result += "&&&PROGRESS.HINT " + GetMultiLine(hint) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetState(MP_INT value)
{
    auto a_Result = (MP_STRING)"";
    if (value != pattern::data::Message::STATE::NONE)
    {
        {
            a_Result += "&&&STATE";
        }
        {
            if ((value & pattern::data::Message::STATE::BEEP) == pattern::data::Message::STATE::BEEP) a_Result += " BEEP";
            if ((value & pattern::data::Message::STATE::BLINK) == pattern::data::Message::STATE::BLINK) a_Result += " BLINK";
            if ((value & pattern::data::Message::STATE::CLEAR) == pattern::data::Message::STATE::CLEAR) a_Result += " CLEAR";
            if ((value & pattern::data::Message::STATE::COLLAPSE) == pattern::data::Message::STATE::COLLAPSE) a_Result += " COLLAPSE";
            if ((value & pattern::data::Message::STATE::EXPAND) == pattern::data::Message::STATE::EXPAND) a_Result += " EXPAND";
            if ((value & pattern::data::Message::STATE::FIX) == pattern::data::Message::STATE::FIX) a_Result += " FIX";
            if ((value & pattern::data::Message::STATE::FOCUS) == pattern::data::Message::STATE::FOCUS) a_Result += " FOCUS";
            if ((value & pattern::data::Message::STATE::HIDE) == pattern::data::Message::STATE::HIDE) a_Result += " HIDE";
            if ((value & pattern::data::Message::STATE::LOCK) == pattern::data::Message::STATE::LOCK) a_Result += " LOCK";
            if ((value & pattern::data::Message::STATE::MUTE) == pattern::data::Message::STATE::MUTE) a_Result += " MUTE";
            if ((value & pattern::data::Message::STATE::PIN) == pattern::data::Message::STATE::PIN) a_Result += " PIN";
            if ((value & pattern::data::Message::STATE::REMOVE) == pattern::data::Message::STATE::REMOVE) a_Result += " REMOVE";
            if ((value & pattern::data::Message::STATE::RESEND) == pattern::data::Message::STATE::RESEND) a_Result += " RESEND";
            if ((value & pattern::data::Message::STATE::SHOW) == pattern::data::Message::STATE::SHOW) a_Result += " SHOW";
            if ((value & pattern::data::Message::STATE::SPEAK) == pattern::data::Message::STATE::SPEAK) a_Result += " SPEAK";
            if ((value & pattern::data::Message::STATE::UNFIX) == pattern::data::Message::STATE::UNFIX) a_Result += " UNFIX";
            if ((value & pattern::data::Message::STATE::UNFOCUS) == pattern::data::Message::STATE::UNFOCUS) a_Result += " UNFOCUS";
            if ((value & pattern::data::Message::STATE::UNLOCK) == pattern::data::Message::STATE::UNLOCK) a_Result += " UNLOCK";
            if ((value & pattern::data::Message::STATE::UNPIN) == pattern::data::Message::STATE::UNPIN) a_Result += " UNPIN";
            if ((value & pattern::data::Message::STATE::UPDATE) == pattern::data::Message::STATE::UPDATE) a_Result += " UPDATE";
        }
        {
            a_Result += " ";
        }
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond)
{
    return "&&&TIME " +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(hour, 24)), 2) + "." +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(minute, 60)), 2) + "." +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(second, 60)), 2) + "." +
        MP_CONVERT_STRING_FROM_INT(MP_MAX(0, MP_MIN(milliSecond, 999)), 3) + " ";
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetUrl(MP_STRING value, MP_STRING hint)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(value) == false)
    {
        a_Result += "&&&URL " + GetFirstLine(value, false) + " ";
    }
    if (MP_STRING_EMPTY(hint) == false)
    {
        a_Result += "&&&URL.HINT " + GetMultiLine(hint) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetUrl(MP_STRING value, MP_STRING hint, MP_INT line, MP_INT position)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(value) == false)
    {
        a_Result += "&&&URL " + GetFirstLine(value, false) + " ";
    }
    if (MP_STRING_EMPTY(hint) == false)
    {
        a_Result += "&&&URL.HINT " + GetMultiLine(hint) + " ";
    }
    if (line > 0)
    {
        a_Result += "&&&URL.LINE " + MP_CONVERT_STRING_FROM_INT(line, 0) + " ";
    }
    if (position > 0)
    {
        a_Result += "&&&URL.POSITION " + MP_CONVERT_STRING_FROM_INT(position, 0) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetUrlInfo(MP_STRING value, MP_STRING hint)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(value) == false)
    {
        a_Result += "&&&URL.INFO " + GetFirstLine(value, false) + " ";
    }
    if (MP_STRING_EMPTY(hint) == false)
    {
        a_Result += "&&&URL.INFO.HINT " + GetMultiLine(hint) + " ";
    }
    return a_Result;
}

MP_STRING atom::Trace::TML::MESSAGE::PARAM::GetValue(MP_STRING value)
{
    auto a_Result = (MP_STRING)"";
    if (MP_STRING_EMPTY(value) == false)
    {
        a_Result += "&&&VALUE " + GetMultiLine(value) + " ";
    }
    return a_Result;
}

// atom::Trace::TML::MESSAGE ##################################################
MP_STRING atom::Trace::TML::MESSAGE::GetCondition(MP_STRING condition)
{
    return "@@@CONDITION " + GetFirstLine(condition, false) + " ";
}

MP_STRING atom::Trace::TML::MESSAGE::GetPreviewMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING url, MP_INT state, MP_INT progress)
{
    MP_UNUSED(level);
    if (MP_STRING_EMPTY(url))
    {
        return "";
    }
    else
    {
        return
            MESSAGE::GetTraceMessage(0, source, event, "[[[PREVIEW]]]: " + System::IO::Path::GetFileName(url), "", "",
                MESSAGE::PARAM::GetId(url) +
                MESSAGE::PARAM::GetUrl(url, "") +
                MESSAGE::PARAM::GetForeground(pattern::data::Control::CONSTANT::PREVIEW::FOREGROUND) +
                MESSAGE::PARAM::GetProgress(progress, "[[[Work progress]]] - " + MP_CONVERT_STRING_FROM_INT(progress, 0) + "%") +
                MESSAGE::PARAM::GetState(state));
    }
}

MP_STRING atom::Trace::TML::MESSAGE::GetToolMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING id, MP_INT state)
{
    return
        MESSAGE::GetTraceMessage(level, source, event, content, "", "",
            MESSAGE::PARAM::GetId(id) +
            MESSAGE::PARAM::GetForeground(pattern::data::Control::CONSTANT::TOOL::FOREGROUND) +
            MESSAGE::PARAM::GetState(state | pattern::data::Message::STATE::CLEAR | pattern::data::Message::STATE::EXPAND | pattern::data::Message::STATE::SHOW | pattern::data::Message::STATE::BLINK));
}

MP_STRING atom::Trace::TML::MESSAGE::GetTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING message, MP_STRING hint, MP_STRING params)
{
    auto a_Result = GetLevel(level) + GetMultiLine(content) + " @@@SOURCE " + GetFirstLine(source, false);
    if (MP_STRING_EMPTY(event) == false)
    {
        a_Result += " @@@EVENT " + GetFirstLine(event, false);
    }
    if ((MP_STRING_EMPTY(message) == false) || (MP_STRING_EMPTY(params) == false))
    {
        if (MP_STRING_EMPTY(message) == false)
        {
            a_Result += " @@@MESSAGE " + GetMultiLine(message) + " " + GetFirstLine(params, false);
        }
        else
        {
            a_Result += " @@@MESSAGE " + GetFirstLine(params, false);
        }
        if (MP_STRING_EMPTY(hint) == false)
        {
            a_Result += " &&&HINT " + GetMultiLine(hint);
        }
    }
    return a_Result + " ";
}

MP_STRING atom::Trace::TML::MESSAGE::GetNextTrace()
{
    return "\n";
}

// atom::Trace::TML::PREVIEW ##################################################
MP_STRING atom::Trace::TML::PREVIEW::GetAppend(MP_STRING name, MP_PTR(extension::AnyPreview) handler, MP_STRING extension)
{
    if (MP_STRING_EMPTY(extension) == false)
    {
        extension::AnyPreview::Register(extension, handler);
    }
    return "@@@PREVIEW.APPEND " + GetFirstLine(name, false) +
        " &&&EXTENSION " + GetFirstLine(extension, false) + " ";
}

MP_STRING atom::Trace::TML::PREVIEW::GetRemove(MP_STRING name)
{
    return "@@@PREVIEW.REMOVE " + GetFirstLine(name, false) + " ";
}

// atom::Trace::TML::RESOURCE #################################################
MP_STRING atom::Trace::TML::RESOURCE::GetAppend(MP_STRING name, MP_STRING culture, MP_STRING value)
{
    return "@@@RESOURCE.APPEND " + GetFirstLine(name, false) +
        " &&&CULTURE " + culture +
        " &&&VALUE " + GetFirstLine(value, false) + " ";
}

MP_STRING atom::Trace::TML::RESOURCE::GetRemove(MP_STRING name, MP_STRING culture)
{
    return "@@@RESOURCE.REMOVE " + GetFirstLine(name, false) +
        " &&&CULTURE " + culture + " ";
}

// atom::Trace::TML::SOURCE ###################################################
MP_STRING atom::Trace::TML::SOURCE::GetAppend(MP_STRING name, MP_STRING picture)
{
    return "@@@SOURCE.APPEND " + GetFirstLine(name, false) +
        " &&&VALUE " + GetFirstLine(picture, false) + " ";
}

MP_STRING atom::Trace::TML::SOURCE::GetRemove(MP_STRING name)
{
    return "@@@SOURCE.REMOVE " + GetFirstLine(name, false) + " ";
}

MP_STRING atom::Trace::TML::SOURCE::GetClear(MP_STRING name)
{
    return "@@@SOURCE.CLEAR " + GetFirstLine(name, false) + " ";
}

// atom::Trace::TML::TOOL #####################################################
MP_STRING atom::Trace::TML::TOOL::GetAppend(MP_STRING name, MP_PTR(extension::AnyTool) handler, MP_STRING picture, MP_STRING group, MP_STRING title, MP_STRING tags, MP_INT background)
{
    if (MP_STRING_EMPTY(name) == false)
    {
        extension::AnyTool::Register(name, handler);
    }
    return "@@@TOOL.APPEND " + GetFirstLine(name, false) +
        " &&&GROUP " + GetFirstLine(group, false) +
        " &&&TITLE " + GetFirstLine(title, false) +
        " &&&TAGS " + GetFirstLine(tags, false) +
        " &&&BACKGROUND " + pattern::data::Color::GetValue(background) +
        " &&&VALUE " + GetFirstLine(picture, false) + " ";
}

MP_STRING atom::Trace::TML::TOOL::GetRemove(MP_STRING name)
{
    {
        extension::AnyTool::Unregister(name);
    }
    return "@@@TOOL.REMOVE " + GetFirstLine(name, false) + " ";
}

MP_STRING atom::Trace::TML::TOOL::GetEnable(MP_STRING name)
{
    return "@@@TOOL.ENABLE " + GetFirstLine(name, false) + " ";
}

MP_STRING atom::Trace::TML::TOOL::GetDisable(MP_STRING name)
{
    return "@@@TOOL.DISABLE " + GetFirstLine(name, false) + " ";
}

MP_STRING atom::Trace::TML::TOOL::GetShow(MP_STRING name)
{
    return "@@@TOOL.SHOW " + GetFirstLine(name, false) + " ";
}

MP_STRING atom::Trace::TML::TOOL::GetHide(MP_STRING name)
{
    return "@@@TOOL.HIDE " + GetFirstLine(name, false) + " ";
}

// atom::Trace::TML::TRANSFORM::TEXT ##########################################
MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetCamelCase(MP_STRING attribute)
{
    return "(((TEXT.CAMEL.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetLowerCase(MP_STRING attribute)
{
    return "(((TEXT.LOWER.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetSentenceCase(MP_STRING attribute)
{
    return "(((TEXT.SENTENCE.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetUpperCase(MP_STRING attribute)
{
    return "(((TEXT.UPPER.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetTrim(MP_STRING attribute)
{
    return "(((TEXT.TRIM &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetTrimBegin(MP_STRING attribute)
{
    return "(((TEXT.TRIM.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetTrimEnd(MP_STRING attribute)
{
    return "(((TEXT.TRIM.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetInsertBegin(MP_STRING attribute, MP_STRING value)
{
    return "(((TEXT.INSERT.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetInsertEnd(MP_STRING attribute, MP_STRING value)
{
    return "(((TEXT.INSERT.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetInsertAfter(MP_STRING attribute, MP_STRING find, MP_STRING value)
{
    return "(((TEXT.INSERT.AFTER &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetInsertBefore(MP_STRING attribute, MP_STRING find, MP_STRING value)
{
    return "(((TEXT.INSERT.BEFORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetInsertBetween(MP_STRING attribute, MP_STRING find1, MP_STRING find2, MP_STRING value)
{
    return "(((TEXT.INSERT.BETWEEN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND1 " + GetFirstLine(find1, false) + " &&&FIND2 " + GetFirstLine(find2, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemove(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveAll(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE.ALL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveBegin(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveEnd(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveAfter(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE.AFTER &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveBefore(MP_STRING attribute, MP_STRING find)
{
    return "(((TEXT.REMOVE.BEFORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetRemoveBetween(MP_STRING attribute, MP_STRING find1, MP_STRING find2)
{
    return "(((TEXT.REMOVE.BETWEEN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND1 " + GetFirstLine(find1, false) + " &&&FIND2 " + GetFirstLine(find2, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetReplace(MP_STRING attribute, MP_STRING find, MP_STRING replace)
{
    return "(((TEXT.REPLACE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&REPLACE " + GetFirstLine(replace, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetReplaceAll(MP_STRING attribute, MP_STRING find, MP_STRING replace)
{
    return "(((TEXT.REPLACE.ALL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&REPLACE " + GetFirstLine(replace, false) + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TEXT::GetUpdate(MP_STRING attribute, MP_STRING value)
{
    return "(((TEXT.UPDATE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
}

// atom::Trace::TML::TRANSFORM::TRACE #########################################
MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentDetect()
{
    return "(((COMMENT.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetFunctionDetect()
{
    return "(((FUNCTION.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupDetect()
{
    return "(((GROUP.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetLevelDetect()
{
    return "(((LEVEL.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetProgressDetect()
{
    return "(((PROGRESS.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetTimeDetect()
{
    return "(((TIME.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetUrlDetect()
{
    return "(((URL.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetUrlInfoDetect()
{
    return "(((URL.INFO.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetValueDetect()
{
    return "(((VALUE.DETECT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetLevelNext()
{
    return "(((LEVEL.NEXT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetLevelPrev()
{
    return "(((LEVEL.PREV))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetLevelRoot()
{
    return "(((LEVEL.ROOT))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentAfter(MP_STRING find)
{
    return "(((COMMENT.AFTER &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentBefore(MP_STRING find)
{
    return "(((COMMENT.BEFORE &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentBegin(MP_STRING find)
{
    return "(((COMMENT.BEGIN &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentBetween(MP_STRING find1, MP_STRING find2)
{
    return "(((COMMENT.BETWEEN &&&FIND1 " + find1 + " &&&FIND2 " + find2 + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetCommentEnd(MP_STRING find)
{
    return "(((COMMENT.END &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroup(MP_STRING find)
{
    return "(((GROUP &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupAfter(MP_STRING find)
{
    return "(((GROUP.AFTER &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupBefore(MP_STRING find)
{
    return "(((GROUP.BEFORE &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupBegin(MP_STRING find)
{
    return "(((GROUP.BEGIN &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupBetween(MP_STRING find1, MP_STRING find2)
{
    return "(((GROUP.BETWEEN &&&FIND1 " + find1 + " &&&FIND2 " + find2 + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupEnd(MP_STRING find)
{
    return "(((GROUP.END &&&FIND " + find + "))) ";
}

MP_STRING atom::Trace::TML::TRANSFORM::TRACE::GetGroupOutside(MP_STRING find)
{
    return "(((GROUP.OUTSIDE &&&FIND " + find + "))) ";
}

// atom::Trace::TML::TRANSFORM ################################################
MP_STRING atom::Trace::TML::TRANSFORM::GetAppend(MP_STRING name, MP_STRING source, MP_STRING scope, MP_STRING condition, MP_STRING action)
{
    return "@@@TRANSFORM.APPEND " + GetFirstLine(name, false) +
        " &&&SOURCE " + GetFirstLine(source, false) +
        " &&&SCOPE " + scope +
        " &&&CONDITION " + condition +
        " &&&ACTION " + GetFirstLine(action, false) + " ";
}

MP_STRING atom::Trace::TML::TRANSFORM::GetRemove(MP_STRING name, MP_STRING source, MP_STRING scope)
{
    return "@@@TRANSFORM.REMOVE " + GetFirstLine(name, false) +
        " &&&SOURCE " + GetFirstLine(source, false) +
        " &&&SCOPE " + scope + " ";
}

// atom::Trace::TML::TRANSLATION ##############################################
MP_STRING atom::Trace::TML::TRANSLATION::GetAppend(MP_STRING name, MP_STRING culture, MP_STRING value)
{
    return "@@@TRANSLATION.APPEND " + GetFirstLine(name, false) +
        " &&&CULTURE " + culture +
        " &&&VALUE " + GetFirstLine(value, false) + " ";
}

MP_STRING atom::Trace::TML::TRANSLATION::GetRemove(MP_STRING name, MP_STRING culture)
{
    return "@@@TRANSLATION.REMOVE " + GetFirstLine(name, false) +
        " &&&CULTURE " + culture + " ";
}

// atom::Trace::TML::VARIABLE #################################################
MP_STRING atom::Trace::TML::VARIABLE::GetSetter(MP_STRING name, MP_STRING value)
{
    return "@@@VARIABLE.SET" + GetFirstLine(name, false) +
        " &&&VALUE " + GetFirstLine(value, false) + " ";
}

// atom::Trace::AnyHandler ####################################################
void atom::Trace::AnyHandler::Execute(MP_PTR(atom::Trace) trace, int level, MP_STRING tool, MP_STRING id, MP_STRING action, MP_STRING attributes)
{
    if (this != nullptr)
    {
        _Execute(trace, level, tool, id, action, attributes);
    }
}

// Protected ###########
void atom::Trace::AnyHandler::_Execute(MP_PTR(atom::Trace) trace, int level, MP_STRING tool, MP_STRING id, MP_STRING action, MP_STRING attributes)
{
    MP_UNUSED(trace);
    MP_UNUSED(level);
    MP_UNUSED(tool);
    MP_UNUSED(id);
    MP_UNUSED(action);
    MP_UNUSED(attributes);
}

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

MP_STRING atom::Trace::GetControl(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Context = MP_STRING_TRIM(value);
        auto a_Name = MP_STRING_LOWER(a_Context);
        {
            if (MP_STRING_INDEXOF(a_Name, "data:image/") == 0) return pattern::data::Control::NAME::PICTURE;
            if (MP_STRING_INDEXOF(a_Name, "data:video/") == 0) return pattern::data::Control::NAME::VIDEO;
            if (MP_STRING_INDEXOF(a_Name, "data:audio/") == 0) return pattern::data::Control::NAME::AUDIO;
        }
        {
            auto a_Index = MP_STRING_LASTINDEXOF(a_Context, ".");
            if (a_Index >= 0)
            {
                a_Name = MP_STRING_SUBSTRING(a_Name, a_Index, MP_STRING_SIZE_GET(a_Context) - a_Index);
            }
            if (a_Index >= 0)
            {
                if (a_Name == ".aac")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".aax")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".ac3")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".aiff")  return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".au")    return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".amb")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".ape")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".dsf")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".dts")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".flac")  return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".m1a")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".m2a")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".m4a")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".m4b")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mka")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mp2")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mp3")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mpa")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mpc")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".mpp")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".ra")    return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".oga")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".ogg")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".opus")  return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".wav")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".wma")   return pattern::data::Control::NAME::AUDIO;
                if (a_Name == ".wv")    return pattern::data::Control::NAME::AUDIO;
            }
            if (a_Index >= 0)
            {
                if (a_Name == ".bmp")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".cur")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".dds")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".dng")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".exr")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".erf")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".ico")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".gif")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".hdr")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".heic")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".heif")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jfif")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jp2")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jpe")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jpeg")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jpg")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".jps")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".mng")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".pbm")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".pcx")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".pict")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".pgm")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".png")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".pnm")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".ppm")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".psd")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".tif")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".tiff")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".tga")   return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".wbmp")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".webp")  return pattern::data::Control::NAME::PICTURE;
                if (a_Name == ".wpg")   return pattern::data::Control::NAME::PICTURE;
            }
            if (a_Index >= 0)
            {
                if (a_Name == ".3g2")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".3gp")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".asf")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".av1")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".avi")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".f4v")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".flv")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".hevc")  return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".m1v")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".m2v")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".m4p")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".m4v")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mjpeg") return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mkv")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mks")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mov")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mp1")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mp2")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mp4")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mpe")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mpeg")  return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mpg")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mpv")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".mts")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".ogg")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".ogm")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".ogv")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".rm")    return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".rmvb")  return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".swf")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".vob")   return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".webm")  return pattern::data::Control::NAME::VIDEO;
                if (a_Name == ".wmv")   return pattern::data::Control::NAME::VIDEO;
            }
            if (a_Index >= 0)
            {
                if (a_Name == ".html")  return pattern::data::Control::NAME::BROWSER;
                if (a_Name == ".htm")   return pattern::data::Control::NAME::BROWSER;
            }
        }
        {
            if (MP_STRING_EMPTY(a_Name) == false)
            {
                if (MP_STRING_INDEXOF(a_Name, "https://") == 0) return pattern::data::Control::NAME::BROWSER;
                if (MP_STRING_INDEXOF(a_Name, "http://") == 0)  return pattern::data::Control::NAME::BROWSER;
                if (MP_STRING_INDEXOF(a_Name, "ftp://") == 0)   return pattern::data::Control::NAME::BROWSER;
                if (MP_STRING_INDEXOF(a_Name, "file://") == 0)  return pattern::data::Control::NAME::BROWSER;
            }
        }
    }
    return "";
}

MP_STRING atom::Trace::GetLevel(MP_INT value)
{
    switch (value)
    {
    case 0: return "";
    case 1: return "  ";
    case 2: return "    ";
    case 3: return "      ";
    case 4: return "        ";
    case 5: return "          ";
    case 6: return "            ";
    case 7: return "              ";
    case 8: return "                ";
    case 9: return "                  ";
    }
    if (value >= 0)
    {
        auto a_Result = (MP_STRING)"";
        for (auto i = 0; i < value; i++)
        {
            a_Result += "  ";
        }
        {
            return a_Result;
        }
    }
    return "";
}

MP_STRING atom::Trace::GetFirstLine(MP_STRING value, bool isAnyText)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = value;
        {
            auto a_Index1 = MP_STRING_INDEXOF(value, '\n');
            auto a_Index2 = MP_STRING_INDEXOF(value, '\r');
            if ((a_Index1 >= 0) || (a_Index2 >= 0))
            {
                a_Result = MP_STRING_SUBSTRING(value, 0, MP_MIN(a_Index1, a_Index2));
            }
        }
        if (isAnyText)
        {
            if (MP_STRING_CONTAINS(value, "{{{"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "{{{", "{<<<{{>>>");
            }
            if (MP_STRING_CONTAINS(value, "}}}"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "}}}", "}<<<}}>>>");
            }
            if (MP_STRING_CONTAINS(value, "((("))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "(((", "(<<<((>>>");
            }
            if (MP_STRING_CONTAINS(value, ")))"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, ")))", ")<<<))>>>");
            }
            if (MP_STRING_CONTAINS(value, "###"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "###", "#<<<##>>>");
            }
            if (MP_STRING_CONTAINS(value, "@@@"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "@@@", "@[[[64]]]@");
            }
            if (MP_STRING_CONTAINS(value, "&&&"))
            {
                a_Result = MP_STRING_REPLACE(a_Result, "&&&", "&[[[38]]]&");
            }
        }
        return MP_STRING_TRIM(a_Result);
    }
    return "";
}

MP_STRING atom::Trace::GetMultiLine(MP_STRING value)
{
    if (MP_STRING_EMPTY(value) == false)
    {
        auto a_Result = value;
        if (MP_STRING_CONTAINS(a_Result, "\r") || MP_STRING_CONTAINS(a_Result, "\n"))
        {
            a_Result = MP_STRING_REPLACE(a_Result, "\r\n", pattern::data::Message::TML::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\r", pattern::data::Message::TML::NEW_LINE);
            a_Result = MP_STRING_REPLACE(a_Result, "\n", pattern::data::Message::TML::NEW_LINE);
        }
        return GetFirstLine(a_Result, true);
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

MP_STRING atom::Trace::GetUrlMediaType(MP_STRING url)
{
    if (MP_STRING_EMPTY(url) == false)
    {
        auto a_Name = MP_STRING_LOWER(MP_FOLDER_EXTENSION_GET(url));
        if (MP_STRING_EMPTY(a_Name) == false)
        {
            {
                if (a_Name == ".bin") return "application/octet-stream";
                if (a_Name == ".cda") return "application/x-cdf";
                if (a_Name == ".csh") return "application/x-csh";
                if (a_Name == ".doc") return "application/msword";
                if (a_Name == ".docx") return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
                if (a_Name == ".eot") return "application/vnd.ms-fontobject";
                if (a_Name == ".jsn") return "application/json";
                if (a_Name == ".json") return "application/json";
                if (a_Name == ".ogx") return "application/ogg";
                if (a_Name == ".pdf") return "application/pdf";
                if (a_Name == ".php") return "application/x-httpd-php";
                if (a_Name == ".ppt") return "application/vnd.ms-powerpoint";
                if (a_Name == ".pptx") return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
                if (a_Name == ".rtf") return "application/rtf";
                if (a_Name == ".sh") return "application/x-sh";
                if (a_Name == ".tml") return "application/tml";
                if (a_Name == ".xhtml") return "application/xhtml+xml";
                if (a_Name == ".xls") return "application/vnd.ms-excel";
                if (a_Name == ".xlsx") return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
                if (a_Name == ".xml") return "application/xml";
                if (a_Name == ".yaml") return "application/yml";
                if (a_Name == ".yml") return "application/yml";
            }
            {
                if (a_Name == ".7z") return "application/x-7z-compressed";
                if (a_Name == ".arc") return "application/x-freearc";
                if (a_Name == ".bz") return "application/x-bzip";
                if (a_Name == ".bz2") return "application/x-bzip2";
                if (a_Name == ".gz") return "application/gzip";
                if (a_Name == ".gzip") return "application/gzip";
                if (a_Name == ".jar") return "application/java-archive";
                if (a_Name == ".rar") return "application/vnd.rar";
                if (a_Name == ".tar") return "application/x-tar";
                if (a_Name == ".tex") return "application/x-tex";
                if (a_Name == ".zip") return "application/zip";
            }
            {
                if (a_Name == ".aac") return "audio/aac";
                if (a_Name == ".flac") return "audio/flac";
                if (a_Name == ".midi") return "audio/midi";
                if (a_Name == ".mka") return "audio/mka";
                if (a_Name == ".mp3") return "audio/mpeg";
                if (a_Name == ".oga") return "audio/ogg";
                if (a_Name == ".opus") return "audio/opus";
                if (a_Name == ".wma") return "audio/x-ms-wma";
                if (a_Name == ".wax") return "audio/x-ms-wax";
                if (a_Name == ".wav") return "audio/wav";
                if (a_Name == ".weba") return "audio/webm";
            }
            {
                if (a_Name == ".avif") return "image/avif";
                if (a_Name == ".azv") return "image/vnd.amazon.ebook";
                if (a_Name == ".bmp") return "image/bmp";
                if (a_Name == ".cur") return "image/vnd.microsoft.icon";
                if (a_Name == ".gif") return "image/gif";
                if (a_Name == ".ico") return "image/vnd.microsoft.icon";
                if (a_Name == ".jfif") return "image/jpeg";
                if (a_Name == ".jif") return "image/jpeg";
                if (a_Name == ".jpe") return "image/jpeg";
                if (a_Name == ".jpeg") return "image/jpeg";
                if (a_Name == ".jpg") return "image/jpeg";
                if (a_Name == ".jps") return "image/jpeg";
                if (a_Name == ".png") return "image/png";
                if (a_Name == ".svg") return "image/svg+xml";
                if (a_Name == ".tif") return "image/tiff";
                if (a_Name == ".tiff") return "image/tiff";
                if (a_Name == ".webp") return "image/webp";
            }
            {
                if (a_Name == ".otf") return "font/otf";
                if (a_Name == ".ttf") return "font/ttf";
                if (a_Name == ".woff") return "font/woff";
                if (a_Name == ".woff2") return "font/woff2";
            }
            {
                if (a_Name == ".iges") return "model/iges";
                if (a_Name == ".igs") return "model/iges";
                if (a_Name == ".mesh") return "model/mesh";
                if (a_Name == ".msh") return "model/mesh";
                if (a_Name == ".x3d") return "model/x3d+xml";
            }
            {
                if (a_Name == ".bat") return "text/cmd";
                if (a_Name == ".cmd") return "text/cmd";
                if (a_Name == ".css") return "text/css";
                if (a_Name == ".csv") return "text/csv";
                if (a_Name == ".htm") return "text/html";
                if (a_Name == ".html") return "text/html";
                if (a_Name == ".ics") return "text/calendar";
                if (a_Name == ".js") return "text/javascript";
                if (a_Name == ".mjs") return "text/javascript";
                if (a_Name == ".md") return "text/markdown";
                if (a_Name == ".php") return "text/php";
                if (a_Name == ".txt") return "text/plain";
            }
            {
                if (a_Name == ".3g2") return "video/3gpp2";
                if (a_Name == ".3gp") return "video/3gpp";
                if (a_Name == ".3gpp") return "video/3gpp";
                if (a_Name == ".3gpp2") return "video/3gpp2";
                if (a_Name == ".avi") return "video/x-msvideo";
                if (a_Name == ".avif") return "video/avif";
                if (a_Name == ".flv") return "video/x-flv";
                if (a_Name == ".mkv") return "video/mkv";
                if (a_Name == ".mp4") return "video/mp4";
                if (a_Name == ".mpeg") return "video/mpeg";
                if (a_Name == ".mpg") return "video/mpeg";
                if (a_Name == ".ogg") return "video/ogg";
                if (a_Name == ".ogv") return "video/ogg";
                if (a_Name == ".qt") return "video/quicktime";
                if (a_Name == ".ts") return "video/mp2t";
                if (a_Name == ".webm") return "video/webm";
                if (a_Name == ".wmv") return "video/x-ms-wmv";
            }
        }
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
        (MP_NEW atom::Trace())->SendTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, MP_EXCEPTION_MESSAGE_GET(ex));
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
        m_Value = "";
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::BeginTransaction(MP_STRING sender)
{
    if (this != nullptr)
    {
        {
            m_Transaction++;
        }
        if (MP_STRING_EMPTY(m_Sender))
        {
            m_Sender = sender;
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::CancelTransaction()
{
    if (this != nullptr)
    {
        m_Transaction = 0;
        m_Sender = "";
        m_Queue = "";
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::CommitTransaction()
{
    if (this != nullptr)
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
    return this;
}

MP_PTR(atom::Trace) atom::Trace::EndTransaction()
{
    if (this != nullptr)
    {
        if (m_Transaction > 0)
        {
            m_Transaction--;
        }
        if (m_Transaction <= 0)
        {
            CommitTransaction();
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
                a_Context += m_Comment;
                a_Context += m_Url;
                a_Context += m_UrlInfo;
                a_Context += m_UrlPreview;
                a_Context += m_Value;
                a_Context += m_Tml;
                a_Context += "\n";
            }
            if (MP_STRING_EMPTY(m_Content) && (MP_STRING_EMPTY(a_Context) == false))
            {
                a_Context =
                    GetLevel(level) +
                    m_Content +
                    MP_STRING_SUBSTRING(a_Context, 1, MP_STRING_SIZE_GET(a_Context) - 1);
            }
            else
            {
                a_Context =
                    GetLevel(level) +
                    m_Content +
                    a_Context;
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

MP_PTR(atom::Trace) atom::Trace::SendPreviewMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING url, MP_INT state, MP_INT progress)
{
    return SendTml(TML::MESSAGE::GetPreviewMessage(level, source, event, url, state, progress));
}

MP_PTR(atom::Trace) atom::Trace::SendToolMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING id, MP_INT state)
{
    return SendTml(TML::MESSAGE::GetToolMessage(level, source, event, content, id, state));
}

MP_PTR(atom::Trace) atom::Trace::SendTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content)
{
    auto a_Context = atom::Trace::TML::MESSAGE::GetTraceMessage(level, source, event, content, "", "", "");
    if ((source == pattern::data::Source::NAME::DIAGNOSTIC) || (source == pattern::data::Source::NAME::METAREPORT))
    {
        if (level == 0)
        {
            auto a_IsFound =
                (event == pattern::data::Event::NAME::EMERGENCY) ||
                (event == pattern::data::Event::NAME::CRITICAL) ||
                (event == pattern::data::Event::NAME::ERROR) ||
                (event == pattern::data::Event::NAME::WARNING);
            if (a_IsFound)
            {
                a_Context += TML::MESSAGE::GetNextTrace() + __GetStackTrace(source, 1, 2) + TML::MESSAGE::GetNextTrace();
            }
        }
        {
            MP_TRACE_DEBUG(a_Context);
        }
    }
    else
    {
        SendTml(a_Context);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SendTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING message, MP_STRING hint, MP_STRING params)
{
    auto a_Context = atom::Trace::TML::MESSAGE::GetTraceMessage(level, source, event, content, message, hint, params);
    if ((source == pattern::data::Source::NAME::DIAGNOSTIC) || (source == pattern::data::Source::NAME::METAREPORT))
    {
        if (level == 0)
        {
            auto a_IsFound =
                (event == pattern::data::Event::NAME::EMERGENCY) ||
                (event == pattern::data::Event::NAME::CRITICAL) ||
                (event == pattern::data::Event::NAME::ERROR) ||
                (event == pattern::data::Event::NAME::WARNING);
            if (a_IsFound)
            {
                a_Context += TML::MESSAGE::GetNextTrace() + __GetStackTrace(source, 1, 2) + TML::MESSAGE::GetNextTrace();
            }
        }
        {
            MP_TRACE_DEBUG(a_Context);
        }
    }
    else
    {
        SendTml(a_Context);
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
            MP_TRACE_DEBUG(TML::MESSAGE::GetTraceMessage(0, pattern::data::Source::NAME::DIAGNOSTIC, pattern::data::Event::NAME::EXCEPTION, ex->Message, "", "", "") + TML::MESSAGE::GetNextTrace());
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

// Public ##############
MP_PTR(atom::Trace) atom::Trace::SetAlignment(MP_INT value)
{
    if ((this != nullptr) && (value != pattern::data::Font::STATE::NONE))
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            {
                m_Control += " &&&ALIGNMENT";
            }
            {
                if ((value & pattern::data::Alignment::NAME::CLIENT) == pattern::data::Alignment::NAME::CLIENT) m_Control += " CLIENT";
                if ((value & pattern::data::Alignment::NAME::CENTER) == pattern::data::Alignment::NAME::CENTER) m_Control += " CENTER";
                if ((value & pattern::data::Alignment::NAME::LEFT) == pattern::data::Alignment::NAME::LEFT) m_Control += " LEFT";
                if ((value & pattern::data::Alignment::NAME::TOP) == pattern::data::Alignment::NAME::TOP) m_Control += " TOP";
                if ((value & pattern::data::Alignment::NAME::RIGHT) == pattern::data::Alignment::NAME::RIGHT) m_Control += " RIGHT";
                if ((value & pattern::data::Alignment::NAME::BOTTOM) == pattern::data::Alignment::NAME::BOTTOM) m_Control += " BOTTOM";
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetBackground(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Background = " &&&BACKGROUND " + pattern::data::Color::GetValue(value);
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
            m_Comment = " " + GetFirstLine(value, true);
        }
        if (hint != nullptr)
        {
            m_Comment += " &&&HINT " + GetMultiLine(hint);
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
            auto a_Context = GetMultiLine(value1);
            if (MP_STRING_EMPTY(a_Context) == false)
            {
                m_Condition += " &&&VALUE1 " + a_Context;
            }
        }
        {
            auto a_Context = GetMultiLine(value2);
            if (MP_STRING_EMPTY(a_Context) == false)
            {
                m_Condition += " &&&VALUE2 " + a_Context;
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetContent(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        m_Content = GetMultiLine(value);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name)
{
    return SetControl(name, nullptr, nullptr, pattern::data::Control::STATE::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name, MP_STRING hint)
{
    return SetControl(name, hint, nullptr, pattern::data::Control::STATE::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetControl(MP_STRING name, MP_STRING hint, MP_STRING tool, MP_INT state)
{
    if ((this != nullptr) && (name != nullptr))
    {
        {
            m_Control = " @@@CONTROL " + GetFirstLine(name, false);
        }
        if (hint != nullptr)
        {
            m_Control += " &&&HINT " + GetMultiLine(hint);
        }
        if (tool != nullptr)
        {
            m_Control += " &&&TOOL " + GetFirstLine(tool, false);
        }
        if (state != pattern::data::Control::STATE::NONE)
        {
            {
                m_Control += " &&&STATE";
            }
            {
                if ((state & pattern::data::Control::STATE::BLINK) == pattern::data::Control::STATE::BLINK) m_Control += " BLINK";
                if ((state & pattern::data::Control::STATE::BLUR) == pattern::data::Control::STATE::BLUR) m_Control += " BLUR";
                if ((state & pattern::data::Control::STATE::DISABLED) == pattern::data::Control::STATE::DISABLED) m_Control += " DISABLED";
                if ((state & pattern::data::Control::STATE::INFINITE) == pattern::data::Control::STATE::INFINITE) m_Control += " INFINITE";
                if ((state & pattern::data::Control::STATE::MUTE) == pattern::data::Control::STATE::MUTE) m_Control += " MUTE";
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetCount(MP_INT value)
{
    if ((this != nullptr) && (value > 0))
    {
        m_Count = " &&&COUNT " + MP_CONVERT_STRING_FROM_INT(value, 0);
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
    return SetFont(name, size, pattern::data::Message::STATE::NONE);
}

MP_PTR(atom::Trace) atom::Trace::SetFont(MP_STRING name, MP_INT size, MP_INT state)
{
    if (this != nullptr)
    {
        {
            m_Font = "";
        }
        if (MP_STRING_EMPTY(name) == false)
        {
            m_Font += " &&&FONT.NAME " + GetFirstLine(name, false);
        }
        if (size > 0)
        {
            m_Font += " &&&FONT.SIZE " + MP_CONVERT_STRING_FROM_INT(size, 0);
        }
        if (state != pattern::data::Font::STATE::NONE)
        {
            {
                m_Font += " &&&FONT.STATE";
            }
            {
                if ((state & pattern::data::Font::STATE::BOLD) == pattern::data::Font::STATE::BOLD) m_Font += " BOLD";
                if ((state & pattern::data::Font::STATE::ITALIC) == pattern::data::Font::STATE::ITALIC) m_Font += " ITALIC";
                if ((state & pattern::data::Font::STATE::STRIKEOUT) == pattern::data::Font::STATE::STRIKEOUT) m_Font += " STRIKEOUT";
                if ((state & pattern::data::Font::STATE::UNDERLINE) == pattern::data::Font::STATE::UNDERLINE) m_Font += " UNDERLINE";
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetForeground(MP_INT value)
{
    if ((this != nullptr) && (value != 0))
    {
        m_Foreground = " &&&FOREGROUND " + pattern::data::Color::GetValue(value);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetMargin(MP_INT x, MP_INT y)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " &&&MARGIN.X " + MP_CONVERT_STRING_FROM_INT(x, 0);
            m_Control += " &&&MARGIN.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
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
            m_Control += " &&&PADDING " + MP_CONVERT_STRING_FROM_INT(value, 0);
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
            m_Control += " &&&PADDING.MIN.X " + MP_CONVERT_STRING_FROM_INT(minX, 0);
            m_Control += " &&&PADDING.MIN.Y " + MP_CONVERT_STRING_FROM_INT(minY, 0);
            m_Control += " &&&PADDING.MAX.X " + MP_CONVERT_STRING_FROM_INT(maxX, 0);
            m_Control += " &&&PADDING.MAX.Y " + MP_CONVERT_STRING_FROM_INT(maxY, 0);
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
            m_Progress = " &&&PROGRESS " + MP_CONVERT_STRING_FROM_DOUBLE(value);
        }
        if (hint != nullptr)
        {
            m_Progress += " &&&PROGRESS.HINT " + GetMultiLine(hint);
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
            m_Control += " &&&SIZE.X " + MP_CONVERT_STRING_FROM_INT(x, 0);
            m_Control += " &&&SIZE.Y " + MP_CONVERT_STRING_FROM_INT(y, 0);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond)
{
    if (this != nullptr)
    {
        m_Time = " &&&TIME " +
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
            m_Trace = " @@@MESSAGE " + id;
        }
        if (state != pattern::data::Message::STATE::NONE)
        {
            {
                m_Trace += " &&&STATE";
            }
            {
                if ((state & pattern::data::Message::STATE::BEEP) == pattern::data::Message::STATE::BEEP) m_Trace += " BEEP";
                if ((state & pattern::data::Message::STATE::BLINK) == pattern::data::Message::STATE::BLINK) m_Trace += " BLINK";
                if ((state & pattern::data::Message::STATE::CLEAR) == pattern::data::Message::STATE::CLEAR) m_Trace += " CLEAR";
                if ((state & pattern::data::Message::STATE::COLLAPSE) == pattern::data::Message::STATE::COLLAPSE) m_Trace += " COLLAPSE";
                if ((state & pattern::data::Message::STATE::EXPAND) == pattern::data::Message::STATE::EXPAND) m_Trace += " EXPAND";
                if ((state & pattern::data::Message::STATE::FIX) == pattern::data::Message::STATE::FIX) m_Trace += " FIX";
                if ((state & pattern::data::Message::STATE::FOCUS) == pattern::data::Message::STATE::FOCUS) m_Trace += " FOCUS";
                if ((state & pattern::data::Message::STATE::HIDE) == pattern::data::Message::STATE::HIDE) m_Trace += " HIDE";
                if ((state & pattern::data::Message::STATE::LOCK) == pattern::data::Message::STATE::LOCK) m_Trace += " LOCK";
                if ((state & pattern::data::Message::STATE::MUTE) == pattern::data::Message::STATE::MUTE) m_Trace += " MUTE";
                if ((state & pattern::data::Message::STATE::PIN) == pattern::data::Message::STATE::PIN) m_Trace += " PIN";
                if ((state & pattern::data::Message::STATE::REMOVE) == pattern::data::Message::STATE::REMOVE) m_Trace += " REMOVE";
                if ((state & pattern::data::Message::STATE::RESEND) == pattern::data::Message::STATE::RESEND) m_Trace += " RESEND";
                if ((state & pattern::data::Message::STATE::SHOW) == pattern::data::Message::STATE::SHOW) m_Trace += " SHOW";
                if ((state & pattern::data::Message::STATE::SPEAK) == pattern::data::Message::STATE::SPEAK) m_Trace += " SPEAK";
                if ((state & pattern::data::Message::STATE::UNFIX) == pattern::data::Message::STATE::UNFIX) m_Trace += " UNFIX";
                if ((state & pattern::data::Message::STATE::UNFOCUS) == pattern::data::Message::STATE::UNFOCUS) m_Trace += " UNFOCUS";
                if ((state & pattern::data::Message::STATE::UNLOCK) == pattern::data::Message::STATE::UNLOCK) m_Trace += " UNLOCK";
                if ((state & pattern::data::Message::STATE::UNPIN) == pattern::data::Message::STATE::UNPIN) m_Trace += " UNPIN";
                if ((state & pattern::data::Message::STATE::UPDATE) == pattern::data::Message::STATE::UPDATE) m_Trace += " UPDATE";
            }
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTranslation(MP_STRING culture, MP_STRING value)
{
    if ((this != nullptr) && (MP_STRING_EMPTY(culture) == false) && (MP_STRING_EMPTY(value) == false))
    {
        m_Value += " @@@TRANSLATION.APPEND &&&CULTURE " + culture + " &&&VALUE " + GetFirstLine(value, false);
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetTransparency(MP_DOUBLE value)
{
    if (this != nullptr)
    {
        if (MP_STRING_EMPTY(m_Control) == false)
        {
            m_Control += " &&&TRANSPARENCY " + MP_CONVERT_STRING_FROM_DOUBLE(value);
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
            m_Url = " &&&URL " + GetFirstLine(value, false);
        }
        if (MP_STRING_EMPTY(hint) == false)
        {
            m_Url += " &&&URL.HINT " + GetMultiLine(hint);
        }
        if (line > 0)
        {
            m_Url += " &&&URL.LINE " + MP_CONVERT_STRING_FROM_INT(line, 0);
        }
        if (position > 0)
        {
            m_Url += " &&&URL.POSITION " + MP_CONVERT_STRING_FROM_INT(position, 0);
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
            m_UrlInfo = " &&&URL.INFO " + GetFirstLine(value, false);
        }
        if (hint != nullptr)
        {
            m_UrlInfo += " &&&URL.INFO.HINT " + GetMultiLine(hint);
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
            m_UrlPreview = " &&&URL.PREVIEW " + GetFirstLine(value, false);
        }
        if (hint != nullptr)
        {
            m_UrlPreview += " &&&URL.PREVIEW.HINT " + GetMultiLine(hint);
        }
    }
    return this;
}

MP_PTR(atom::Trace) atom::Trace::SetValue(MP_STRING value)
{
    if ((this != nullptr) && (value != nullptr))
    {
        m_Value = " &&&VALUE " + GetMultiLine(value);
    }
    return this;
}

// Private #############
MP_PTR(MP_THREAD_MUTEX) atom::Trace::__GetMutex()
{
    if (s_Mutex == nullptr)
    {
        MP_THREAD_MUTEX_INITIALIZE(s_Mutex, pattern::data::Message::CONSTANT::PIPE::MUTEX, false);
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
        if (source == pattern::data::Source::NAME::CONSOLE)
        {
            return MP_STRING_REPLACE(a_Context, "\n", " @@@SOURCE CONSOLE\n");
        }
        else
        {
            auto a_TextBuffer = MP_STRING_BUFFER_GET(a_Context);
            auto a_TextSize = MP_STRING_SIZE_GET(a_Context);
            auto a_Result = MP_NEW System::Text::StringBuilder(a_TextSize * 2);
            auto a_Context1 = (MP_STRING)"";
            if (a_TextSize > pattern::data::Message::CONSTANT::OUTPUT::MAX_BUFFER_SIZE)
            {
                return "[[[Too big input]]] TML @@@SOURCE METAOUTPUT @@@EVENT CRITICAL";
            }
            if (a_TextSize > 0)
            {
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
                        a_Result->Append(a_Context2);
                        a_Context1 += a_Context2;
                    }
                    if (MP_STRING_CONTAINS(a_Context1, "@@@SOURCE ") == false)
                    {
                        a_Result->Append(" @@@SOURCE " + source);
                    }
                    if (a_Context2 == '\n')
                    {
                        a_Result->Append(a_Context2);
                    }
                    {
                        a_Context1 = "";
                    }
                }
                else
                {
                    a_Result->Append(a_Context2);
                    a_Context1 += a_Context2;
                }
            }
            return a_Result->ToString();
        }
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
            auto a_Count = extension::AnyPreview::GetProperty(extension::AnyPreview::VARIABLE::DEBUGGING::STACK_SIZE, true);
            for (auto i = skip; (i < a_Size) && (a_Count > 0); i++)
            {
                auto a_Context1 = MP_STACKTRACE_FRAME_GET(a_Context, i);
                if (a_Context1 != nullptr)
                {
                    if (MP_STRING_EMPTY(MP_STACKFRAME_FILE_NAME_GET(a_Context1)))
                    {
                        continue;
                    }
                    else
                    {
                        a_Count--;
                    }
                    {
                        auto a_Context2 = (MP_STRING)"";
                        auto a_Size1 = MP_STACKFRAME_METHOD_PARAM_COUNT_GET(a_Context1);
                        for (auto ii = 0; ii < a_Size1; ii++)
                        {
                            auto a_Context3 = MP_STACKFRAME_METHOD_PARAM_GET(a_Context1, ii);
                            {
                                a_Context2 += ((ii == 0) ? "" : ", ") + MP_STACKPARAM_TYPE_NAME_GET(a_Context3) + " " + MP_STACKPARAM_NAME_GET(a_Context3);
                            }
                        }
                        {
                            a_Result += TML::MESSAGE::GetTraceMessage(level, __GetSource(source), pattern::data::Event::NAME::FUNCTION, MP_STACKFRAME_METHOD_NAME_GET(a_Context1) + "(" + a_Context2 + ")", "<" + MP_STACKFRAME_MODULE_NAME_GET(a_Context1) + ">", "<[[[Module Name]]]>",
                                TML::MESSAGE::PARAM::GetUrl(MP_STACKFRAME_FILE_NAME_GET(a_Context1), "", MP_STACKFRAME_FILE_LINE_GET(a_Context1), MP_STACKFRAME_FILE_POSITION_GET(a_Context1)));
                            a_Result += TML::MESSAGE::GetNextTrace();
                        }
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
                extension::AnyTool::Execute("", a_Context);
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
