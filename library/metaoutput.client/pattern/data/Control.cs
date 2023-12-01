#pragma warning disable CA1707 // Identifiers should not contain underscores

using System;
using System.Globalization;
using System.IO;

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Control
    {
        public class CONSTANT
        {
            public class ACTION
            {
                public const int TRANSPARENCY = 90;
                public const int SIZE_Y = 64;
                public const uint FOREGROUND = Color.NAME.DARK_RED;
                public const int FONT_SIZE = 20;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class BUTTON
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 26;
                public const int SIZE_X = 200;
                public const uint FOREGROUND = Color.NAME.BLACK;
                public const int FONT_SIZE = 14;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class COMBOBOX
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 26;
                public const int SIZE_X = 140;
                public const uint FOREGROUND = Color.NAME.BLACK;
                public const int FONT_SIZE = 12;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class COUNT
            {
                public const int TINY = 3;
                public const int SMALL = 7;
                public const int NORMAL = 10;
                public const int MIDDLE = 12;
                public const int HUGE = 20;
                public const int BIG = 15;
            }

            public class DELIMITER
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 1;
            }

            public class ERROR
            {
                public const uint BACKGROUND = Color.NAME.RED;
                public const uint FOREGROUND = Color.NAME.WHITE;
            }

            public class ITEM
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 32;
                public const int SIZE_X = 32;
            }

            public class FOOTER
            {
                public const int TRANSPARENCY = 70;
                public const int SIZE_Y = 26;
                public const uint FOREGROUND = Color.NAME.BLACK;
                public const int FONT_SIZE = 12;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class HEADER
            {
                public const int TRANSPARENCY = 70;
                public const int SIZE_Y = 26;
                public const uint FOREGROUND = Color.NAME.BLACK;
                public const int FONT_SIZE = 14;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class LOGO
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_X = 150;
            }

            public class MESSAGE
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 20;
                public const uint PREVIEW_FOREGROUND = Color.NAME.ORCHID;
                public const uint TOOL_FOREGROUND = Color.NAME.DODGER_BLUE;
                public const int FONT_SIZE = 14;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class NOTIFICATION
            {
                public const uint BACKGROUND = Color.NAME.SLATE_GRAY;
                public const uint FOREGROUND = Color.NAME.WHITE;
            }

            public class PREVIEW
            {
                public const int PAGE_BREAK = 7;
                public const int PAGE_INDENT = 10;
                public const int MIN_SIZE_X = 200;
                public const int MIN_COUNT = 2;
                public const int ITEM_SIZE_Y = 19;
            }

            public class RESOURCE
            {
                public const string PICTURE_STATUS_SUCCESS = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAMAAACdt4HsAAAAVFBMVEUAAAD6+vr9/f38/Pz+/v7////+/v78/Pz9/f01bVT////3+/ri8etanX5gjHg/e2B8oZCwxrzt9vLA39Kx2MaWyrJWhW+o079trpC+0MhLfWebtqqMVCFlAAAACXRSTlMAh2oNxNQcOEfmekUeAAAB0ElEQVRYw+2X23KDMAxE6wsQrzEp14T2//+zMAN13Q02GU/esu9nkWRZFh9vvVRlJaVYJGVVPk9XQlv8ympRPUMrqTfQdp3djLRUp/FiBep+vLvrIncf+xqLinMWlxXvBmcCuaFbLS7pz4v146N5oHENQ6hE5TVgb+ZANwvoMsoXQO3ModwSRFHG+d5E1YcOzA8moeHYQWnPxx3040oKH38qC/Hw/IHanFINXB4mYN05A2dRcBISuJmTugGSAijSCTRXn0ShOIAxxeP7a+9qDkGjS/Kw33sMHXTIV9wCzC/aYxiA6n8PuDS/OmwH8b8XNOpTPJq9jGEOpUV/iv/07WhVWIIxAI55fw5VeIh34zW3U4I3d0AGBvb6hwfmJs4bZwMDsRp4flE7RXlztRCBQfdr0AKr5on4wKA7NJg3oG0ivDfgFL7a3WEinlPgIi7Q7jA3xAdFpGPkGIgPjvG4kaaNZP6okZRvZXZg3rcyXyZ2YN5fJr7O7MA8X2ceKL6SzPuBwiONY2DejzQequTAfDBUeayTA/E01uMPyxR5WDKfNq3yH9f85z1/wchfcfKXrPw1L3/RzF91WRedsWxnrPvZPxz5vzws5X+61Mdbr9QPiLNXd59EGP8AAAAASUVORK5CYII=";
                public const string PICTURE_STATUS_FAIL = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAMAAACdt4HsAAAAQlBMVEUAAAD8/Pz////+/v79/f38/Pz6+vr+/v79/f3+/v78AQH/////u7v/iYn/9PT/x8f/2Nj/oKD/aGj/Jib/5eX/Pz+U0t39AAAACnRSTlMADdLDZj57H4zqhzP+GQAAAZlJREFUWMPtV9mShCAMHOQQQTxQ//9XF2dqJ9vCeGzKt+kntew2nUQIjy9uRa2VMdYao3R9na2tbPwbjbT6Clso+SJ23Tx33etaKnGa/vz2MMbFPbHEcVhVmnMSukrvzmFygCkM6XF1bETY9ePRFRBXCSsOMi+T8eA+ICQjst7lp/B7DB6N9MlGvc8f3S5GVMj5wR0gfFYQkvj7CrKcSUvxH7mwxfqn/LlTSJnUBQOV7/7kH73gg6nzVW5CQQJ63yK/9T2kQRUCGCBI3yIfDA4phDyACPykAHxQiHkIlZ+BDworHxVmL7MSBHL4ixb5+A4WwrxLAIQ2u6VCGBCQlEKk4A1hQA+ioSbcKGz41I6NwBREV1bY8qkOGou4OFTI+YDFe4U5dBu0GR9BWQQBUAD+voClNkKFnE+tZNkCbAvsJLLLyG4kditzfybe7+w3v3N9fUHZbE+SsaQxFlXess7fWPhbG39z5W/v/AGDP+Lwhyz+mMcfNPmjLkJL1rCdIFSVj/t+pStx64EDoc1/jjwIQYcu8fjiTvwAHzBdUWl/e0IAAAAASUVORK5CYII=";
                public const string PICTURE_SAVE = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABAAgMAAADXB5lNAAAACVBMVEUAAACJFRWJFRXBlzF/AAAAAnRSTlMATX7+8BUAAABkSURBVDjLYxg8QGoVDDhABLLgAhMgAqvgYAm6wEqYAJohqxqYwLwFUhBDEAJsEEMQAowQQxACQAegCUihC7ChCzBRUwAaMAMuoAUJ0RXUFVgAorlGhgACECuQhZ62pZBT/6ABAL7R6vfbwnzYAAAAAElFTkSuQmCC";
                public const string PICTURE_FILE = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAElBMVEUAAACJFRWJFRWJFRWJFRWJFRX5ECxnAAAABXRSTlMAWWzX7FJmiVYAAACJSURBVEjH7dWxCoAgFIVhpdp1aG/oFXqAhvYIev9XiQOp0b2cKAIHPZPgxz+4aMqa3cOcDsYIZhrABg10F7AxkBISnCckOECCgwkJBhokVOC9BzBIUIAEBUhwgAQFSHDQpoQE2ILnZABzT2D9CMKygbgKKvgDpGUCYi+BleD2LfTpRv8VrAwUtQPcyY7NJrXFSgAAAABJRU5ErkJggg==";
                public const string PICTURE_COPY = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAD1BMVEUAAACJFRWJFRWJFRWJFRUl+XJUAAAABHRSTlMATaZ/8zYPywAAAJNJREFUSMft1UEKhSAUheGgFRhuQGgBDVyBuv81FWT8plzONMIze/DxPxp0W+barWXY8QJxBFkESBDoEyJAgkBy9/Y+UepCBb7+BjwBAYIAib/vAYGtGICAAQjwqC0gwKN2gIAFCBiAgAEIGICACTwBCyQnQFDATfATEBS49m0Q2xPD253lGVSHVJ5idcz152Cu2QllDcS2wk3e2wAAAABJRU5ErkJggg==";
            }

            public class TOOL
            {
                public const int TRANSPARENCY = 80;
                public const int SIZE_Y = 48;
                public const int SIZE_X = 48;
                public const int PADDING = 3;
                public const uint BACKGROUND = Color.NAME.BLACK;
                public const uint FOREGROUND = Color.NAME.WHITE;
                public const int FONT_SIZE = 14;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class TITLE
            {
                public const int TRANSPARENCY = 0;
                public const int SIZE_Y = 18;
                public const int SIZE_X = 140;
                public const uint FOREGROUND = Color.NAME.BLACK;
                public const int FONT_SIZE = 12;
                public const string FONT_NAME = Font.NAME.ARIAL;
            }

            public class TRACE
            {
                public const uint FOREGROUND = Color.NAME.TEAL;
            }

            public class WINDOW
            {
                public const int TRANSPARENCY = 0;
                public const int PADDING = 5;
                public const uint BACKGROUND = Color.NAME.WHITE;
            }
        }

        public class CHART
        {
            public const int AREA = 0x00000001;
            public const int BAR = 0x00000002;
            public const int DONUT = 0x00000004;
            public const int DOT = 0x00000008;
            public const int LINE = 0x00000010;
            public const int STACK = 0x00000020;
        }

        public class NAME
        {
            public const string AUDIO = "AUDIO";
            public const string BROWSER = "BROWSER";
            public const string BUTTON = "BUTTON";
            public const string CANVAS = "CANVAS";
            public const string CHART = "CHART";
            public const string CHECKBOX = "CHECKBOX";
            public const string COMBOBOX = "COMBOBOX";
            public const string EDITBOX = "EDITBOX";
            public const string GALLERY = "GALLERY";
            public const string GAUGE = "GAUGE";
            public const string HINT = "HINT";
            public const string ITEM = "ITEM";
            public const string LABEL = "LABEL";
            public const string LINK = "LINK";
            public const string PANEL = "PANEL";
            public const string PICTURE = "PICTURE";
            public const string PROGRESSBOX = "PROGRESSBOX";
            public const string RADIOBOX = "RADIOBOX";
            public const string SCROLLBOX = "SCROLLBOX";
            public const string SLIDEBOX = "SLIDEBOX";
            public const string SPLITTER = "SPLITTER";
            public const string TABBOX = "TABBOX";
            public const string TABLE = "TABLE";
            public const string TEXTBOX = "TEXTBOX";
            public const string TREE = "TREE";
            public const string VIDEO = "VIDEO";
            public const string WINDOW = "WINDOW";
        }

        public class PROGRESS
        {
            public const int REMOVE = -1;
            public const int INFINITE = 101;
        }

        public class STATE
        {
            public const int MUTE = 32;
            public const int INFINITE = 16;
            public const int FIX = 8;
            public const int DISABLE = 4;
            public const int BLUR = 2;
            public const int BLINK = 1;
            public const int NONE = 0;
        }

        public static string GetMediaType(string url)
        {
            if (!string.IsNullOrEmpty(url))
            {
                switch (Path.GetExtension(url).ToLower(CultureInfo.CurrentCulture))
                {
                    case ".com": return "application/x-msdownload";
                    case ".dll": return "application/x-msdownload";
                    case ".exe": return "application/x-msdownload";
                    case ".msi": return "application/x-msdownload";
                    case ".wmf": return "application/x-msmetafile";
                    case ".ani": return "application/x-navi-animation";
                    case ".bin": return "application/octet-stream";
                    case ".cda": return "application/x-cdf";
                    case ".csh": return "application/x-csh";
                    case ".doc": return "application/msword";
                    case ".docx": return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
                    case ".hlp": return "application/winhlp";
                    case ".jsn": return "application/json";
                    case ".json": return "application/json";
                    case ".ogx": return "application/ogg";
                    case ".pdf": return "application/pdf";
                    case ".ppt": return "application/application/vnd.ms-powerpoint";
                    case ".pptx": return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
                    case ".rtf": return "application/rtf";
                    case ".sh": return "application/x-sh";
                    case ".swf": return "application/x-shockwave-flash";
                    case ".tml": return "application/tml";
                    case ".torrent": return "application/x-bittorrent";
                    case ".xhtml": return "application/xhtml+xml";
                    case ".xls": return "application/vnd.a_Context2-excel";
                    case ".xlsx": return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
                    case ".xml": return "application/xml";
                    case ".yaml": return "application/yml";
                    case ".yml": return "application/yml";
                    case ".7z": return "application/x-7z-compressed";
                    case ".ace": return "application/x-ace-compressed";
                    case ".arc": return "application/x-freearc";
                    case ".bz": return "application/x-bzip";
                    case ".bz2": return "application/x-bzip2";
                    case ".gz": return "application/gzip";
                    case ".gzip": return "application/gzip";
                    case ".jar": return "application/java-archive";
                    case ".rar": return "application/vnd.rar";
                    case ".ser": return "application/java-serialized-object";
                    case ".tar": return "application/x-tar";
                    case ".tex": return "application/x-tex";
                    case ".tgz": return "application/gzip";
                    case ".zip": return "application/zip";
                    case ".aac": return "audio/aac";
                    case ".aff": return "audio/aiff";
                    case ".aif": return "audio/aiff";
                    case ".aifc": return "audio/aiff";
                    case ".aiff": return "audio/aiff";
                    case ".au": return "audio/basic";
                    case ".dts": return "audio/vnd.dts";
                    case ".flac": return "audio/flac";
                    case ".m2a": return "audio/mpeg";
                    case ".m3a": return "audio/mpeg";
                    case ".m3u": return "audio/x-mpegurl";
                    case ".m4a": return "audio/aac";
                    case ".mid": return "audio/midi";
                    case ".midi": return "audio/midi";
                    case ".mka": return "audio/mka";
                    case ".mp2": return "audio/mpeg";
                    case ".mp2a": return "audio/mpeg";
                    case ".mp3": return "audio/mpeg";
                    case ".mp4a": return "audio/mp4";
                    case ".mpga": return "audio/mpeg";
                    case ".oga": return "audio/ogg";
                    case ".ogg": return "audio/ogg";
                    case ".opus": return "audio/opus";
                    case ".ra": return "audio/x-pn-realaudio";
                    case ".ram": return "audio/x-pn-realaudio";
                    case ".rmi": return "audio/midi";
                    case ".spx": return "audio/ogg";
                    case ".wav": return "audio/wav";
                    case ".wax": return "audio/x-ms-wax";
                    case ".weba": return "audio/webm";
                    case ".wma": return "audio/x-ms-wma";
                    case ".avif": return "image/avif";
                    case ".bmp": return "image/bmp";
                    case ".cur": return "image/vnd.microsoft.icon";
                    case ".djv": return "image/vnd.djvu";
                    case ".djvu": return "image/vnd.djvu";
                    case ".dng": return "image/x-adobe-dng";
                    case ".dwg": return "image/vnd.dwg";
                    case ".gif": return "image/gif";
                    case ".heic": return "image/heic";
                    case ".heif": return "image/heic";
                    case ".icns": return "image/x-icns";
                    case ".ico": return "image/x-icon";
                    case ".jfif": return "image/jpeg";
                    case ".jif": return "image/jpeg";
                    case ".jpe": return "image/jpeg";
                    case ".jpeg": return "image/jpeg";
                    case ".jpg": return "image/jpeg";
                    case ".jps": return "image/jpeg";
                    case ".pbm": return "image/x-portable-ms";
                    case ".pcx": return "image/x-pcx";
                    case ".pgm": return "image/x-portable-graymap";
                    case ".pic": return "image/x-pict";
                    case ".png": return "image/png";
                    case ".pnm": return "image/x-portable-anymap";
                    case ".ppm": return "image/x-portable-pixmap";
                    case ".psd": return "image/vnd.adobe.photoshop";
                    case ".raw": return "image/x-panasonic-raw";
                    case ".rw2": return "image/x-panasonic-raw";
                    case ".rwl": return "image/x-panasonic-raw";
                    case ".svg": return "image/svg+xml";
                    case ".svgz": return "image/svg+xml";
                    case ".tif": return "image/tiff";
                    case ".tiff": return "image/tiff";
                    case ".wbmp": return "image/vnd.wap.wbmp";
                    case ".webp": return "image/webp";
                    case ".xbm": return "image/x-xbitmap";
                    case ".xpm": return "image/x-xpixmap";
                    case ".otf": return "font/otf";
                    case ".ttf": return "font/ttf";
                    case ".woff": return "font/woff";
                    case ".woff2": return "font/woff2";
                    case ".dwf": return "model/vnd.dwf";
                    case ".gdl": return "model/vnd.gdl";
                    case ".gtw": return "model/vnd.gtw";
                    case ".iges": return "model/iges";
                    case ".igs": return "model/iges";
                    case ".mesh": return "model/mesh";
                    case ".msh": return "model/mesh";
                    case ".silo": return "model/mesh";
                    case ".vrl": return "model/vrml";
                    case ".vrml": return "model/vrml";
                    case ".vtu": return "model/vnd.vtu";
                    case ".x3d": return "model/x3d+xml";
                    case ".bat": return "text/cmd";
                    case ".c": return "text/x-c";
                    case ".cmd": return "text/cmd";
                    case ".cpp": return "text/x-c";
                    case ".css": return "text/css";
                    case ".csv": return "text/csv";
                    case ".cxx": return "text/x-c";
                    case ".f": return "text/x-fortran";
                    case ".h": return "text/x-c";
                    case ".hpp": return "text/x-c";
                    case ".htm": return "text/html";
                    case ".html": return "text/html";
                    case ".ics": return "text/calendar";
                    case ".inc": return "text/x-pascal";
                    case ".java": return "text/x-java-source";
                    case ".js": return "text/javascript";
                    case ".markdown": return "text/markdown";
                    case ".md": return "text/markdown";
                    case ".mjs": return "text/javascript";
                    case ".p": return "text/x-pascal";
                    case ".pas": return "text/x-pascal";
                    case ".php": return "text/php";
                    case ".py": return "text/x-python";
                    case ".rtx": return "text/richtext";
                    case ".text": return "text/plain";
                    case ".tsv": return "text/tab-separated-values";
                    case ".txt": return "text/plain";
                    case ".uri": return "text/uri-list";
                    case ".urls": return "text/uri-list";
                    case ".3g2": return "video/3gpp2";
                    case ".3gp": return "video/3gpp";
                    case ".3gpp": return "video/3gpp";
                    case ".3gpp2": return "video/3gpp2";
                    case ".avi": return "video/x-msvideo";
                    case ".f4v": return "video/x-f4v";
                    case ".fli": return "video/x-fli";
                    case ".flv": return "video/x-flv";
                    case ".h261": return "video/h261";
                    case ".h263": return "video/h263";
                    case ".h264": return "video/h264";
                    case ".jpgm": return "video/jpm";
                    case ".jpgv": return "video/jpeg";
                    case ".jpm": return "video/jpm";
                    case ".m1v": return "video/mpeg";
                    case ".m2v": return "video/mpeg";
                    case ".m4u": return "video/vnd.mpegurl";
                    case ".m4v": return "video/x-m4v";
                    case ".mkv": return "video/mkv";
                    case ".mov": return "video/quicktime";
                    case ".movie": return "video/x-sgi-movie";
                    case ".mp4": return "video/mp4";
                    case ".mp4v": return "video/mp4";
                    case ".mpa": return "video/mpeg";
                    case ".mpe": return "video/mpeg";
                    case ".mpeg": return "video/mpeg";
                    case ".mpg": return "video/mpeg";
                    case ".mpg4": return "video/mp4";
                    case ".mxu": return "video/vnd.mpegurl";
                    case ".ogv": return "video/ogg";
                    case ".qt": return "video/quicktime";
                    case ".ts": return "video/mp2t";
                    case ".viv": return "video/vnd.vivo";
                    case ".webm": return "video/webm";
                    case ".wm": return "video/x-ms-wm";
                    case ".wmv": return "video/x-ms-wmv";
                    case ".wmx": return "video/x-ms-wmx";
                    case ".wvx": return "video/x-ms-wvx";
                }
            }
            return "";
        }

        public static string GetName(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                var a_Context = value.Trim();
                var a_Name = a_Context.ToLower(CultureInfo.CurrentCulture);
                var a_Index = a_Context.LastIndexOf('.');
                if (a_Name.StartsWith("data:image/", StringComparison.InvariantCulture))
                {
                    return NAME.PICTURE;
                }
                if (a_Name.StartsWith("data:video/", StringComparison.InvariantCulture))
                {
                    return NAME.VIDEO;
                }
                if (a_Name.StartsWith("data:audio/", StringComparison.InvariantCulture))
                {
                    return NAME.AUDIO;
                }
                if (a_Index >= 0)
                {
                    a_Name = a_Name.Substring(a_Index, a_Context.Length - a_Index);
                }
                if (a_Index >= 0)
                {
                    switch (a_Name)
                    {
                        case ".aac": return NAME.AUDIO;
                        case ".aax": return NAME.AUDIO;
                        case ".ac3": return NAME.AUDIO;
                        case ".aiff": return NAME.AUDIO;
                        case ".au": return NAME.AUDIO;
                        case ".amb": return NAME.AUDIO;
                        case ".ape": return NAME.AUDIO;
                        case ".dsf": return NAME.AUDIO;
                        case ".dts": return NAME.AUDIO;
                        case ".flac": return NAME.AUDIO;
                        case ".m1a": return NAME.AUDIO;
                        case ".m2a": return NAME.AUDIO;
                        case ".m4a": return NAME.AUDIO;
                        case ".m4b": return NAME.AUDIO;
                        case ".mka": return NAME.AUDIO;
                        case ".mp2": return NAME.AUDIO;
                        case ".mp3": return NAME.AUDIO;
                        case ".mpa": return NAME.AUDIO;
                        case ".mpc": return NAME.AUDIO;
                        case ".mpp": return NAME.AUDIO;
                        case ".ra": return NAME.AUDIO;
                        case ".oga": return NAME.AUDIO;
                        case ".ogg": return NAME.AUDIO;
                        case ".opus": return NAME.AUDIO;
                        case ".wav": return NAME.AUDIO;
                        case ".wma": return NAME.AUDIO;
                        case ".wv": return NAME.AUDIO;
                    }
                }
                if (a_Index >= 0)
                {
                    switch (a_Name)
                    {
                        case ".bmp": return NAME.PICTURE;
                        case ".cur": return NAME.PICTURE;
                        case ".dds": return NAME.PICTURE;
                        case ".dng": return NAME.PICTURE;
                        case ".exr": return NAME.PICTURE;
                        case ".erf": return NAME.PICTURE;
                        case ".ico": return NAME.PICTURE;
                        case ".gif": return NAME.PICTURE;
                        case ".hdr": return NAME.PICTURE;
                        case ".heic": return NAME.PICTURE;
                        case ".heif": return NAME.PICTURE;
                        case ".jfif": return NAME.PICTURE;
                        case ".jp2": return NAME.PICTURE;
                        case ".jpe": return NAME.PICTURE;
                        case ".jpeg": return NAME.PICTURE;
                        case ".jpg": return NAME.PICTURE;
                        case ".jps": return NAME.PICTURE;
                        case ".mng": return NAME.PICTURE;
                        case ".pbm": return NAME.PICTURE;
                        case ".pcx": return NAME.PICTURE;
                        case ".pict": return NAME.PICTURE;
                        case ".pgm": return NAME.PICTURE;
                        case ".png": return NAME.PICTURE;
                        case ".pnm": return NAME.PICTURE;
                        case ".ppm": return NAME.PICTURE;
                        case ".psd": return NAME.PICTURE;
                        case ".tif": return NAME.PICTURE;
                        case ".tiff": return NAME.PICTURE;
                        case ".tga": return NAME.PICTURE;
                        case ".wbmp": return NAME.PICTURE;
                        case ".webp": return NAME.PICTURE;
                        case ".wpg": return NAME.PICTURE;
                    }
                }
                if (a_Index >= 0)
                {
                    switch (a_Name)
                    {
                        case ".3g2": return NAME.VIDEO;
                        case ".3gp": return NAME.VIDEO;
                        case ".asf": return NAME.VIDEO;
                        case ".av1": return NAME.VIDEO;
                        case ".avi": return NAME.VIDEO;
                        case ".f4v": return NAME.VIDEO;
                        case ".flv": return NAME.VIDEO;
                        case ".hevc": return NAME.VIDEO;
                        case ".m1v": return NAME.VIDEO;
                        case ".m2v": return NAME.VIDEO;
                        case ".m4p": return NAME.VIDEO;
                        case ".m4v": return NAME.VIDEO;
                        case ".mjpeg": return NAME.VIDEO;
                        case ".mkv": return NAME.VIDEO;
                        case ".mks": return NAME.VIDEO;
                        case ".mov": return NAME.VIDEO;
                        case ".mp1": return NAME.VIDEO;
                        case ".mp2": return NAME.VIDEO;
                        case ".mp4": return NAME.VIDEO;
                        case ".mpe": return NAME.VIDEO;
                        case ".mpeg": return NAME.VIDEO;
                        case ".mpg": return NAME.VIDEO;
                        case ".mpv": return NAME.VIDEO;
                        case ".mts": return NAME.VIDEO;
                        case ".ogg": return NAME.VIDEO;
                        case ".ogm": return NAME.VIDEO;
                        case ".ogv": return NAME.VIDEO;
                        case ".rm": return NAME.VIDEO;
                        case ".rmvb": return NAME.VIDEO;
                        case ".swf": return NAME.VIDEO;
                        case ".vob": return NAME.VIDEO;
                        case ".webm": return NAME.VIDEO;
                        case ".wmv": return NAME.VIDEO;
                    }
                }
                if (a_Index >= 0)
                {
                    switch (a_Name)
                    {
                        case ".html": return NAME.BROWSER;
                        case ".htm": return NAME.BROWSER;
                    }
                }
                if (!string.IsNullOrEmpty(a_Name))
                {
                    if (a_Name.StartsWith("https://", StringComparison.InvariantCulture)) return NAME.BROWSER;
                    if (a_Name.StartsWith("http://", StringComparison.InvariantCulture)) return NAME.BROWSER;
                    if (a_Name.StartsWith("ftp://", StringComparison.InvariantCulture)) return NAME.BROWSER;
                    if (a_Name.StartsWith("file://", StringComparison.InvariantCulture)) return NAME.BROWSER;
                }
            }
            return "";
        }
    }
}
