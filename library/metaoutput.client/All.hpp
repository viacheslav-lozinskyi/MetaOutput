
#pragma once

#include <metaplatform.core/All.hpp>

#define MP_METAOUTPUT_CLIENT

#if !defined(MP_PLATFORM_CLI) || defined(MP_COMPILING_METAOUTPUT_CLIENT) || defined(MP_COMPILING_METAOUTPUT_CORE)
#include "atom/Trace.hpp"
#include "extension/AnyExport.hpp"
#include "extension/AnyImport.hpp"
#include "extension/AnyPreview.hpp"
#include "extension/AnySource.hpp"
#endif
