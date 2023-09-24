#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Font
        {
        public:
            MP_CLASS NAME
            {
                MP_CONSTANT_STRING(ARIAL, "Arial");
                MP_CONSTANT_STRING(COURIER, "Courier");
                MP_CONSTANT_STRING(COURIER_NEW, "Courier New");
                MP_CONSTANT_STRING(GEORGIA, "Georgia");
                MP_CONSTANT_STRING(GARAMOND, "Garamond");
                MP_CONSTANT_STRING(IMPACT, "Impact");
                MP_CONSTANT_STRING(LUCIDA, "Lucida");
                MP_CONSTANT_STRING(SERIF, "Serif");
                MP_CONSTANT_STRING(SANS_SERIF, "Sans Serif");
                MP_CONSTANT_STRING(TAHOMA, "Tahoma");
                MP_CONSTANT_STRING(TIMES_NEW_ROMAN, "Times New Roman");
                MP_CONSTANT_STRING(VERDANA, "Verdana");
            };
        public:
            MP_CLASS STATE
            {
                MP_CONSTANT_INTEGER(NONE,      0x00000000);
                MP_CONSTANT_INTEGER(BOLD,      0x00000020);
                MP_CONSTANT_INTEGER(ITALIC,    0x00000040);
                MP_CONSTANT_INTEGER(STRIKEOUT, 0x00000080);
                MP_CONSTANT_INTEGER(UNDERLINE, 0x00000100);
            };
        };
    }
}
