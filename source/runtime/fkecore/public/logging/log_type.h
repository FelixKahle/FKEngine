// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	enum class log_type : uint8_t
	{
		no_logging = 0,
		fatal,
		error,
		warning,
		display,
		log
	};
}