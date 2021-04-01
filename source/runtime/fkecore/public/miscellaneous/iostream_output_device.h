// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/output_device.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	class FKECORE_API iostream_output_device : public output_device
	{
	public:

		virtual void serialize(const char_t* v, log_type type, const char_t_string& category) override;
		virtual void serialize(const char_t* v, log_type type, const char_t_string& category, const double time) override;
		virtual void flush() override;
	};
}