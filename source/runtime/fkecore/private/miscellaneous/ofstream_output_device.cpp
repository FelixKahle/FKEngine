// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/c_string.h"
#include "miscellaneous/ofstream_output_device.h"
#include "miscellaneous/output_device_helper.h"
#include "miscellaneous/time.h"
#include <iostream>

namespace fkengine
{
	ofstream_output_device::ofstream_output_device(const char_t* output_file_name)
	{
		// Give the file a unique name.
		// This name is made of the current data and time and the actual file name passed in this function.
		// For example year-month-day-hour-minute-second-Log File.txt
		chrono::system_clock::time_point now = chrono::system_clock::now();
		char_t_string actual_file_name = time_conversation::time_point_to_string<char_t>(now, FKE_TEXT("%Y-%m-%d-%H-%M-%S")) + FKE_TEXT("-") + output_file_name;
		device_ofstream.open(actual_file_name, ios_base::out);
	}

	ofstream_output_device::~ofstream_output_device()
	{
		device_ofstream.close();
	}

	void ofstream_output_device::serialize(const char_t* v, log_type type, const char_t_string& category)
	{
		serialize(v, type, category, -1.0f);
	}

	void ofstream_output_device::serialize(const char_t* data, log_type type, const char_t_string& category, const double time)
	{
		char_t output_string[FKE_MAX_SPRINTF] = FKE_TEXT("");
		c_string::sprintf(output_string, FKE_TEXT("%s%s"), output_device_helper::format_log_line(type, category, data, time).c_str(), FKE_LINE_TERMINATOR);

		device_ofstream << output_string;
	}

	void ofstream_output_device::flush()
	{
		device_ofstream.flush();
	}
}
