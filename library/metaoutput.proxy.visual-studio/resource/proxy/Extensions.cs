using System;
using System.IO;

namespace resource
{
    namespace proxy
    {
        public class Extensions : extension.AnyProxy
        {
            protected override bool _Execute(atom.Trace context, string command, string param)
            {
                return false;
            }

            protected override bool _ReadMetadata(atom.Trace context, string name, ref string value)
            {
                return false;
            }

            protected override bool _ReadVariable(atom.Trace context, string name, ref string value)
            {
                return false;
            }

            protected override bool _WriteVariable(atom.Trace context, string name, string value)
            {
                return false;
            }
        };
    }
}
