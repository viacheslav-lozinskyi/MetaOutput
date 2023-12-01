#pragma warning disable CA1707 // Identifiers should not contain underscores

using System;
using System.Threading;

namespace basic
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public class AnyAtom
    {
        private static ValueType s_Sync = 1;

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
