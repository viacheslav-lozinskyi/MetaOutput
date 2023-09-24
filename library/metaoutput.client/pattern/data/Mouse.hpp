#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Mouse
        {
        public:
            MP_CLASS VARIABLE
            {
                MP_CONSTANT_STRING(BUTTON_CENTER, "<<SHARED>>HMI/KEYBOARD/BUTTON.CENTER");
                MP_CONSTANT_STRING(BUTTON_LEFT, "<<SHARED>>HMI/KEYBOARD/BUTTON.LEFT");
                MP_CONSTANT_STRING(BUTTON_RIGHT, "<<SHARED>>HMI/KEYBOARD/BUTTON.RIGHT");
                MP_CONSTANT_STRING(KEY_DOWN, "<<SHARED>>HMI/KEYBOARD/KEY.DOWN");
                MP_CONSTANT_STRING(KEY_UP, "<<SHARED>>HMI/KEYBOARD/KEY.UP");
            };
        public:
            MP_CONSTANT_PATTERN(Mouse);
            MP_CONSTANT_NAME(CLICK);
            MP_CONSTANT_NAME(CLICK_CENTER);
            MP_CONSTANT_NAME(CLICK_LEFT);
            MP_CONSTANT_NAME(CLICK_RIGHT);
            MP_CONSTANT_NAME(CURSOR_X);
            MP_CONSTANT_NAME(CURSOR_Y);
            MP_CONSTANT_NAME(DOUBLE_CLICK);
            MP_CONSTANT_NAME(FORCE);
            MP_CONSTANT_NAME(KEY_DOWN);
            MP_CONSTANT_NAME(KEY_UP);
            MP_CONSTANT_NAME(MOVE);
            MP_CONSTANT_NAME(OVER);
            MP_CONSTANT_NAME(WHEEL);
        };
    }
}
