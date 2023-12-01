#pragma warning disable CA1707 // Identifiers should not contain underscores

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Font
    {
        public class NAME
        {
            public const string ARIAL = "Arial";
            public const string COURIER = "Courier";
            public const string COURIER_NEW = "Courier New";
            public const string GARAMOND = "Garamond";
            public const string GEORGIA = "Georgia";
            public const string IMPACT = "Impact";
            public const string LUCIDA = "Lucida";
            public const string SANS_SERIF = "Sans Serif";
            public const string SERIF = "Serif";
            public const string TAHOMA = "Tahoma";
            public const string TIMES_NEW_ROMAN = "Times New Roman";
            public const string VERDANA = "Verdana";
        }

        public class STATE
        {
            public const int NONE = 0x00000000;
            public const int BOLD = 0x00000020;
            public const int ITALIC = 0x00000040;
            public const int STRIKEOUT = 0x00000080;
            public const int UNDERLINE = 0x00000100;
        }

        public static string ToString(int state)
        {
            var a_Result = "";
            {
                if ((state & STATE.BOLD) == STATE.BOLD) a_Result += " BOLD";
                if ((state & STATE.ITALIC) == STATE.ITALIC) a_Result += " ITALIC";
                if ((state & STATE.STRIKEOUT) == STATE.STRIKEOUT) a_Result += " STRIKEOUT";
                if ((state & STATE.UNDERLINE) == STATE.UNDERLINE) a_Result += " UNDERLINE";
            }
            return a_Result.Trim();
        }
    }
}