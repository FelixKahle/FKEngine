// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "miscellaneous/standard_library_include.h"
#include "miscellaneous/output_device_redirector.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace globals
	{
	}
}

#define FKE_GLOBAL_LOG_SINGLETON() fkengine::fkecore::output_device_redirector::get()