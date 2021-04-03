// Copyright 2021 Felix Kahle.All rights reserved.

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"
#include "miscellaneous/output_device.h"
#include "miscellaneous/var_args_helper.h"
#include "miscellaneous/output_device_redirector.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		void output_device::log(log_type type, const char_t* str)
		{
			serialize(str, type, FKE_NAME_NONE);
		}
		void output_device::log(log_type type, const char_t_string& s)
		{
			serialize(s.c_str(), type, FKE_NAME_NONE);
		}
		void output_device::log(const char_t_string& category, log_type type, const char_t* str)
		{
			serialize(str, type, category);
		}
		void output_device::log(const char_t_string& category, log_type type, const char_t_string& s)
		{
			serialize(s.c_str(), type, category);
		}
		void output_device::log(const char_t* str)
		{
			serialize(str, log_type::log, FKE_NAME_NONE);
		}
		void output_device::log(const char_t_string& s)
		{
			serialize(s.c_str(), log_type::log, FKE_NAME_NONE);
		}

		// Do not inline these functions, in case we need to capture a call stack in FOutputDeviceError::serialize. We need to be certain of how many frames to ignore.
		FKE_FORCENOINLINE void output_device::categorized_logf_impl(const char_t_string& category, log_type type, const char_t* fmt, ...)
		{
			FKE_GROWABLE_LOGF(serialize(buffer, type, category));
		}
		FKE_FORCENOINLINE void output_device::logf_impl(log_type type, const char_t* fmt, ...)
		{
			FKE_GROWABLE_LOGF(serialize(buffer, type, FKE_NAME_NONE));
		}
		FKE_FORCENOINLINE void output_device::logf_impl(const char_t* fmt, ...)
		{
			FKE_GROWABLE_LOGF(serialize(buffer, log_type::log, FKE_NAME_NONE));
		}
	}
}