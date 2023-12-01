#pragma warning disable CA1305 // Specify IFormatProvider
#pragma warning disable CA1707 // Identifiers should not contain underscores
#pragma warning disable CA1716 // Identifiers should not match keywords

using extension;
using pattern.data;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text;
using System.Threading;

namespace atom
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public sealed class Trace : basic.AnyAtom
    {
        private static Mutex s_Mutex;
        private static Thread s_TraceThread;
        private static string s_TraceBuffer;
        private int m_Transaction;
        private string m_Sender;
        private StringBuilder m_Buffer;

        private sealed class CONSTANT : AnyPreview.CONSTANT
        {
        }

        private sealed class NAME : AnyPreview.NAME
        {
        }

        private sealed class STATE : AnyPreview.STATE
        {
        }

        public class TML
        {
            public class CONTROL
            {
                public class PARAM
                {
                    public static string GetBackground(string value)
                    {
                        return "&&&BACKGROUND " + GetFirstLine(value, false) + " ";
                    }

                    public static string GetBackground(uint value)
                    {
                        return "&&&BACKGROUND " + Color.ToString(value) + " ";
                    }

                    public static string GetCount(int value)
                    {
                        string a_Result = "";
                        if (value > 0)
                        {
                            a_Result += "&&&COUNT " + value.ToString("d0") + " ";
                        }
                        return a_Result;
                    }

                    public static string GetFont(string name, int size, int state)
                    {
                        string a_Result = "";
                        if (!string.IsNullOrEmpty(name))
                        {
                            a_Result += "&&&FONT.NAME " + GetFirstLine(name, false) + " ";
                        }
                        if (size > 0)
                        {
                            a_Result += "&&&FONT.SIZE " + size.ToString("d0") + " ";
                        }
                        if (state != STATE.FONT.NONE)
                        {
                            a_Result += "&&&FONT.STATE " + pattern.data.Font.ToString(state) + " ";
                        }
                        return a_Result;
                    }

                    public static string GetFont(string name, int size)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(name))
                        {
                            a_Result += "&&&FONT.NAME " + GetFirstLine(name, false) + " ";
                        }
                        if (size > 0)
                        {
                            a_Result += "&&&FONT.SIZE " + size.ToString("d0") + " ";
                        }
                        return a_Result;
                    }

                    public static string GetForeground(string value)
                    {
                        return "&&&FOREGROUND " + GetFirstLine(value, false) + " ";
                    }

                    public static string GetForeground(uint value)
                    {
                        return "&&&FOREGROUND " + Color.ToString(value) + " ";
                    }

                    public static string GetHandler(string tool, string id, AnyHandler handler)
                    {
                        string result = "";
                        if (!string.IsNullOrEmpty(tool))
                        {
                            {
                                AnyTool.Register(tool, id, handler);
                            }
                            {
                                result = "&&&TOOL " + GetFirstLine(tool, false);
                            }
                            if (!string.IsNullOrEmpty(id))
                            {
                                result += " &&&ID " + GetFirstLine(id, false);
                            }
                            return result + " ";
                        }
                        return result;
                    }

                    public static string GetHint(string value)
                    {
                        var a_Result = GetMultiLine(value);
                        if (!string.IsNullOrEmpty(a_Result))
                        {
                            return "&&&HINT " + a_Result + " ";
                        }
                        return a_Result;
                    }

                    public static string GetMargin(int x, int y)
                    {
                        var a_Result = "";
                        if (x != 0)
                        {
                            a_Result += "&&&MARGIN.X " + x.ToString("d0") + " ";
                        }
                        if (y != 0)
                        {
                            a_Result += "&&&MARGIN.Y " + y.ToString("d0") + " ";
                        }
                        return a_Result;
                    }

                    public static string GetState(int state)
                    {
                        var a_Result = "";
                        if (state != STATE.FONT.NONE)
                        {
                            {
                                a_Result += "&&&STATE";
                            }
                            if ((state & STATE.CONTROL.BLINK) == STATE.CONTROL.BLINK) a_Result += " BLINK";
                            if ((state & STATE.CONTROL.BLUR) == STATE.CONTROL.BLUR) a_Result += " BLUR";
                            if ((state & STATE.CONTROL.DISABLE) == STATE.CONTROL.DISABLE) a_Result += " DISABLE";
                            if ((state & STATE.CONTROL.FIX) == STATE.CONTROL.FIX) a_Result += " FIX";
                            if ((state & STATE.CONTROL.INFINITE) == STATE.CONTROL.INFINITE) a_Result += " INFINITE";
                            if ((state & STATE.CONTROL.MUTE) == STATE.CONTROL.MUTE) a_Result += " MUTE";
                            {
                                a_Result += " ";
                            }
                        }
                        return a_Result;
                    }

                    public static string GetPadding(int minX, int minY, int maxX, int maxY)
                    {
                        var a_Result = "";
                        if (minX != 0)
                        {
                            a_Result += "&&&PADDING.MIN.X " + minX.ToString("d0") + " ";
                        }
                        if (minY != 0)
                        {
                            a_Result += "&&&PADDING.MIN.Y " + minY.ToString("d0") + " ";
                        }
                        if (maxX != 0)
                        {
                            a_Result += "&&&PADDING.MAX.X " + maxX.ToString("d0") + " ";
                        }
                        if (maxY != 0)
                        {
                            a_Result += "&&&PADDING.MAX.Y " + maxY.ToString("d0") + " ";
                        }
                        return a_Result;
                    }

                    public static string GetPadding(int value)
                    {
                        if (value != 0)
                        {
                            return "&&&PADDING " + value.ToString("d0") + " ";
                        }
                        return "";
                    }

                    public static string GetTransparency(int value)
                    {
                        if (value >= 0)
                        {
                            return "&&&TRANSPARENCY " + value.ToString("d0") + " ";
                        }
                        return "";
                    }

                    public static string GetUrl(string value)
                    {
                        if (!string.IsNullOrEmpty(value))
                        {
                            return "&&&URL " + GetFirstLine(value, false) + " ";
                        }
                        return "";
                    }
                }

                public static string GetAudio(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("AUDIO", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetBrowser(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("BROWSER", level, source, "", alignment, sizeX, sizeY, @params) + "&&&URL " + content + " ";
                }

                public static string GetButton(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("BUTTON", level, source, GetMultiLine(content), alignment, sizeX, sizeY, @params);
                }

                public static string GetCanvas(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("CANVAS", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetChart(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("CHART", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetCheckBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("CHECKBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetComboBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("COMBOBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetEditBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("EDITBOX", level, source, GetFirstLine(content, true), alignment, sizeX, sizeY, @params);
                }

                public static string GetGallery(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("GALLERY", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetGauge(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("GAUGE", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetItem(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("ITEM", level, source, GetMultiLine(content), alignment, sizeX, sizeY, @params);
                }

                public static string GetLabel(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("LABEL", level, source, GetMultiLine(content), alignment, sizeX, sizeY, @params);
                }

                public static string GetLink(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("LINK", level, source, GetFirstLine(content, true), alignment, sizeX, sizeY, @params);
                }

                public static string GetPanel(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("PANEL", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetPicture(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("PICTURE", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetProgressBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("PROGRESSBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetRadioBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("RADIOBOX", level, source, GetFirstLine(content, true), alignment, sizeX, sizeY, @params);
                }

                public static string GetScrollBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("SCROLLBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetSlideBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("SLIDEBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetSplitter(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("SPLITTER", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetTabBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("TABBOX", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetTable(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("TABLE", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetTextBox(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("TEXTBOX", level, source, GetMultiLine(content), alignment, sizeX, sizeY, @params);
                }

                public static string GetTree(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("TREE", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetVideo(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("VIDEO", level, source, content, alignment, sizeX, sizeY, @params);
                }

                public static string GetWindow(int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    return __GetTml("WINDOW", level, source, GetFirstLine(content, true), alignment, sizeX, sizeY, @params);
                }

                private static string __GetTml(string control, int level, string source, string content, int alignment, int sizeX, int sizeY, string @params)
                {
                    var a_Result = GetLevel(level) + "@@@SOURCE " + GetFirstLine(source, false) + " @@@CONTROL " + control;
                    if (alignment != NAME.ALIGNMENT.NONE)
                    {
                        {
                            a_Result += " &&&ALIGNMENT";
                        }
                        if ((alignment & NAME.ALIGNMENT.CLIENT) == NAME.ALIGNMENT.CLIENT)
                        {
                            a_Result += " CLIENT";
                        }
                        else
                        {
                            if ((alignment & NAME.ALIGNMENT.CENTER) == NAME.ALIGNMENT.CENTER) a_Result += " CENTER";
                            if ((alignment & NAME.ALIGNMENT.CONTENT) == NAME.ALIGNMENT.CONTENT) a_Result += " CONTENT";
                            if ((alignment & NAME.ALIGNMENT.LEFT) == NAME.ALIGNMENT.LEFT) a_Result += " LEFT";
                            if ((alignment & NAME.ALIGNMENT.TOP) == NAME.ALIGNMENT.TOP) a_Result += " TOP";
                            if ((alignment & NAME.ALIGNMENT.RIGHT) == NAME.ALIGNMENT.RIGHT) a_Result += " RIGHT";
                            if ((alignment & NAME.ALIGNMENT.BOTTOM) == NAME.ALIGNMENT.BOTTOM) a_Result += " BOTTOM";
                        }
                    }
                    if (sizeX != 0)
                    {
                        a_Result += " &&&SIZE.X " + sizeX.ToString("d0");
                    }
                    if (sizeY != 0)
                    {
                        a_Result += " &&&SIZE.Y " + sizeY.ToString("d0");
                    }
                    if (!string.IsNullOrEmpty(@params))
                    {
                        a_Result += " " + @params.Trim();
                    }
                    if (!string.IsNullOrWhiteSpace(content))
                    {
                        a_Result += " &&&VALUE " + content.Trim();
                    }
                    return a_Result + " ";
                }
            }

            public class EVENT
            {
                public static string GetAppend(string name, string picture)
                {
                    return "@@@EVENT.APPEND " + GetFirstLine(name, false) + " &&&VALUE " + GetFirstLine(picture, false) + " ";
                }

                public static string GetRemove(string name)
                {
                    return "@@@EVENT.REMOVE " + GetFirstLine(name, false) + " ";
                }
            }

            public class EXTENSION
            {
                public static string GetActionBox(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(background)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(background)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.ACTION.TRANSPARENCY)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0, "");
                }

                public static string GetActionButton(int level, string source, string content, uint background, uint foreground, int alignment, int size, string url)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, CONSTANT.CONTROL.ACTION.SIZE_Y, CONSTANT.CONTROL.ACTION.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPicture(level + 1, source, content, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2), CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2),
                            CONTROL.PARAM.GetUrl(url));
                }

                public static string GetActionButton(int level, string source, string content, uint background, uint foreground, int alignment, int size, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, CONSTANT.CONTROL.ACTION.SIZE_Y, CONSTANT.CONTROL.ACTION.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPicture(level + 1, source, content, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2), CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2),
                            CONTROL.PARAM.GetHandler(tool, id, handler));
                }

                public static string GetActionCanvas(int level, string source, string content, uint background, uint foreground, int alignment, int size, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetCanvas(level, source, content, alignment, size, size,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetHandler(tool, id, handler));
                }

                public static string GetActionEditBox(int level, string source, string content, uint background, uint foreground, int alignment, int size, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetPanel(level, source, "", alignment, size, size,
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.WINDOW.PADDING * 4, CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.WINDOW.PADDING * 4)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetForeground(CONSTANT.CONTROL.ACTION.FOREGROUND) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.DELIMITER.SIZE_Y, CONSTANT.CONTROL.DELIMITER.SIZE_Y, CONSTANT.CONTROL.DELIMITER.SIZE_Y)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetEditBox(level + 2, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(foreground) +
                            CONTROL.PARAM.GetForeground(CONSTANT.CONTROL.ACTION.FOREGROUND) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.ACTION.FONT_NAME, CONSTANT.CONTROL.ACTION.FONT_SIZE, STATE.FONT.NONE) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, 0, CONSTANT.CONTROL.WINDOW.PADDING, 0) +
                            CONTROL.PARAM.GetHandler(tool, id, handler));
                }

                public static string GetActionIndent(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    if (size <= 0)
                    {
                        size = CONSTANT.CONTROL.WINDOW.PADDING;
                    }
                    return
                        CONTROL.GetPanel(level, source, "", alignment, size, size,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND));
                }

                public static string GetActionGallery(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetGallery(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0, "");
                }

                public static string GetActionGalleryItem(int level, string source, string content, uint background, uint foreground, string picture, int size, string url)
                {
                    return
                        CONTROL.GetItem(level, source, picture, NAME.ALIGNMENT.NONE, size, size,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetHint(content) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                            CONTROL.PARAM.GetUrl(url) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.TOOL.TRANSPARENCY));
                }

                public static string GetActionGalleryItem(int level, string source, string content, uint background, uint foreground, string picture, int size, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetItem(level, source, picture, NAME.ALIGNMENT.NONE, size, size,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetHint(content) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                            CONTROL.PARAM.GetHandler(tool, id, handler) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.TOOL.TRANSPARENCY));
                }

                public static string GetActionGalleryTitle(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetItem(level, source, content, NAME.ALIGNMENT.NONE, 0, CONSTANT.CONTROL.TITLE.SIZE_Y,
                            CONTROL.PARAM.GetBackground((background & 0x00FFFFFF) | ((0xFF - ((CONSTANT.CONTROL.HEADER.TRANSPARENCY * 0xFF) / 100)) << 24)) +
                            CONTROL.PARAM.GetForeground(foreground));
                }

                public static string GetActionLabel(int level, string source, string content, uint background, uint foreground, int alignment, bool isHighlighted)
                {
                    return
                        CONTROL.GetLabel(level, source, content, alignment, 0, 0,
                            CONTROL.PARAM.GetForeground(isHighlighted ? CONSTANT.CONTROL.ACTION.FOREGROUND : background) +
                            CONTROL.PARAM.GetTransparency(isHighlighted ? 0 : CONSTANT.CONTROL.HEADER.TRANSPARENCY) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.ACTION.FONT_NAME, CONSTANT.CONTROL.ACTION.FONT_SIZE, isHighlighted ? STATE.FONT.BOLD : STATE.FONT.NONE));
                }

                public static string GetActionProperty(int level, string source, string content, uint background, uint foreground, string value, int size, bool isHighlighted)
                {
                    var a_Result =
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.TITLE.SIZE_Y,
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, 0, CONSTANT.CONTROL.WINDOW.PADDING, 0)) + MESSAGE.GetNextTrace();
                    if (isHighlighted)
                    {
                        a_Result +=
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                                CONTROL.PARAM.GetBackground(foreground)) + MESSAGE.GetNextTrace();
                    }
                    if (!string.IsNullOrEmpty(content))
                    {
                        a_Result +=
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.LEFT, size > 0 ? size : CONSTANT.CONTROL.TITLE.SIZE_X, 0, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetLabel(level + 2, source, content, NAME.ALIGNMENT.CONTENT_RIGHT, 0, 0,
                                CONTROL.PARAM.GetForeground(background)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.WINDOW.PADDING, 0, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetLabel(level + 1, source, ":", NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                                CONTROL.PARAM.GetForeground(NAME.COLOR.GRAY)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.WINDOW.PADDING, 0, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetLabel(level + 1, source, GetFirstLine(value, true), NAME.ALIGNMENT.CLIENT, 0, 0,
                                CONTROL.PARAM.GetForeground(CONSTANT.CONTROL.ACTION.FOREGROUND) +
                                CONTROL.PARAM.GetFont(null, 0, STATE.FONT.BOLD));
                    }
                    return a_Result;
                }

                public static string GetActionPicture(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    if (!string.IsNullOrEmpty(content))
                    {
                        return CONTROL.GetPicture(level, source, content, alignment, size, size, "");
                    }
                    return "";
                }

                public static string GetActionPreview(int level, string source, string content, uint background, uint foreground, int alignment)
                {
                    switch (Control.GetName(content))
                    {
                        case NAME.CONTROL.PICTURE:
                            return
                                CONTROL.GetPanel(level, source, "", alignment, CONSTANT.CONTROL.ACTION.SIZE_Y, CONSTANT.CONTROL.ACTION.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                                CONTROL.GetPicture(level + 1, source, content, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2), CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2),
                                    CONTROL.PARAM.GetHint("[[[Preview]]]"));
                        case NAME.CONTROL.VIDEO:
                            return
                                CONTROL.GetPanel(level, source, "", alignment, CONSTANT.CONTROL.ACTION.SIZE_Y, CONSTANT.CONTROL.ACTION.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                                CONTROL.GetVideo(level + 1, source, content, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2), CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2),
                                    CONTROL.PARAM.GetHint("[[[Preview]]]"));
                        default:
                            return
                                CONTROL.GetPanel(level, source, "", alignment, CONSTANT.CONTROL.ACTION.SIZE_Y, CONSTANT.CONTROL.ACTION.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                                CONTROL.GetPicture(level + 1, source, CONSTANT.CONTROL.RESOURCE.PICTURE_FILE, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2), CONSTANT.CONTROL.ACTION.SIZE_Y - (CONSTANT.CONTROL.WINDOW.PADDING * 2),
                                    CONTROL.PARAM.GetHint("[[[Preview]]]"));
                    }
                }

                public static string GetActionRedirect(int level, string source, string content, uint background, uint foreground, int alignment)
                {
                    return
                        CONTROL.GetPanel(level, source, "", alignment, CONSTANT.CONTROL.ACTION.SIZE_Y / 2, CONSTANT.CONTROL.ACTION.SIZE_Y,
                            CONTROL.PARAM.GetBackground(foreground)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/EXTENSION/ARROW}}}", NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.ACTION.SIZE_Y / 2, CONSTANT.CONTROL.ACTION.SIZE_Y / 2, "");
                }

                public static string GetActionSlideBox(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    return
                        CONTROL.GetSlideBox(level, source, "", alignment, size, size,
                            CONTROL.PARAM.GetBackground(foreground) +
                            CONTROL.PARAM.GetForeground(background));
                }

                public static string GetActionSlideItem(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetForeground(background));
                }

                public static string GetActionSplitter(int level, string source, string content, uint background, uint foreground, int alignment)
                {
                    return
                        CONTROL.GetSplitter(level, source, "", alignment, CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.WINDOW.PADDING,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND));
                }

                public static string GetActionTabBox(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    return
                        CONTROL.GetTabBox(level, source, "", alignment, size, size,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.FOOTER.TRANSPARENCY));
                }

                public static string GetActionTabItem(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetForeground(foreground)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetScrollBox(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING, "");
                }

                public static string GetActionTable(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    return
                        CONTROL.GetTable(level, source, "", alignment, size, size, "");
                }

                public static string GetActionTextBox(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    return
                        CONTROL.GetTextBox(level, source, content, alignment, size, size,
                            CONTROL.PARAM.GetForeground(background) +
                            CONTROL.PARAM.GetForeground(foreground));
                }

                public static string GetActionTitle(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.TITLE.SIZE_Y,
                            CONTROL.PARAM.GetBackground(background)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetLabel(level + 1, source, content, NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, 0, CONSTANT.CONTROL.WINDOW.PADDING, 0) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.TITLE.FONT_NAME, CONSTANT.CONTROL.TITLE.FONT_SIZE, STATE.FONT.NONE)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(foreground));
                }

                public static string GetActionViewerBox(int level, string source, string content, uint background, uint foreground, int alignment, int size)
                {
                    if (!string.IsNullOrEmpty(content) && !content.Contains("\r") && !content.Contains("\n"))
                    {
                        switch (Control.GetName(content))
                        {
                            case NAME.CONTROL.AUDIO:
                                return
                                    CONTROL.GetPanel(level, source, "", alignment, size, size, "") + MESSAGE.GetNextTrace() +
                                    CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                                        CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND)) + MESSAGE.GetNextTrace() +
                                    CONTROL.GetAudio(level + 1, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                                        CONTROL.PARAM.GetBackground(background) +
                                        CONTROL.PARAM.GetForeground(background));
                            case NAME.CONTROL.PICTURE:
                                return
                                    CONTROL.GetPicture(level, source, content, alignment, size, size, "");
                            case NAME.CONTROL.VIDEO:
                                return
                                    CONTROL.GetVideo(level, source, content, alignment, size, size, "");
                            case NAME.CONTROL.BROWSER:
                                return
                                    CONTROL.GetBrowser(level, source, content.Replace("\\\\", "\\"), alignment, size, size, "");
                        }
                    }
                    {
                        return
                            CONTROL.GetTextBox(level, source, content, size == 0 ? NAME.ALIGNMENT.CLIENT : alignment, size, size,
                                CONTROL.PARAM.GetForeground(background));
                    }
                }

                public static string GetFooterBox(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.FOOTER.SIZE_Y + CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.FOOTER.TRANSPARENCY)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0, "");
                }

                public static string GetFooterButton(int level, string source, string content, uint background, uint foreground, string hint, int size, bool isBlink, string url)
                {
                    if (!string.IsNullOrEmpty(content))
                    {
                        return
                            CONTROL.GetButton(level, source, content, NAME.ALIGNMENT.RIGHT, size <= 0 ? CONSTANT.CONTROL.BUTTON.SIZE_X : size, 0,
                                CONTROL.PARAM.GetState(STATE.CONTROL.BLINK) +
                                CONTROL.PARAM.GetBackground(background) +
                                CONTROL.PARAM.GetForeground(foreground) +
                                CONTROL.PARAM.GetFont(CONSTANT.CONTROL.BUTTON.FONT_NAME, CONSTANT.CONTROL.BUTTON.FONT_SIZE, STATE.FONT.BOLD) +
                                CONTROL.PARAM.GetState(isBlink ? STATE.CONTROL.BLINK : STATE.CONTROL.NONE) +
                                CONTROL.PARAM.GetUrl(url) +
                                CONTROL.PARAM.GetHint(hint)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, CONSTANT.CONTROL.WINDOW.PADDING, 0,
                                CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND));
                    }
                    return "";
                }

                public static string GetFooterButton(int level, string source, string content, uint background, uint foreground, string hint, int size, bool isBlink, string tool, string id, AnyHandler handler)
                {
                    if (!string.IsNullOrEmpty(content))
                    {
                        return
                            CONTROL.GetButton(level, source, content, NAME.ALIGNMENT.RIGHT, size <= 0 ? CONSTANT.CONTROL.BUTTON.SIZE_X : size, 0,
                                CONTROL.PARAM.GetBackground(background) +
                                CONTROL.PARAM.GetForeground(foreground) +
                                CONTROL.PARAM.GetFont(CONSTANT.CONTROL.BUTTON.FONT_NAME, CONSTANT.CONTROL.BUTTON.FONT_SIZE, STATE.FONT.BOLD) +
                                CONTROL.PARAM.GetState(isBlink ? STATE.CONTROL.BLINK : STATE.CONTROL.NONE) +
                                CONTROL.PARAM.GetHandler(tool, id, handler) +
                                CONTROL.PARAM.GetHint(hint)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, CONSTANT.CONTROL.WINDOW.PADDING, 0,
                                CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND));
                    }
                    return "";
                }

                public static string GetFooterComboBox(int level, string source, string content, uint background, uint foreground, string hint, int size, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, size <= 0 ? CONSTANT.CONTROL.COMBOBOX.SIZE_X : size, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.TOOL.PADDING)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetComboBox(level + 1, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetHandler(tool, id, handler) +
                            CONTROL.PARAM.GetHint(hint) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.COMBOBOX.FONT_NAME, CONSTANT.CONTROL.COMBOBOX.FONT_SIZE, STATE.FONT.BOLD));
                }

                public static string GetFooterComboItem(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetItem(level + 1, source, content, NAME.ALIGNMENT.NONE, 0, CONSTANT.CONTROL.PREVIEW.ITEM_SIZE_Y,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.COMBOBOX.FONT_NAME, CONSTANT.CONTROL.COMBOBOX.FONT_SIZE, STATE.FONT.BOLD));
                }

                public static string GetFooterIndent(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.RIGHT, CONSTANT.CONTROL.WINDOW.PADDING, 0,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND));
                }

                public static string GetFooterInfo(int level, string source, string content, uint background, uint foreground, string hint)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.TOOL.PADDING)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y * 2, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y * 2, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/OTHER/INFO}}}", NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                            CONTROL.PARAM.GetHint(hint)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetEditBox(level + 1, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetForeground(background) +
                            CONTROL.PARAM.GetHint(hint));
                }

                public static string GetFooterFind(int level, string source, string content, uint background, uint foreground, string tool, string id, AnyHandler handler)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.TOOL.PADDING)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPicture(level + 1, source, "{{{RESOURCE:METAOUTPUT/OTHER/FIND}}}", NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                            CONTROL.PARAM.GetHint("[[[Search text]]]")) + MESSAGE.GetNextTrace() +
                        CONTROL.GetEditBox(level + 1, source, content, NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetHandler(tool, id, handler) +
                            CONTROL.PARAM.GetHint("[[[Search text]]]"));
                }

                public static string GetFooterLabel(int level, string source, string content, uint background, uint foreground, string hint, bool isHighlighted)
                {
                    return
                        CONTROL.GetLabel(level, source, content, NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                            CONTROL.PARAM.GetHint(hint) +
                            CONTROL.PARAM.GetForeground(isHighlighted ? CONSTANT.CONTROL.ACTION.FOREGROUND : foreground) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, 0, CONSTANT.CONTROL.WINDOW.PADDING, 0) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.FOOTER.FONT_NAME, CONSTANT.CONTROL.FOOTER.FONT_SIZE, isHighlighted ? STATE.FONT.BOLD : STATE.FONT.NONE));
                }

                public static string GetFooterPicture(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPicture(level, source, content, NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.FOOTER.SIZE_Y, 0,
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.FOOTER.TRANSPARENCY) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING));
                }

                public static string GetHeaderBox(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING + CONSTANT.CONTROL.HEADER.SIZE_Y, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(background) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.HEADER.TRANSPARENCY)) + MESSAGE.GetNextTrace() +
                        CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, 0, CONSTANT.CONTROL.WINDOW.PADDING, 0));
                }

                public static string GetHeaderLabel(int level, string source, string content, uint background, uint foreground)
                {
                    return
                        CONTROL.GetLabel(level + 1, source, content, NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                            CONTROL.PARAM.GetForeground(CONSTANT.CONTROL.HEADER.FOREGROUND) +
                            CONTROL.PARAM.GetFont(CONSTANT.CONTROL.HEADER.FONT_NAME, CONSTANT.CONTROL.HEADER.FONT_SIZE, STATE.FONT.NONE));
                }

                public static string GetPreviewWindow(int level, string source, string content, uint background, uint foreground, int rowCount)
                {
                    if (rowCount <= 0)
                    {
                        rowCount = CONSTANT.CONTROL.COUNT.NORMAL;
                    }
                    return
                        EXTENSION.GetToolWindow(level, source, "[[[PREVIEW]]]: <<<" + GetFirstLine(content, false) + ">>>", background, foreground, rowCount, "{{{RESOURCE:METAOUTPUT/OTHER/PREVIEW}}}", "", "");
                }

                public static string GetToolWindow(int level, string source, string content, uint background, uint foreground, int rowCount, string logoPicture, string @params, string hint)
                {
                    if (rowCount <= 0)
                    {
                        rowCount = CONSTANT.CONTROL.COUNT.NORMAL;
                    }
                    if (!@params.Contains(CONSTANT.MESSAGE.TML.ATTRIBUTE))
                    {
                        @params = CONTROL.GetLabel(level + 3, source, GetFirstLine(@params, false), NAME.ALIGNMENT.CONTENT_RIGHT, 0, 0,
                            CONTROL.PARAM.GetHint(hint) +
                            CONTROL.PARAM.GetForeground(foreground) +
                            CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.TOOL.TRANSPARENCY / 2));
                    }
                    {
                        return
                            CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                                CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND) +
                                CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                                CONTROL.PARAM.GetCount(rowCount)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.HEADER.SIZE_Y,
                                CONTROL.PARAM.GetFont(CONSTANT.CONTROL.HEADER.FONT_NAME, CONSTANT.CONTROL.HEADER.FONT_SIZE, STATE.FONT.BOLD) +
                                CONTROL.PARAM.GetBackground(background) +
                                CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.TOOL.PADDING, CONSTANT.CONTROL.WINDOW.PADDING, CONSTANT.CONTROL.TOOL.PADDING)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetLabel(level + 2, source, content, NAME.ALIGNMENT.CONTENT_LEFT, 0, 0,
                                CONTROL.PARAM.GetFont(CONSTANT.CONTROL.HEADER.FONT_NAME, CONSTANT.CONTROL.HEADER.FONT_SIZE, STATE.FONT.BOLD) +
                                CONTROL.PARAM.GetForeground(foreground) +
                                CONTROL.PARAM.GetCount(CONSTANT.CONTROL.COUNT.NORMAL)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 2, source, "", NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.WINDOW.PADDING * 10, 0, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 2, source, "", NAME.ALIGNMENT.CLIENT, 0, 0, "") + MESSAGE.GetNextTrace() + @params + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.LOGO.SIZE_X, 0,
                                CONTROL.PARAM.GetForeground(background) +
                                CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.DELIMITER.SIZE_Y)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPicture(level + 2, source, logoPicture, NAME.ALIGNMENT.CENTER, CONSTANT.CONTROL.LOGO.SIZE_X, CONSTANT.CONTROL.LOGO.SIZE_X,
                                CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.LEFT, CONSTANT.CONTROL.WINDOW.PADDING, 0, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0, "");
                    }
                }

                public static string GetTraceViewer(int level, string source, string content, uint background, uint foreground, int rowCount)
                {
                    if (rowCount <= 0)
                    {
                        rowCount = CONSTANT.CONTROL.COUNT.NORMAL;
                    }
                    {
                        return
                            CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                                CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND) +
                                CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                                CONTROL.PARAM.GetCount(rowCount)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                                CONTROL.PARAM.GetBackground(background)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.TOP, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.DELIMITER.SIZE_Y,
                                CONTROL.PARAM.GetBackground(background)) + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.BOTTOM, 0, CONSTANT.CONTROL.WINDOW.PADDING, "") + MESSAGE.GetNextTrace() +
                            CONTROL.GetPanel(level + 1, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                                CONTROL.PARAM.GetBackground(background) +
                                CONTROL.PARAM.GetTransparency(CONSTANT.CONTROL.ACTION.TRANSPARENCY));
                    }
                }
            }

            public class FILE
            {
                public static string GetImport(string source, string url)
                {
                    return "@@@IMPORT " + url +
                        (string.IsNullOrEmpty(source) ? "" : " &&&SOURCE " + GetFirstLine(source, false)) + " ";
                }

                public static string GetExport(string source, string url)
                {
                    return "@@@EXPORT " + url +
                        (string.IsNullOrEmpty(source) ? "" : " &&&SOURCE " + GetFirstLine(source, false)) + " ";
                }
            }

            public class MESSAGE
            {
                public class CONDITION
                {
                    public static string GetAnd(string condition1, string condition2, string condition3, string condition4, string condition5)
                    {
                        return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) +
                            " &&&CONDITION " + GetFirstLine(condition4, false) +
                            " &&&CONDITION " + GetFirstLine(condition5, false) + "))) ";
                    }

                    public static string GetAnd(string condition1, string condition2, string condition3, string condition4)
                    {
                        return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) +
                            " &&&CONDITION " + GetFirstLine(condition4, false) + "))) ";
                    }

                    public static string GetAnd(string condition1, string condition2, string condition3)
                    {
                        return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) + "))) ";
                    }

                    public static string GetAnd(string condition1, string condition2)
                    {
                        return "(((COMPARE.AND &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) + "))) ";
                    }

                    public static string GetOr(string condition1, string condition2, string condition3, string condition4, string condition5)
                    {
                        return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) +
                            " &&&CONDITION " + GetFirstLine(condition4, false) +
                            " &&&CONDITION " + GetFirstLine(condition5, false) + "))) ";
                    }

                    public static string GetOr(string condition1, string condition2, string condition3, string condition4)
                    {
                        return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) +
                            " &&&CONDITION " + GetFirstLine(condition4, false) + "))) ";
                    }

                    public static string GetOr(string condition1, string condition2, string condition3)
                    {
                        return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) +
                            " &&&CONDITION " + GetFirstLine(condition3, false) + "))) ";
                    }

                    public static string GetOr(string condition1, string condition2)
                    {
                        return "(((COMPARE.OR &&&CONDITION " + GetFirstLine(condition1, false) +
                            " &&&CONDITION " + GetFirstLine(condition2, false) + "))) ";
                    }

                    public static string GetEmpty(string attribute)
                    {
                        return "(((COMPARE.EMPTY &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetNotEmpty(string attribute)
                    {
                        return "(((COMPARE.NOT.EMPTY &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetEqual(string attribute, string find)
                    {
                        return "(((COMPARE.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetNotEqual(string attribute, string find)
                    {
                        return "(((COMPARE.NOT.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetContains(string attribute, string find)
                    {
                        return "(((COMPARE.CONTAINS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetNotContains(string attribute, string find)
                    {
                        return "(((COMPARE.NOT.CONTAINS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetMore(string attribute, string find)
                    {
                        return "(((COMPARE.MORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetMoreEqual(string attribute, string find)
                    {
                        return "(((COMPARE.MORE.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetLess(string attribute, string find)
                    {
                        return "(((COMPARE.LESS &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }

                    public static string GetLessEqual(string attribute, string find)
                    {
                        return "(((COMPARE.LESS.EQUAL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetMultiLine(find) + "))) ";
                    }
                }

                public class PARAM
                {
                    public static string GetBackground(string value)
                    {
                        return CONTROL.PARAM.GetBackground(value);
                    }

                    public static string GetBackground(uint value)
                    {
                        return CONTROL.PARAM.GetBackground(value);
                    }

                    public static string GetDate(int year, int month, int day)
                    {
                        return "&&&DATE " +
                            Math.Max(0, Math.Min(year, 2100)).ToString("d4") + "." +
                            Math.Max(0, Math.Min(month, 12)).ToString("d2") + "." +
                            Math.Max(0, Math.Min(day, 31)).ToString("d2") + " ";
                    }

                    public static string GetCount(int value)
                    {
                        return CONTROL.PARAM.GetCount(value);
                    }

                    public static string GetId(string id)
                    {
                        if (!string.IsNullOrEmpty(id))
                        {
                            return "&&&ID " + GetFirstLine(id, false) + " ";
                        }
                        return "";
                    }

                    public static string GetFont(string name, int state)
                    {
                        return CONTROL.PARAM.GetFont(name, 0, state);
                    }

                    public static string GetFont(string name)
                    {
                        return CONTROL.PARAM.GetFont(name, 0);
                    }

                    public static string GetForeground(string value)
                    {
                        return CONTROL.PARAM.GetForeground(value);
                    }

                    public static string GetForeground(uint value)
                    {
                        return CONTROL.PARAM.GetForeground(value);
                    }

                    public static string GetProgress(double value, string hint)
                    {
                        var a_Result = "";
                        if (value != 0)
                        {
                            a_Result += "&&&PROGRESS " + value + " ";
                        }
                        if (value != 0 && !string.IsNullOrEmpty(hint))
                        {
                            a_Result += "&&&PROGRESS.HINT " + GetMultiLine(hint) + " ";
                        }
                        return a_Result;
                    }

                    public static string GetState(int value)
                    {
                        var a_Result = "";
                        if (value != STATE.MESSAGE.NONE)
                        {
                            {
                                a_Result += "&&&STATE";
                            }
                            if ((value & STATE.MESSAGE.BEEP) == STATE.MESSAGE.BEEP) a_Result += " BEEP";
                            if ((value & STATE.MESSAGE.BLINK) == STATE.MESSAGE.BLINK) a_Result += " BLINK";
                            if ((value & STATE.MESSAGE.CLEAR) == STATE.MESSAGE.CLEAR) a_Result += " CLEAR";
                            if ((value & STATE.MESSAGE.COLLAPSE) == STATE.MESSAGE.COLLAPSE) a_Result += " COLLAPSE";
                            if ((value & STATE.MESSAGE.EXPAND) == STATE.MESSAGE.EXPAND) a_Result += " EXPAND";
                            if ((value & STATE.MESSAGE.FIX) == STATE.MESSAGE.FIX) a_Result += " FIX";
                            if ((value & STATE.MESSAGE.FOCUS) == STATE.MESSAGE.FOCUS) a_Result += " FOCUS";
                            if ((value & STATE.MESSAGE.HIDE) == STATE.MESSAGE.HIDE) a_Result += " HIDE";
                            if ((value & STATE.MESSAGE.LOCK) == STATE.MESSAGE.LOCK) a_Result += " LOCK";
                            if ((value & STATE.MESSAGE.MUTE) == STATE.MESSAGE.MUTE) a_Result += " MUTE";
                            if ((value & STATE.MESSAGE.PIN) == STATE.MESSAGE.PIN) a_Result += " PIN";
                            if ((value & STATE.MESSAGE.REMOVE) == STATE.MESSAGE.REMOVE) a_Result += " REMOVE";
                            if ((value & STATE.MESSAGE.RESEND) == STATE.MESSAGE.RESEND) a_Result += " RESEND";
                            if ((value & STATE.MESSAGE.SHOW) == STATE.MESSAGE.SHOW) a_Result += " SHOW";
                            if ((value & STATE.MESSAGE.SPEAK) == STATE.MESSAGE.SPEAK) a_Result += " SPEAK";
                            if ((value & STATE.MESSAGE.UNFIX) == STATE.MESSAGE.UNFIX) a_Result += " UNFIX";
                            if ((value & STATE.MESSAGE.UNFOCUS) == STATE.MESSAGE.UNFOCUS) a_Result += " UNFOCUS";
                            if ((value & STATE.MESSAGE.UNLOCK) == STATE.MESSAGE.UNLOCK) a_Result += " UNLOCK";
                            if ((value & STATE.MESSAGE.UNPIN) == STATE.MESSAGE.UNPIN) a_Result += " UNPIN";
                            if ((value & STATE.MESSAGE.UPDATE) == STATE.MESSAGE.UPDATE) a_Result += " UPDATE";
                            {
                                a_Result += " ";
                            }
                        }
                        return a_Result;
                    }

                    public static string GetTime(int hour, int minute, int second, int milliSecond)
                    {
                        return "&&&TIME " +
                            Math.Max(0, Math.Min(hour, 24)).ToString("d2") + "." +
                            Math.Max(0, Math.Min(minute, 60)).ToString("d2") + "." +
                            Math.Max(0, Math.Min(second, 60)).ToString("d2") + "." +
                            Math.Max(0, Math.Min(milliSecond, 999)).ToString("d3") + " ";
                    }

                    public static string GetUrl(string value, string hint, int line, int position)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(value))
                        {
                            a_Result += "&&&URL " + GetFirstLine(value, false) + " ";
                        }
                        if (!string.IsNullOrEmpty(hint))
                        {
                            a_Result += "&&&URL.HINT " + GetMultiLine(hint) + " ";
                        }
                        if (line > 0)
                        {
                            a_Result += "&&&URL.LINE " + line.ToString("d0") + " ";
                        }
                        if (position > 0)
                        {
                            a_Result += "&&&URL.POSITION " + position.ToString("d0") + " ";
                        }
                        return a_Result;
                    }

                    public static string GetUrl(string value, string hint)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(value))
                        {
                            a_Result += "&&&URL " + GetFirstLine(value, false) + " ";
                        }
                        if (!string.IsNullOrEmpty(hint))
                        {
                            a_Result += "&&&URL.HINT " + GetMultiLine(hint) + " ";
                        }
                        return a_Result;
                    }

                    public static string GetUrlInfo(string value, string hint)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(value))
                        {
                            a_Result += "&&&URL.INFO " + GetFirstLine(value, false) + " ";
                        }
                        if (!string.IsNullOrEmpty(hint))
                        {
                            a_Result += "&&&URL.INFO.HINT " + GetMultiLine(hint) + " ";
                        }
                        return a_Result;
                    }

                    public static string GetUrlPreview(string value)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(value))
                        {
                            a_Result += "&&&URL.PREVIEW " + GetFirstLine(value, false) + " ";
                        }
                        return a_Result;
                    }

                    public static string GetValue(string value)
                    {
                        var a_Result = "";
                        if (!string.IsNullOrEmpty(value))
                        {
                            a_Result += "&&&VALUE " + GetMultiLine(value) + " ";
                        }
                        return a_Result;
                    }
                }

                public static string GetCondition(string condition)
                {
                    return "@@@CONDITION " + GetFirstLine(condition, false) + " ";
                }

                public static string GetTraceViewer(int level, string source, int rowCount)
                {
                    return
                        CONTROL.GetPanel(level, source, "", NAME.ALIGNMENT.CLIENT, 0, 0,
                            CONTROL.PARAM.GetBackground(CONSTANT.CONTROL.WINDOW.BACKGROUND) +
                            CONTROL.PARAM.GetPadding(CONSTANT.CONTROL.WINDOW.PADDING) +
                            CONTROL.PARAM.GetCount(rowCount));
                }

                public static string GetTracePreview(int level, string source, string @event, string url, int state, int progress)
                {
                    if (string.IsNullOrEmpty(url))
                    {
                        return "";
                    }
                    else
                    {
                        var a_Name = Path.GetFileName(url);
                        {
                            var a_Index = a_Name.LastIndexOf('.');
                            var a_Context = "";
                            if (a_Index >= 0)
                            {
                                a_Context = a_Name.Substring(a_Index, a_Name.Length - a_Index);
                                a_Name = a_Name.Substring(0, a_Index);
                            }
                            {
                                a_Name = a_Name.Replace("_", "<<<_>>>");
                                a_Name = a_Name.Replace("-", "<<<->>>");
                                a_Name = a_Name.Replace(".", "<<<.>>>");
                                a_Name = a_Name.Replace("0", "<<<0>>>");
                                a_Name = a_Name.Replace("1", "<<<1>>>");
                                a_Name = a_Name.Replace("2", "<<<2>>>");
                                a_Name = a_Name.Replace("3", "<<<3>>>");
                                a_Name = a_Name.Replace("4", "<<<4>>>");
                                a_Name = a_Name.Replace("5", "<<<5>>>");
                                a_Name = a_Name.Replace("6", "<<<6>>>");
                                a_Name = a_Name.Replace("7", "<<<7>>>");
                                a_Name = a_Name.Replace("8", "<<<8>>>");
                                a_Name = a_Name.Replace("9", "<<<9>>>");
                                a_Name = a_Name + "<<<" + a_Context + ">>>";
                            }
                            {
                                return
                                    MESSAGE.GetTraceMessage(0, source, @event, "[[[PREVIEW]]]: " + a_Name, "", "",
                                        MESSAGE.PARAM.GetId(url) +
                                        MESSAGE.PARAM.GetUrl(url, "") +
                                        MESSAGE.PARAM.GetForeground(CONSTANT.CONTROL.MESSAGE.PREVIEW_FOREGROUND) +
                                        MESSAGE.PARAM.GetProgress(progress, "[[[Work progress]]] - " + progress.ToString("d0") + "%") +
                                        MESSAGE.PARAM.GetState(state | STATE.MESSAGE.EXPAND | STATE.MESSAGE.SHOW | STATE.MESSAGE.BLINK));
                            }
                        }
                    }
                }

                public static string GetTraceTool(int level, string source, string @event, string content, string id, int state)
                {
                    if (content != "[[[ALL TOOLS]]]")
                    {
                        content = "[[[TOOL]]]: " + content;
                    }
                    {
                        return
                            MESSAGE.GetTraceMessage(level, source, @event, content, "", "",
                                MESSAGE.PARAM.GetId(id) +
                                MESSAGE.PARAM.GetForeground(CONSTANT.CONTROL.MESSAGE.TOOL_FOREGROUND) +
                                MESSAGE.PARAM.GetState(state | STATE.MESSAGE.EXPAND | STATE.MESSAGE.SHOW | STATE.MESSAGE.BLINK));
                    }
                }

                public static string GetTraceMessage(int level, string source, string @event, string content, string message, string hint, string @params)
                {
                    var a_Result = GetLevel(level) + GetMultiLine(content) + " @@@SOURCE " + GetFirstLine(source, false);
                    if (!string.IsNullOrEmpty(@event))
                    {
                        a_Result += " @@@EVENT " + GetFirstLine(@event, false);
                }
                    if (!string.IsNullOrEmpty(message) || !string.IsNullOrEmpty(@params))
                    {
                        if (!string.IsNullOrEmpty(message))
                        {
                            a_Result += " @@@MESSAGE " + GetMultiLine(message) + " " + GetFirstLine(@params, false);
                        }
                        else
                        {
                            a_Result += " @@@MESSAGE " + GetFirstLine(@params, false);
                        }
                        if (!string.IsNullOrEmpty(hint))
                        {
                            a_Result += " &&&HINT " + GetMultiLine(hint);
                        }
                    }
                    return a_Result + " ";
                }

                public static string GetNextTrace()
                {
                    return "\n";
                }
            }

            public class PREVIEW
            {
                public static string GetAppend(string name, AnyPreview handler, string extension)
                {
                    if (!string.IsNullOrEmpty(extension))
                    {
                        AnyPreview.Register(extension, handler);
                    }
                    {
                        return "@@@PREVIEW.APPEND " + GetFirstLine(name, false) +
                            " &&&EXTENSION " + GetFirstLine(extension, false) + " ";
                    }
                }

                public static string GetRemove(string name)
                {
                    return "@@@PREVIEW.REMOVE " + GetFirstLine(name, false) + " ";
                }
            }

            public class RESOURCE
            {
                public static string GetAppend(string name, string culture, string value)
                {
                    return "@@@RESOURCE.APPEND " + GetFirstLine(name, false) +
                        " &&&CULTURE " + culture +
                        " &&&VALUE " + GetFirstLine(value, false) + " ";
                }

                public static string GetRemove(string name, string culture)
                {
                    return "@@@RESOURCE.REMOVE " + GetFirstLine(name, false) +
                        " &&&CULTURE " + culture + " ";
                }
            }

            public class SOURCE
            {
                public static string GetAppend(string name, string picture)
                {
                    return "@@@SOURCE.APPEND " + GetFirstLine(name, false) +
                        " &&&VALUE " + GetFirstLine(picture, false) + " ";
                }

                public static string GetRemove(string name)
                {
                    return "@@@SOURCE.REMOVE " + GetFirstLine(name, false) + " ";
                }

                public static string GetClear(string name)
                {
                    return "@@@SOURCE.CLEAR " + GetFirstLine(name, false) + " ";
                }
            }

            public class TOOL
            {
                public static string GetAppend(string name, AnyTool handler, string picture, string group, string title, string tags, uint background)
                {
                    if (!string.IsNullOrEmpty(name))
                    {
                        AnyTool.Register(name, handler);
                    }
                    {
                        return "@@@TOOL.APPEND " + GetFirstLine(name, false) +
                            " &&&GROUP " + GetFirstLine(group, false) +
                            " &&&TITLE " + GetFirstLine(title, false) +
                            " &&&TAGS " + GetFirstLine(tags, false) +
                            " &&&BACKGROUND " + Color.ToString(background) +
                            " &&&VALUE " + GetFirstLine(picture, false) + " ";
                    }
                }

                public static string GetRemove(string name)
                {
                    if (!string.IsNullOrEmpty(name))
                    {
                        AnyTool.Unregister(name);
                    }
                    {
                        return "@@@TOOL.REMOVE " + GetFirstLine(name, false) + " ";
                    }
                }

                public static string GetEnable(string name)
                {
                    return "@@@TOOL.ENABLE " + GetFirstLine(name, false) + " ";
                }

                public static string GetDisable(string name)
                {
                    return "@@@TOOL.DISABLE " + GetFirstLine(name, false) + " ";
                }

                public static string GetShow(string name)
                {
                    return "@@@TOOL.SHOW " + GetFirstLine(name, false) + " ";
                }

                public static string GetHide(string name)
                {
                    return "@@@TOOL.HIDE " + GetFirstLine(name, false) + " ";
                }
            }

            public class TRANSFORM
            {
                public class CONDITION : MESSAGE.CONDITION
                {
                }

                public class TEXT
                {
                    public static string GetCamelCase(string attribute)
                    {
                        return "(((TEXT.CAMEL.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetLowerCase(string attribute)
                    {
                        return "(((TEXT.LOWER.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetSentenceCase(string attribute)
                    {
                        return "(((TEXT.SENTENCE.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetUpperCase(string attribute)
                    {
                        return "(((TEXT.UPPER.CASE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetTrim(string attribute)
                    {
                        return "(((TEXT.TRIM &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetTrimBegin(string attribute)
                    {
                        return "(((TEXT.TRIM.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetTrimEnd(string attribute)
                    {
                        return "(((TEXT.TRIM.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + "))) ";
                    }

                    public static string GetInsertBegin(string attribute, string value)
                    {
                        return "(((TEXT.INSERT.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }

                    public static string GetInsertEnd(string attribute, string value)
                    {
                        return "(((TEXT.INSERT.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }

                    public static string GetInsertAfter(string attribute, string find, string value)
                    {
                        return "(((TEXT.INSERT.AFTER &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }

                    public static string GetInsertBefore(string attribute, string find, string value)
                    {
                        return "(((TEXT.INSERT.BEFORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }

                    public static string GetInsertBetween(string attribute, string find1, string find2, string value)
                    {
                        return "(((TEXT.INSERT.BETWEEN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND1 " + GetFirstLine(find1, false) + " &&&FIND2 " + GetFirstLine(find2, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }

                    public static string GetRemove(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveAll(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE.ALL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveBegin(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE.BEGIN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveEnd(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE.END &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveAfter(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE.AFTER &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveBefore(string attribute, string find)
                    {
                        return "(((TEXT.REMOVE.BEFORE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + "))) ";
                    }

                    public static string GetRemoveBetween(string attribute, string find1, string find2)
                    {
                        return "(((TEXT.REMOVE.BETWEEN &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND1 " + GetFirstLine(find1, false) + " &&&FIND2 " + GetFirstLine(find2, false) + "))) ";
                    }

                    public static string GetReplace(string attribute, string find, string replace)
                    {
                        return "(((TEXT.REPLACE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&REPLACE " + GetFirstLine(replace, false) + "))) ";
                    }

                    public static string GetReplaceAll(string attribute, string find, string replace)
                    {
                        return "(((TEXT.REPLACE.ALL &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&FIND " + GetFirstLine(find, false) + " &&&REPLACE " + GetFirstLine(replace, false) + "))) ";
                    }

                    public static string GetUpdate(string attribute, string value)
                    {
                        return "(((TEXT.UPDATE &&&ATTRIBUTE " + GetFirstLine(attribute, false) + " &&&VALUE " + GetFirstLine(value, false) + "))) ";
                    }
                }

                public class TRACE
                {
                    public static string GetCommentDetect()
                    {
                        return "(((COMMENT.DETECT))) ";
                    }

                    public static string GetFunctionDetect()
                    {
                        return "(((FUNCTION.DETECT))) ";
                    }

                    public static string GetGroupDetect()
                    {
                        return "(((GROUP.DETECT))) ";
                    }

                    public static string GetLevelDetect()
                    {
                        return "(((LEVEL.DETECT))) ";
                    }

                    public static string GetProgressDetect()
                    {
                        return "(((PROGRESS.DETECT))) ";
                    }

                    public static string GetTimeDetect()
                    {
                        return "(((TIME.DETECT))) ";
                    }

                    public static string GetUrlDetect()
                    {
                        return "(((URL.DETECT))) ";
                    }

                    public static string GetUrlInfoDetect()
                    {
                        return "(((URL.INFO.DETECT))) ";
                    }

                    public static string GetValueDetect()
                    {
                        return "(((VALUE.DETECT))) ";
                    }

                    public static string GetLevelNext()
                    {
                        return "(((LEVEL.NEXT))) ";
                    }

                    public static string GetLevelPrev()
                    {
                        return "(((LEVEL.PREV))) ";
                    }

                    public static string GetLevelRoot()
                    {
                        return "(((LEVEL.ROOT))) ";
                    }

                    public static string GetCommentAfter(string find)
                    {
                        return "(((COMMENT.AFTER &&&FIND " + find + "))) ";
                    }

                    public static string GetCommentBefore(string find)
                    {
                        return "(((COMMENT.BEFORE &&&FIND " + find + "))) ";
                    }

                    public static string GetCommentBegin(string find)
                    {
                        return "(((COMMENT.BEGIN &&&FIND " + find + "))) ";
                    }

                    public static string GetCommentBetween(string find1, string find2)
                    {
                        return "(((COMMENT.BETWEEN &&&FIND1 " + find1 + " &&&FIND2 " + find2 + "))) ";
                    }

                    public static string GetCommentEnd(string find)
                    {
                        return "(((COMMENT.END &&&FIND " + find + "))) ";
                    }

                    public static string GetGroup(string find)
                    {
                        return "(((GROUP &&&FIND " + find + "))) ";
                    }

                    public static string GetGroupAfter(string find)
                    {
                        return "(((GROUP.AFTER &&&FIND " + find + "))) ";
                    }

                    public static string GetGroupBefore(string find)
                    {
                        return "(((GROUP.BEFORE &&&FIND " + find + "))) ";
                    }

                    public static string GetGroupBegin(string find)
                    {
                        return "(((GROUP.BEGIN &&&FIND " + find + "))) ";
                    }

                    public static string GetGroupBetween(string find1, string find2)
                    {
                        return "(((GROUP.BETWEEN &&&FIND1 " + find1 + " &&&FIND2 " + find2 + "))) ";
                    }

                    public static string GetGroupEnd(string find)
                    {
                        return "(((GROUP.END &&&FIND " + find + "))) ";
                    }

                    public static string GetGroupOutside(string find)
                    {
                        return "(((GROUP.OUTSIDE &&&FIND " + find + "))) ";
                    }
                }

                public static string GetAppend(string name, string source, string scope, string condition, string action)
                {
                    return "@@@TRANSFORM.APPEND " + GetFirstLine(name, false) +
                        " &&&SOURCE " + GetFirstLine(source, false) +
                        " &&&SCOPE " + scope +
                        " &&&CONDITION " + condition +
                        " &&&ACTION " + GetFirstLine(action, false) + " ";
                }

                public static string GetRemove(string name, string source, string scope)
                {
                    return "@@@TRANSFORM.REMOVE " + GetFirstLine(name, false) +
                        " &&&SOURCE " + GetFirstLine(source, false) +
                        " &&&SCOPE " + scope + " ";
                }
            }

            public class TRANSLATION
            {
                public static string GetAppend(string name, string culture, string value)
                {
                    return "@@@TRANSLATION.APPEND " + GetFirstLine(name, false) +
                        " &&&CULTURE " + culture +
                        " &&&VALUE " + GetFirstLine(value, false) + " ";
                }

                public static string GetRemove(string name, string culture)
                {
                    return "@@@TRANSLATION.REMOVE " + GetFirstLine(name, false) +
                        " &&&CULTURE " + culture + " ";
                }
            }

            public class VARIABLE
            {
                public static string GetSetter(string name, string value)
                {
                    return "@@@VARIABLE.SET" + GetFirstLine(name, false) +
                        " &&&VALUE " + GetFirstLine(value, false) + " ";
                }
            }
        }

        public class AnyHandler // TODO: Remake it into delegate
        {
            public void Execute(Trace trace, int level, string tool, string id, string action, string attributes)
            {
                _Execute(trace, level, tool, id, action, attributes);
            }

            protected virtual void _Execute(Trace trace, int level, string tool, string id, string action, string attributes)
            {
            }
        }

        public Trace()
        {
            m_Transaction = 0;
            m_Sender = "";
            m_Buffer = new StringBuilder(1024);
        }

        public string GetBuffer()
        {
            return m_Buffer.ToString();
        }

        public static string GetLevel(int value)
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
                var a_Result = "";
                for (var i = 0; i < value; i++)
                {
                    a_Result += "  ";
                }
                {
                    return a_Result;
                }
            }
            return "";
        }

        public static string GetFirstLine(string value, bool isAnyText)
        {
            if (!string.IsNullOrEmpty(value))
            {
                var a_Result = value;
                {
                    var a_Index1 = value.IndexOf('\n');
                    var a_Index2 = value.IndexOf('\r');
                    if (a_Index1 >= 0 || a_Index2 >= 0)
                    {
                        a_Result = value.Substring(0, Math.Min(a_Index1, a_Index2));
                    }
                    if (isAnyText)
                    {
                        if (value.Contains("{{{")) a_Result = a_Result.Replace("{{{", "{<<<{{>>>");
                        if (value.Contains("}}}")) a_Result = a_Result.Replace("}}}", "}<<<}}>>>");
                        if (value.Contains("(((")) a_Result = a_Result.Replace("(((", "(<<<((>>>");
                        if (value.Contains(")))")) a_Result = a_Result.Replace(")))", ")<<<))>>>");
                        if (value.Contains("###")) a_Result = a_Result.Replace("###", "#<<<##>>>");
                        if (value.Contains("@@@")) a_Result = a_Result.Replace("@@@", "@[[[64]]]@");
                        if (value.Contains("&&&")) a_Result = a_Result.Replace("&&&", "&[[[38]]]&");
                    }
                }
                return a_Result.Trim();
            }
            return "";
        }

        public static string GetMultiLine(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                var a_Result = value;
                if (a_Result.Contains("\r") || a_Result.Contains("\n"))
                {
                    a_Result = a_Result.Replace("\r\n", CONSTANT.MESSAGE.TML.NEW_LINE);
                    a_Result = a_Result.Replace("\r", CONSTANT.MESSAGE.TML.NEW_LINE);
                    a_Result = a_Result.Replace("\n", CONSTANT.MESSAGE.TML.NEW_LINE);
                }
                return GetFirstLine(a_Result, true);
            }
            return "";
        }

        public static string GetUrlFinal(string url)
        {
            if (!string.IsNullOrEmpty(url))
            {
                var a_Result = url;
                {
                    var a_Index = a_Result.LastIndexOf('?');
                    if (a_Index > 0)
                    {
                        a_Result = a_Result.Substring(0, a_Index);
                    }
                }
                {
                    var a_Index = a_Result.LastIndexOf('#');
                    if (a_Index > 0)
                    {
                        a_Result = a_Result.Substring(0, a_Index);
                    }
                }
                return a_Result.Trim();
            }
            return "";
        }

        public static string GetUrlTemp(string url, string extension)
        {
            try
            {
                if (!string.IsNullOrEmpty(url))
                {
                    var a_Context = GetUrlFinal(url);
                    {
                        a_Context = a_Context.Replace("\\", "-");
                        a_Context = a_Context.Replace("/", "-");
                        a_Context = a_Context.Replace(":", "-");
                        a_Context = a_Context.Replace(" ", "_");
                        a_Context = a_Context.ToLower(CultureInfo.CurrentCulture);
                        a_Context = a_Context.Trim();
                    }
                    {
                        var a_Context1 = __GetProxyFolder();
                        if (!Directory.Exists(a_Context1))
                        {
                            Directory.CreateDirectory(a_Context1);
                        }
                        if (string.IsNullOrEmpty(extension))
                        {
                            return a_Context1 + "\\" + a_Context;
                        }
                        else
                        {
                            return a_Context1 + "\\" + a_Context + ((extension[0] != '.') ? "." : "") + extension.ToLower(CultureInfo.CurrentCulture);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return "";
        }

        public static string GetUrlTemp(string url)
        {
            return GetUrlTemp(url, "");
        }

        public Trace BeginTransaction(string sender)
        {
            {
                m_Transaction++;
            }
            if (string.IsNullOrEmpty(m_Sender))
            {
                m_Sender = sender;
            }
            return this;
        }

        public Trace CancelTransaction()
        {
            m_Transaction = 0;
            m_Sender = "";
            m_Buffer.Clear();
            return this;
        }

        public Trace CommitTransaction()
        {
            {
                __GetMutex().WaitOne();
            }
            {
                s_TraceBuffer += m_Buffer;
                m_Buffer.Clear();
            }
            {
                __GetMutex().ReleaseMutex();
            }
            if (s_TraceBuffer.Length > 0)
            {
                try
                {
                    if (s_TraceThread == null)
                    {
                        s_TraceThread = new Thread(__ThreadExecute);
                        s_TraceThread.Name = "METAOUTPUT.SEND";
                        s_TraceThread.TrySetApartmentState(ApartmentState.STA);
                        s_TraceThread.Start(null);
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(TML.MESSAGE.GetTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message, "", "", "") + TML.MESSAGE.GetNextTrace());
                }
            }
            return this;
        }

        public Trace EndTransaction()
        {
            if (m_Transaction > 0)
            {
                m_Transaction--;
            }
            if (m_Transaction <= 0)
            {
                CommitTransaction();
            }
            return this;
        }

        public Trace SendTraceMessage(int level, string source, string @event, string content, string message, string hint, string @params)
        {
            var a_Context = TML.MESSAGE.GetTraceMessage(level, source, @event, content, message, hint, @params);
            switch (source)
            {
                case NAME.SOURCE.DIAGNOSTIC:
                case NAME.SOURCE.METAREPORT:
                    switch (@event)
                    {
                        case NAME.EVENT.EMERGENCY:
                        case NAME.EVENT.CRITICAL:
                        case NAME.EVENT.ERROR:
                        case NAME.EVENT.WARNING:
                            if (level == 0)
                            {
                                a_Context += TML.MESSAGE.GetNextTrace() + __GetStackTrace(source, 1, 2) + TML.MESSAGE.GetNextTrace();
                            }
                            break;
                    }
                    {
                        Debug.WriteLine(a_Context);
                    }
                    break;
                default:
                    SendTml(a_Context);
                    break;
            }
            return this;
        }

        public Trace SendTraceMessage(int level, string source, string @event, string content)
        {
            var a_Context = TML.MESSAGE.GetTraceMessage(level, source, @event, content, "", "", "");
            switch (source)
            {
                case NAME.SOURCE.DIAGNOSTIC:
                case NAME.SOURCE.METAREPORT:
                    switch (@event)
                    {
                        case NAME.EVENT.EMERGENCY:
                        case NAME.EVENT.CRITICAL:
                        case NAME.EVENT.ERROR:
                        case NAME.EVENT.WARNING:
                            if (level == 0)
                            {
                                a_Context += TML.MESSAGE.GetNextTrace() + __GetStackTrace(source, 1, 2) + TML.MESSAGE.GetNextTrace();
                            }
                            break;
                    }
                    {
                        Debug.WriteLine(a_Context);
                    }
                    break;
                default:
                    SendTml(a_Context);
                    break;
            }
            return this;
        }

        public Trace SendTracePreview(int level, string source, string @event, string url, int state, int progress)
        {
            return SendTml(TML.MESSAGE.GetTracePreview(level, source, @event, url, state, progress));
        }

        public Trace SendTraceTool(int level, string source, string @event, string content, string id, int state)
        {
            return SendTml(TML.MESSAGE.GetTraceTool(level, source, @event, content, id, state));
        }

        public Trace SendTraceViewer(int level, string source, int rowCount)
        {
            return SendTml(TML.MESSAGE.GetTraceViewer(level, source, rowCount));
        }

        public Trace SendTml(string value, string source)
        {
            if (value != null)
            {
                return SendTml(__GetTml(value, source));
            }
            return this;
        }

        public Trace SendTml(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                m_Buffer.Append(value);
                m_Buffer.Append('\n');
            }
            if (m_Transaction > 0)
            {
                return this;
            }
            if (m_Buffer.Length > 0)
            {
                CommitTransaction();
            }
            return this;
        }

        private static Mutex __GetMutex() // TODO: Remake it into _Lock / _Unlock
        {
            if (s_Mutex == null)
            {
                s_Mutex = new Mutex(false, Message.CONSTANT.PIPE.MUTEX);
            }
            return s_Mutex;
        }

        private static string __GetTml(string value, string source)
        {
            if (!string.IsNullOrEmpty(value) && !string.IsNullOrEmpty(source))
            {
                var a_Context = value;
                if (a_Context.Contains("\r\n"))
                {
                    a_Context = a_Context.Replace("\r\n", "\n");
                }
                if (a_Context.Contains("\r"))
                {
                    a_Context = a_Context.Replace("\r", "\n");
                }
                if (a_Context.Contains("\t"))
                {
                    a_Context = a_Context.Replace("\t", " ");
                }
                if (source == NAME.SOURCE.CONSOLE)
                {
                    return a_Context.Replace("\n", " @@@SOURCE CONSOLE\n");
                }
                else
                {
                    var a_Size = a_Context.Length;
                    var a_Result = new StringBuilder(a_Size * 2);
                    var a_Context1 = "";
                    if (a_Size > Message.CONSTANT.OUTPUT.MAX_BUFFER_SIZE)
                    {
                        return "[[[Too big input]]] TML @@@SOURCE METAOUTPUT @@@EVENT CRITICAL";
                    }
                    for (var i = 0; i < a_Size; i++)
                    {
                        var a_Context2 = a_Context[i];
                        if (a_Context2 == '\n' || (i + 1) == a_Size)
                        {
                            if (!string.IsNullOrEmpty(a_Context1))
                            {
                                if (a_Context2 != '\n')
                                {
                                    a_Result.Append(a_Context2);
                                    a_Context1 += a_Context2;
                                }
                                if (!a_Context1.Contains("@@@SOURCE "))
                                {
                                    a_Result.Append(" @@@SOURCE " + source);
                                }
                                if (a_Context2 == '\n')
                                {
                                    a_Result.Append(a_Context2);
                                }
                                {
                                    a_Context1 = "";
                                }
                            }
                        }
                        else
                        {
                            a_Result.Append(a_Context2);
                            a_Context1 += a_Context2;
                        }
                    }
                    return a_Result.ToString();
                }
            }
            return value;
        }

        private static string __GetStackTrace(string source, int level, int skip)
        {
            var a_Result = "";
            try
            {
                var a_Context = new StackTrace(true);
                var a_Size = a_Context.FrameCount;
                var a_Count = AnyPreview.GetProperty(AnyPreview.VARIABLE.DEBUGGING.STACK_SIZE, true);
                for (var i = skip; i < a_Size; i++)
                {
                    if (a_Count <= 0)
                    {
                        break;
                    }
                    else
                    {
                        var a_Context1 = a_Context.GetFrame(i);
                        if (!string.IsNullOrEmpty(a_Context1?.GetFileName()))
                        {
                            var a_Context2 = "";
                            var a_Size1 = a_Context1.GetMethod().GetParameters().Length;
                            {
                                a_Count--;
                            }
                            for (var j = 0; j < a_Size1; j++)
                            {
                                var a_Context3 = a_Context1.GetMethod().GetParameters()[j];
                                {
                                    a_Context2 += ((j == 0) ? "" : ", ") + a_Context3.ParameterType.FullName + " " + a_Context3.Name;
                                }
                            }
                            {
                                a_Result += TML.MESSAGE.GetTraceMessage(level, source, NAME.EVENT.FUNCTION, a_Context1.GetMethod().Name + "(" + a_Context2 + ")", "<" + a_Context1.GetMethod().Module?.Name + ">", "<[[[Module Name]]]>",
                                    TML.MESSAGE.PARAM.GetUrl(a_Context1.GetFileName(), "", a_Context1.GetFileLineNumber(), a_Context1.GetFileColumnNumber()));
                                a_Result += TML.MESSAGE.GetNextTrace();
                            }
                        }
                    }
                }
            }
            catch (Exception)
            {
            }
            return a_Result;
        }

        private static string __GetProxyFolder()
        {
            var a_Result = Path.GetTempPath() + ".metaoutput\\";
            var a_Context = DateTime.Now;
            {
                a_Result += a_Context.Year.ToString("d4");
                a_Result += "-";
                a_Result += a_Context.Month.ToString("d2");
                a_Result += "-";
                a_Result += a_Context.Day.ToString("d2");
            }
            return a_Result;
        }

        private static void __ThreadExecute(object sender)
        {
            try
            {
                while (s_TraceThread != null)
                {
                    var a_Context = "";
                    {
                        __GetMutex().WaitOne();
                    }
                    {
                        a_Context = s_TraceBuffer;
                        s_TraceBuffer = "";
                    }
                    {
                        __GetMutex().ReleaseMutex();
                    }
                    if (string.IsNullOrEmpty(a_Context))
                    {
                        break;
                    }
                    else
                    {
                        AnyTool.Execute("", a_Context);
                        Thread.Sleep(1);
                    }
                }
            }
            catch (Exception)
            {
            }
            {
                s_TraceThread = null;
            }
        }
    }
}
