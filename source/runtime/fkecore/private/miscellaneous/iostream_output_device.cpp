// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/c_string.h"
#include "miscellaneous/iostream_output_device.h"
#include "miscellaneous/output_device_helper.h"

// Needed for wcout and cout.
#include <iostream>

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		void iostream_output_device::serialize(const char_t* data, log_type type, const char_t_string& category, const double time)
		{
			char_t output_string[FKE_MAX_SPRINTF] = FKE_TEXT("");
			c_string::sprintf(output_string, FKE_TEXT("%s%s"), output_device_helper::format_log_line(type, category, data, time, true).c_str(), FKE_LINE_TERMINATOR);

#if FKE_UNICODE
			wcout << output_string;
#else
			cout << output_string;
#endif
		}

		void iostream_output_device::serialize(const char_t* data, log_type type, const char_t_string& category)
		{
			serialize(data, type, category, -1.0f);
		}

		void iostream_output_device::flush()
		{
#if FKE_UNICODE
			wcout.flush();
#else
			cout.flush();
#endif
		}
	}
}