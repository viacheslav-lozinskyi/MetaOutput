#pragma once

#include <metaplatform.core/All.hpp>

namespace pattern
{
    namespace data
    {
        MP_CLASS_SHARED Event
        {
        public:
            MP_CLASS NAME
            {
                MP_CONSTANT_STRING(UNKNOWN, "UNKNOWN");
                MP_CONSTANT_STRING(CLASS, "CLASS");
                MP_CONSTANT_STRING(CONTROL, "CONTROL");
                MP_CONSTANT_STRING(CRITICAL, "CRITICAL");
                MP_CONSTANT_STRING(DEBUG, "DEBUG");
                MP_CONSTANT_STRING(ERROR, "ERROR");
                MP_CONSTANT_STRING(EMERGENCY, "EMERGENCY");
                MP_CONSTANT_STRING(EXCEPTION, "EXCEPTION");
                MP_CONSTANT_STRING(FILE, "FILE");
                MP_CONSTANT_STRING(FOLDER, "FOLDER");
                MP_CONSTANT_STRING(FOOTER, "FOOTER");
                MP_CONSTANT_STRING(FUNCTION, "FUNCTION");
                MP_CONSTANT_STRING(HEADER, "HEADER");
                MP_CONSTANT_STRING(HINT, "HINT");
                MP_CONSTANT_STRING(INFO, "INFO");
                MP_CONSTANT_STRING(LINK, "LINK");
                MP_CONSTANT_STRING(MESSAGE, "MESSAGE");
                MP_CONSTANT_STRING(OBJECT, "OBJECT");
                MP_CONSTANT_STRING(PARAMETER, "PARAMETER");
                MP_CONSTANT_STRING(PROJECT, "PROJECT");
                MP_CONSTANT_STRING(REQUEST, "REQUEST");
                MP_CONSTANT_STRING(RESPONSE, "RESPONSE");
                MP_CONSTANT_STRING(TEXT, "TEXT");
                MP_CONSTANT_STRING(TRANSFORM, "TRANSFORM");
                MP_CONSTANT_STRING(TRANSLATION, "TRANSLATION");
                MP_CONSTANT_STRING(VARIABLE, "VARIABLE");
                MP_CONSTANT_STRING(WARNING, "WARNING");
            };
        };
    }
}
