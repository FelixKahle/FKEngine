// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Needed for FKE_DLLEXPORT and FKE_DLLIMPORT.
#include "hardware_abstraction_layer/platform.h"
#include "module/module_setup.h"
#include "fkecore.h"

#if FKEENTITIES_LINK_DYNAMICALLY
	// fkeentities_EXPORTS is defined CMake.
	#if defined(fkeentities_EXPORTS)
		/** Exports/Imports symbols or does nothing. Depends on build settings. */
		#define FKEENTITIES_API FKE_DLLEXPORT
	#else
		/** Exports/Imports symbols or does nothing. Depends on build settings. */
		#define FKEENTITIES_API FKE_DLLIMPORT
	#endif
#else
	/** Exports/Imports symbols or does nothing. Depends on build settings. */
	#define FKEENTITIES_API
#endif

namespace fkengine
{
	namespace fkeentities
	{
		using namespace fkecore;
		FKE_DECLARE_LOG_CATEGORY_EXTERN(fkeentities_log);
		FKEENTITIES_API int lol();
	}
}

