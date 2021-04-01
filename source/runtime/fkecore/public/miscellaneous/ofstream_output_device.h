// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/output_device.h"

#include <fstream>

/** The namespace of the FKEngine. */
namespace fkengine
{
	class FKECORE_API ofstream_output_device : public output_device
	{
	public:

		ofstream_output_device(const char_t* output_file_name);
		~ofstream_output_device();

		virtual void serialize(const char_t* v, log_type type, const char_t_string& category) override;
		virtual void serialize(const char_t* v, log_type type, const char_t_string& category, const double time) override;
		virtual void flush() override;

	private:
		basic_ofstream<char_t> device_ofstream;
	};
}