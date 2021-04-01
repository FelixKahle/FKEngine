// Copyright 2021 Felix Kahle. All rights reserved.

#include "fkecore_module.h"
#include "windows_platform/windows_platform_misc.h"

#include <Windows.h>

/** The namespace of the FKEngine. */
namespace fkengine
{
#if !FKE_BUILD_SHIPPING
	bool windows_platform_misc::is_debugger_present()
	{
		return !!::IsDebuggerPresent();
	}
#endif
}