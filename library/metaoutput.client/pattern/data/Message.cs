#pragma warning disable CA1707 // Identifiers should not contain underscores

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Message
    {
        public class CONSTANT
        {
            public class OUTPUT
            {
                public const int MAX_BUFFER_SIZE = 128 * 1024 * 1024;
                public const string MUTEX = "urn:metaoutput:mutex:EXECUTE";
            }

            public class PIPE
            {
                public const int TIMEOUT = 1000; // TODO: Reduce it
                public const int BUFFER_SIZE = 256 * 1024;
                public const string TERMINATE_REQUEST = "urn:metaoutput:tool:<<<CLIENT-TERMINATE>>>";
                public const string MUTEX = "urn:metaoutput:mutex:PIPE";
                public const string DEMO = "urn:metaoutput:tool:DEMO";
                public const string METAOUTPUT = "urn:metaoutput:tool:DEFAULT";
            }

            public class TML
            {
                public const string ATTRIBUTE = "@@@";
                public const string COMMENT = "###";
                public const string FUNCTION_BEGIN = "(((";
                public const string FUNCTION_END = ")))";
                public const string GROUP_BEGIN = "<<<";
                public const string GROUP_END = ">>>";
                public const string NEW_LINE = "|||";
                public const string PARAMETER = "&&&";
                public const string TRANSLATE_BEGIN = "[[[";
                public const string TRANSLATE_END = "]]]";
                public const string VARIABLE_BEGIN = "{{{";
                public const string VARIABLE_END = "}}}";
            }
        }

        public class STATE
        {
            public const int NONE = 0x00000000;
            public const int BEEP = 0x00000200;
            public const int BLINK = 0x00000400;
            public const int CLEAR = 0x00000800;
            public const int COLLAPSE = 0x00001000;
            public const int EXPAND = 0x00002000;
            public const int FIX = 0x00004000;
            public const int FOCUS = 0x00008000;
            public const int HIDE = 0x00010000;
            public const int LOCK = 0x00020000;
            public const int MUTE = 0x00040000;
            public const int PIN = 0x00080000;
            public const int REMOVE = 0x00100000;
            public const int RESEND = 0x00200000;
            public const int SHOW = 0x00400000;
            public const int SPEAK = 0x00800000;
            public const int UNFIX = 0x01000000;
            public const int UNFOCUS = 0x02000000;
            public const int UNLOCK = 0x04000000;
            public const int UNPIN = 0x08000000;
            public const int UPDATE = 0x10000000;
        }
    }
}
