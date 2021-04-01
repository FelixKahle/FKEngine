// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Needed for FKE_DLLEXPORT and FKE_DLLIMPORT.
#include "hardware_abstraction_layer/platform.h"
#include "module/module_setup.h"

#if FKECORE_LINK_DYNAMICALLY
	// fkeentities_EXPORTS is defined CMake.
	#if defined(fkecore_EXPORTS)
		/** Exports/Imports symbols or does nothing. Depends on build settings. */
		#define FKECORE_API FKE_DLLEXPORT
	#else
		/** Exports/Imports symbols or does nothing. Depends on build settings. */
		#define FKECORE_API FKE_DLLIMPORT
	#endif
#else
	/** Exports/Imports symbols or does nothing. Depends on build settings. */
	#define FKECORE_API
#endif

FKE_DEFINE_MODULE(fkecore, FKECORE_API)