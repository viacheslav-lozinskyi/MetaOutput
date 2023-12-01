#pragma warning disable CA1716 // Identifiers should not match keywords
#pragma warning disable CA1720 // Identifier contains type name

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    [System.Reflection.Obfuscation(Exclude = true, StripAfterObfuscation = true)]
    public static class Event
    {
        public class NAME
        {
            public const string CLASS = "CLASS";
            public const string CONTROL = "CONTROL";
            public const string CRITICAL = "CRITICAL";
            public const string DEBUG = "DEBUG";
            public const string EMERGENCY = "EMERGENCY";
            public const string ERROR = "ERROR";
            public const string EXCEPTION = "EXCEPTION";
            public const string FILE = "FILE";
            public const string FOLDER = "FOLDER";
            public const string FOOTER = "FOOTER";
            public const string FUNCTION = "FUNCTION";
            public const string HEADER = "HEADER";
            public const string HINT = "HINT";
            public const string INFO = "INFO";
            public const string LINK = "LINK";
            public const string MESSAGE = "MESSAGE";
            public const string OBJECT = "OBJECT";
            public const string PARAMETER = "PARAMETER";
            public const string PROJECT = "PROJECT";
            public const string REQUEST = "REQUEST";
            public const string RESPONSE = "RESPONSE";
            public const string TEXT = "TEXT";
            public const string TRANSFORM = "TRANSFORM";
            public const string TRANSLATION = "TRANSLATION";
            public const string UNKNOWN = "UNKNOWN";
            public const string VARIABLE = "VARIABLE";
            public const string WARNING = "WARNING";
        }
    }
}
