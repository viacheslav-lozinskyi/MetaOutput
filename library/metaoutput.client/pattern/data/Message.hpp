#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Message
        {
        public:
            MP_CLASS CONSTANT
            {
            public:
                MP_CLASS OUTPUT
                {
                    MP_CONSTANT_STRING(MUTEX, "urn:metaoutput:mutex:EXECUTE");
                    MP_CONSTANT_INTEGER(MAX_BUFFER_SIZE, 100 * 1024 * 1024);
                };
            public:
                MP_CLASS PIPE
                {
                    MP_CONSTANT_STRING(METAOUTPUT, "urn:metaoutput:tool:DEFAULT");
                    MP_CONSTANT_STRING(DEMO, "urn:metaoutput:tool:DEMO");
                    MP_CONSTANT_STRING(MUTEX, "urn:metaoutput:mutex:PIPE");
                    MP_CONSTANT_STRING(TERMINATE_REQUEST, "urn:metaoutput:tool:<<<CLIENT-TERMINATE>>>");
                    MP_CONSTANT_INTEGER(BUFFER_SIZE, 256 * 1024);
                    MP_CONSTANT_INTEGER(TIMEOUT, 100);
                };
            };
        public:
            MP_CLASS STATE
            {
                MP_CONSTANT_INTEGER(NONE,       0x00000000);
                MP_CONSTANT_INTEGER(BEEP,       0x00000200);
                MP_CONSTANT_INTEGER(BLINK,      0x00000400);
                MP_CONSTANT_INTEGER(CLEAR,      0x00000800);
                MP_CONSTANT_INTEGER(COLLAPSE,   0x00001000);
                MP_CONSTANT_INTEGER(EXPAND,     0x00002000);
                MP_CONSTANT_INTEGER(FIX,        0x00004000);
                MP_CONSTANT_INTEGER(FOCUS,      0x00008000);
                MP_CONSTANT_INTEGER(HIDE,       0x00010000);
                MP_CONSTANT_INTEGER(LOCK,       0x00020000);
                MP_CONSTANT_INTEGER(MUTE,       0x00040000);
                MP_CONSTANT_INTEGER(PIN,        0x00080000);
                MP_CONSTANT_INTEGER(REMOVE,     0x00100000);
                MP_CONSTANT_INTEGER(RESEND,     0x00200000);
                MP_CONSTANT_INTEGER(SHOW,       0x00400000);
                MP_CONSTANT_INTEGER(SPEAK,      0x00800000);
                MP_CONSTANT_INTEGER(UNFIX,      0x01000000);
                MP_CONSTANT_INTEGER(UNFOCUS,    0x02000000);
                MP_CONSTANT_INTEGER(UNLOCK,     0x04000000);
                MP_CONSTANT_INTEGER(UNPIN,      0x08000000);
                MP_CONSTANT_INTEGER(UPDATE,     0x10000000);
            };
        public:
            MP_CLASS TML
            {
                MP_CONSTANT_STRING(ATTRIBUTE, "@@@");
                MP_CONSTANT_STRING(COMMENT, "###");
                MP_CONSTANT_STRING(FUNCTION_BEGIN, "(((");
                MP_CONSTANT_STRING(FUNCTION_END, ")))");
                MP_CONSTANT_STRING(GROUP_BEGIN, "<<<");
                MP_CONSTANT_STRING(GROUP_END, ">>>");
                MP_CONSTANT_STRING(NEW_LINE, "|||");
                MP_CONSTANT_STRING(PARAMETER, "@@"); // TODO: Remove it
                MP_CONSTANT_STRING(PARAMETER0, "&&&");
                MP_CONSTANT_STRING(TRANSLATE_BEGIN, "[[[");
                MP_CONSTANT_STRING(TRANSLATE_END, "]]]");
                MP_CONSTANT_STRING(VARIABLE_BEGIN, "{{{");
                MP_CONSTANT_STRING(VARIABLE_END, "}}}");
            };
        };
    }
}
