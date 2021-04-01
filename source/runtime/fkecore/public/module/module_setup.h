// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "miscellaneous/eastl_pre_setup.h"

#define FKE_DEFINE_MODULE(name, api) \
		struct name##_module_info \
		{ \
			static api const char_t* name##_module_name(); \
		};

/**
 * Implements a module.
 * Needs to be put in a source file.
 * 
 * @param name - The name of the module to implement.
 */
#define FKE_IMPLEMENT_MODULE(name) \
		const char_t* name##_module_info::name##_module_name() \
		{ \
			return FKE_TEXT(#name); \
		}
		