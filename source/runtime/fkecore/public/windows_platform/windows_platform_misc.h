// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_module.h"
#include "generic_platform/generic_platform_misc.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	struct FKECORE_API windows_platform_misc : public generic_platform_misc
	{
		FKE_STATIC_STRUCT(windows_platform_misc)

#if !FKE_BUILD_SHIPPING
		static bool is_debugger_present();
#endif
	};

	typedef windows_platform_misc platform_misc;
}