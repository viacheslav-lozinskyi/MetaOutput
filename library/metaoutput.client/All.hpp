#pragma once

#include <metaplatform.core/All.hpp>

#define MP_METAOUTPUT_CLIENT

#if !defined(MP_PLATFORM_CLI) || defined(MP_COMPILING_METAOUTPUT_CLIENT) || defined(MP_COMPILING_METAOUTPUT_CORE)
#include "pattern/data/Alignment.hpp"
#include "pattern/data/Color.hpp"
#include "pattern/data/Culture.hpp"
#include "pattern/data/Cursor.hpp"
#include "pattern/data/Event.hpp"
#include "pattern/data/Font.hpp"
#include "pattern/data/Keyboard.hpp"
#include "pattern/data/Message.hpp"
#include "pattern/data/Metadata.hpp"
#include "pattern/data/Mouse.hpp"
#include "pattern/data/Source.hpp"
#include "pattern/data/Control.hpp"
#include "atom/Trace.hpp"
#include "extension/AnyPreview.hpp"
#include "extension/AnyTool.hpp"
#endif
