// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "miscellaneous/output_device_helper.h"

// TODO: Propper time logging.

/** The namespace of the FKEngine. */
namespace fkengine
{
	const char_t* output_device_helper::log_type_to_string(log_type type)
	{
		switch (type)
		{
		case log_type::no_logging:
			return TEXT("No Logging");
		case log_type::fatal:
			return TEXT("Fatal Error");
		case log_type::error:
			return TEXT("Error");
		case log_type::warning:
			return TEXT("Warning");
		case log_type::display:
			return TEXT("Display");
		case log_type::log:
			return TEXT("Log");
		}
		return TEXT("Unknown Log Type");
	}

	// time unused, change in future versions.
	char_t_string output_device_helper::format_log_line(log_type type, const char_t_string& category, const char_t* message, const double time, const bool show_type)
	{
		const bool show_category = !(category.empty());
		char_t_string format;

		if (show_category)
		{
			format += category.c_str();
			format += FKE_TEXT(": ");

			if (show_type)
			{
				format += log_type_to_string(type);
				format += FKE_TEXT(": ");
			}
		}
		else if (show_type)
		{
			format += log_type_to_string(type);
			format += FKE_TEXT(": ");
		}

		if (message)
		{
			format += message;
		}
		return format;
	}
}