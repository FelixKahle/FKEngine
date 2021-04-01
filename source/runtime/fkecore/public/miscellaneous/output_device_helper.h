// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "logging/log_type.h"
#include "logging/log_category.h"
#include "miscellaneous/standard_library_include.h"
#include "templates/is_array_or_ref_of_type.h"
#include "templates/is_valid_variadic_function_arg.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	struct FKECORE_API output_device_helper
	{
		FKE_STATIC_STRUCT(output_device_helper)

		static const char_t* log_type_to_string(log_type type);

		static char_t_string format_log_line(log_type type, const char_t_string& category, const char_t* message = nullptr, const double time = -1.0, const bool show_type = true);
	};
}