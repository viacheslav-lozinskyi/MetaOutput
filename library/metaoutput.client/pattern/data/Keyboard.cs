#pragma warning disable CA1707 // Identifiers should not contain underscores
#pragma warning disable CA1720 // Identifier contains type name

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Keyboard
    {
        public static string PATTERN => typeof(Keyboard).FullName;

        public const string KEY = "KEY";
        public const string KEY_DOWN = "KEY.DOWN";
        public const string KEY_UP = "KEY.UP";
        public const string TEXT = "TEXT";

        public class NAME
        {
            public class KEY
            {
                public const string A = "A";
                public const string ADD = "ADD";
                public const string ALT_LEFT = "ALT.LEFT";
                public const string ALT_RIGHT = "ALT.RIGHT";
                public const string APPS = "APPS";
                public const string B = "B";
                public const string BACK = "BACK";
                public const string BROWSER_BACK = "BROWSER.BACK";
                public const string BROWSER_FAVORITES = "BROWSER.FAVORITES";
                public const string BROWSER_FIND = "BROWSER.FIND";
                public const string BROWSER_FORWARD = "BROWSER.FORWARD";
                public const string BROWSER_HOME = "BROWSER.HOME";
                public const string BROWSER_REFRESH = "BROWSER.REFRESH";
                public const string BROWSER_STOP = "BROWSER.STOP";
                public const string C = "C";
                public const string CANCEL = "CANCEL";
                public const string CAPS_LOCK = "CAPS.LOCK";
                public const string CLEAR = "CLEAR";
                public const string CTRL_LEFT = "CTRL.LEFT";
                public const string CTRL_RIGHT = "CTRL.RIGHT";
                public const string D = "D";
                public const string D0 = "D0";
                public const string D1 = "D1";
                public const string D2 = "D2";
                public const string D3 = "D3";
                public const string D4 = "D4";
                public const string D5 = "D5";
                public const string D6 = "D6";
                public const string D7 = "D7";
                public const string D8 = "D8";
                public const string D9 = "D9";
                public const string DECIMAL = "DECIMAL";
                public const string DELETE = "DELETE";
                public const string DIVIDE = "DIVIDE";
                public const string DOWN = "DOWN";
                public const string E = "E";
                public const string END = "END";
                public const string ESCAPE = "ESCAPE";
                public const string EXECUTE = "EXECUTE";
                public const string F = "F";
                public const string F1 = "F1";
                public const string F10 = "F10";
                public const string F11 = "F11";
                public const string F12 = "F12";
                public const string F13 = "F13";
                public const string F14 = "F14";
                public const string F15 = "F15";
                public const string F16 = "F16";
                public const string F17 = "F17";
                public const string F18 = "F18";
                public const string F19 = "F19";
                public const string F2 = "F2";
                public const string F20 = "F20";
                public const string F21 = "F21";
                public const string F22 = "F22";
                public const string F23 = "F23";
                public const string F24 = "F24";
                public const string F3 = "F3";
                public const string F4 = "F4";
                public const string F5 = "F5";
                public const string F6 = "F6";
                public const string F7 = "F7";
                public const string F8 = "F8";
                public const string F9 = "F9";
                public const string G = "G";
                public const string H = "H";
                public const string HELP = "HELP";
                public const string HOME = "HOME";
                public const string I = "I";
                public const string INSERT = "INSERT";
                public const string J = "J";
                public const string K = "K";
                public const string L = "L";
                public const string LAUNCH_APPLICATION1 = "LAUNCH.APPLICATION1";
                public const string LAUNCH_APPLICATION2 = "LAUNCH.APPLICATION2";
                public const string LAUNCH_MAIL = "LAUNCH.MAIL";
                public const string LEFT = "LEFT";
                public const string LINE_FEED = "LINE.FEED";
                public const string M = "M";
                public const string MEDIA_NEXT_TRACK = "MEDIA.NEXT.TRACK";
                public const string MEDIA_PLAY_PAUSE = "MEDIA.PLAY.PAUSE";
                public const string MEDIA_PREV_TRACK = "MEDIA.PREV.TRACK";
                public const string MEDIA_SELECT = "MEDIA.SELECT";
                public const string MEDIA_STOP = "MEDIA.STOP";
                public const string MULTIPLY = "MULTIPLY";
                public const string N = "N";
                public const string NUM_LOCK = "NUM.LOCK";
                public const string NUMPAD_0 = "NUMPAD.0";
                public const string NUMPAD_1 = "NUMPAD.1";
                public const string NUMPAD_2 = "NUMPAD.2";
                public const string NUMPAD_3 = "NUMPAD.3";
                public const string NUMPAD_4 = "NUMPAD.4";
                public const string NUMPAD_5 = "NUMPAD.5";
                public const string NUMPAD_6 = "NUMPAD.6";
                public const string NUMPAD_7 = "NUMPAD.7";
                public const string NUMPAD_8 = "NUMPAD.8";
                public const string NUMPAD_9 = "NUMPAD.9";
                public const string O = "O";
                public const string OEM_AUTO = "OEM.AUTO";
                public const string OEM_BACK_SLASH = "OEM.BACK.SLASH";
                public const string OEM_BACK_TAB = "OEM.BACK.TAB";
                public const string OEM_CLEAR = "OEM.CLEAR";
                public const string OEM_CLOSE_BRACKETS = "OEM.CLOSE.BRACKETS";
                public const string OEM_COMMA = "OEM.COMMA";
                public const string OEM_COPY = "OEM.COPY";
                public const string OEM_ENLW = "OEM.ENLW";
                public const string OEM_FINISH = "OEM.FINISH";
                public const string OEM_MINUS = "OEM.MINUS";
                public const string OEM_OPEN_BRACKETS = "OEM.OPEN.BRACKETS";
                public const string OEM_PERIOD = "OEM.PERIOD";
                public const string OEM_PIPE = "OEM.PIPE";
                public const string OEM_PLUS = "OEM.PLUS";
                public const string OEM_QUESTION = "OEM.QUESTION";
                public const string OEM_QUOTES = "OEM.QUOTES";
                public const string OEM_SEMICOLON = "OEM.SEMICOLON";
                public const string OEM_TILDE = "OEM.TILDE";
                public const string P = "P";
                public const string PAGE_DOWN = "PAGE.DOWN";
                public const string PAGE_UP = "PAGE.UP";
                public const string PAUSE = "PAUSE";
                public const string PLAY = "PLAY";
                public const string PRINT = "PRINT";
                public const string PRINT_SCREEN = "PRINT.SCREEN";
                public const string Q = "Q";
                public const string R = "R";
                public const string RETURN = "RETURN";
                public const string RIGHT = "RIGHT";
                public const string S = "S";
                public const string SCROLL = "SCROLL";
                public const string SELECT = "SELECT";
                public const string SEPARATOR = "SEPARATOR";
                public const string SHIFT_LEFT = "SHIFT.LEFT";
                public const string SHIFT_RIGHT = "SHIFT.RIGHT";
                public const string SLEEP = "SLEEP";
                public const string SPACE = "SPACE";
                public const string SUBTRACT = "SUBTRACT";
                public const string SYSTEM = "SYSTEM";
                public const string T = "T";
                public const string TAB = "TAB";
                public const string U = "U";
                public const string UP = "UP";
                public const string V = "V";
                public const string VOLUME_DOWN = "VOLUME.DOWN";
                public const string VOLUME_MUTE = "VOLUME.MUTE";
                public const string VOLUME_UP = "VOLUME.UP";
                public const string W = "W";
                public const string WIN_LEFT = "WIN.LEFT";
                public const string WIN_RIGHT = "WIN.RIGHT";
                public const string X = "X";
                public const string Y = "Y";
                public const string Z = "Z";
                public const string ZOOM = "ZOOM";
            }
        }

        public class VARIABLE
        {
            public const string BUTTON_ALT = "<<SHARED>>HMI/KEYBOARD/BUTTON.ALT";
            public const string BUTTON_CAPS = "<<SHARED>>HMI/KEYBOARD/BUTTON.CAPS";
            public const string BUTTON_CONTROL = "<<SHARED>>HMI/KEYBOARD/BUTTON.CONTROL";
            public const string BUTTON_NUM_LOCK = "<<SHARED>>HMI/KEYBOARD/BUTTON.NUM.LOCK";
            public const string BUTTON_SCROLL_LOCK = "<<SHARED>>HMI/KEYBOARD/BUTTON.SCROLL.LOCK";
            public const string BUTTON_SHIFT = "<<SHARED>>HMI/KEYBOARD/BUTTON.SHIFT";
            public const string BUTTON_WINDOWS = "<<SHARED>>HMI/KEYBOARD/BUTTON.WINDOWS";
            public const string KEY_DOWN = "<<SHARED>>HMI/KEYBOARD/KEY.DOWN";
            public const string KEY_UP = "<<SHARED>>HMI/KEYBOARD/KEY.UP";
        }
    }
}
