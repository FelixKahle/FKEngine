// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_module.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{

		/** Miscellaneous platform functions. */
		struct FKECORE_API generic_platform_misc
		{
			FKE_STATIC_STRUCT(generic_platform_misc)

				/** Return true if a debugger is present */
				FKE_FORCEINLINE static bool is_debugger_present()
			{
#if FKE_BUILD_SHIPPING
				return 0;
#else
				return 1;
#endif
			}
		};
	}
}