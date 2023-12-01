#pragma warning disable CA1707 // Identifiers should not contain underscores

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Mouse
    {
        public static string PATTERN => typeof(Mouse).FullName;

        public const string CLICK = "CLICK";
        public const string CLICK_CENTER = "CLICK.CENTER";
        public const string CLICK_LEFT = "CLICK.LEFT";
        public const string CLICK_RIGHT = "CLICK.RIGHT";
        public const string CURSOR_X = "CURSOR.X";
        public const string CURSOR_Y = "CURSOR.Y";
        public const string DOUBLE_CLICK = "DOUBLE.CLICK";
        public const string FORCE = "FORCE";
        public const string KEY_DOWN = "KEY.DOWN";
        public const string KEY_UP = "KEY.UP";
        public const string MOVE = "MOVE";
        public const string OVER = "OVER";
        public const string WHEEL = "WHEEL";

        public class VARIABLE
        {
            public const string BUTTON_CENTER = "<<SHARED>>HMI/KEYBOARD/BUTTON.CENTER";
            public const string BUTTON_LEFT = "<<SHARED>>HMI/KEYBOARD/BUTTON.LEFT";
            public const string BUTTON_RIGHT = "<<SHARED>>HMI/KEYBOARD/BUTTON.RIGHT";
            public const string KEY_DOWN = "<<SHARED>>HMI/KEYBOARD/KEY.DOWN";
            public const string KEY_UP = "<<SHARED>>HMI/KEYBOARD/KEY.UP";
        }
    }
}
