#pragma warning disable CA1707 // Identifiers should not contain underscores

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Alignment
    {
        public class NAME
        {
            public const int NONE = 0x00;
            public const int LEFT = 0x01;
            public const int TOP = 0x02;
            public const int RIGHT = 0x04;
            public const int BOTTOM = 0x08;
            public const int CENTER = 0x10;
            public const int CLIENT = 0x20;
            public const int CONTENT = 0x40;
            public const int CENTER_LEFT = CENTER | LEFT;
            public const int CENTER_TOP = CENTER | TOP;
            public const int CENTER_RIGHT = CENTER | RIGHT;
            public const int CENTER_BOTTOM = CENTER | BOTTOM;
            public const int CONTENT_LEFT = CONTENT | LEFT;
            public const int CONTENT_TOP = CONTENT | TOP;
            public const int CONTENT_RIGHT = CONTENT | RIGHT;
            public const int CONTENT_BOTTOM = CONTENT | BOTTOM;
            public const int LEFT_BOTTOM = LEFT | BOTTOM;
            public const int LEFT_TOP = LEFT | TOP;
            public const int RIGHT_BOTTOM = RIGHT | BOTTOM;
            public const int RIGHT_TOP = RIGHT | TOP;
        }

        public static string ToString(int value)
        {
            var a_Result = "";
            {
                if ((value & NAME.LEFT) == NAME.LEFT) a_Result += " LEFT";
                if ((value & NAME.TOP) == NAME.TOP) a_Result += " TOP";
                if ((value & NAME.RIGHT) == NAME.RIGHT) a_Result += " RIGHT";
                if ((value & NAME.BOTTOM) == NAME.BOTTOM) a_Result += " BOTTOM";
                if ((value & NAME.CLIENT) == NAME.CLIENT) a_Result += " CLIENT";
                if ((value & NAME.CENTER) == NAME.CENTER) a_Result += " CENTER";
                if ((value & NAME.CONTENT) == NAME.CONTENT) a_Result += " CONTENT";
            }
            return a_Result.Trim();
        }
    }
}
