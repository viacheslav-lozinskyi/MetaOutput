#pragma warning disable CA1707 // Identifiers should not contain underscores
#pragma warning disable CA1716 // Identifiers should not match keywords

using atom;
using System;
using System.Threading;

namespace basic
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public class AnyObject
    {
        private static ValueType s_Sync = 1;

        public class CONSTANT
        {
            public class CONTROL : pattern.data.Control.CONSTANT
            {
            }

            public class MESSAGE : pattern.data.Message.CONSTANT
            {
            }
        }

        public class NAME
        {
            public class ALIGNMENT : pattern.data.Alignment.NAME
            {
            }

            public class COLOR : pattern.data.Color.NAME
            {
            }

            public class CONTROL : pattern.data.Control.NAME
            {
            }

            public class CULTURE : pattern.data.Culture.NAME
            {
            }

            public class CURSOR : pattern.data.Cursor.NAME
            {
            }

            public class EVENT : pattern.data.Event.NAME
            {
            }

            public class KEYBOARD : pattern.data.Keyboard.NAME
            {
            }

            public class FONT : pattern.data.Font.NAME
            {
            }

            public class METADATA : pattern.data.Metadata.NAME
            {
            }

            public class SOURCE : pattern.data.Source.NAME
            {
            }
        }

        public class STATE
        {
            public class CONTROL : pattern.data.Control.STATE
            {
            }

            public class FONT : pattern.data.Font.STATE
            {
            }

            public class MESSAGE : pattern.data.Message.STATE
            {
            }
        }

        public class TML : Trace.TML
        {
        }

        public class VARIABLE
        {
            public class COLOR : pattern.data.Color.VARIABLE
            {
            }

            public class KEYBOARD : pattern.data.Keyboard.VARIABLE
            {
            }

            public class MOUSE : pattern.data.Mouse.VARIABLE
            {
            }
        }

        protected static void _Lock()
        {
            Monitor.Enter(s_Sync);
        }

        protected static void _Unlock()
        {
            Monitor.Exit(s_Sync);
        }
    }
}
