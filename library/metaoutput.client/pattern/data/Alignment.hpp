#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Alignment
        {
        public:
            MP_CLASS NAME
            {
                MP_CONSTANT_INTEGER(NONE,           0x00);
                MP_CONSTANT_INTEGER(LEFT,           0x01);
                MP_CONSTANT_INTEGER(TOP,            0x02);
                MP_CONSTANT_INTEGER(RIGHT,          0x04);
                MP_CONSTANT_INTEGER(BOTTOM,         0x08);
                MP_CONSTANT_INTEGER(CENTER,         0x10);
                MP_CONSTANT_INTEGER(CLIENT,         0x20);
                MP_CONSTANT_INTEGER(CONTENT,        0x40);
                MP_CONSTANT_INTEGER(CENTER_LEFT,    CENTER | LEFT);
                MP_CONSTANT_INTEGER(CENTER_TOP,     CENTER | TOP);
                MP_CONSTANT_INTEGER(CENTER_RIGHT,   CENTER | RIGHT);
                MP_CONSTANT_INTEGER(CENTER_BOTTOM,  CENTER | BOTTOM);
                MP_CONSTANT_INTEGER(CONTENT_LEFT,   CONTENT | LEFT);
                MP_CONSTANT_INTEGER(CONTENT_TOP,    CONTENT | TOP);
                MP_CONSTANT_INTEGER(CONTENT_RIGHT,  CONTENT | RIGHT);
                MP_CONSTANT_INTEGER(CONTENT_BOTTOM, CONTENT | BOTTOM);
                MP_CONSTANT_INTEGER(LEFT_BOTTOM,    LEFT | BOTTOM);
                MP_CONSTANT_INTEGER(LEFT_TOP,       LEFT | TOP);
                MP_CONSTANT_INTEGER(RIGHT_BOTTOM,   RIGHT | BOTTOM);
                MP_CONSTANT_INTEGER(RIGHT_TOP,      RIGHT | TOP);
            };
        };
    }
}
