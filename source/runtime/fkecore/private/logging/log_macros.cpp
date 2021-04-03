// Copyright 2021 Felix Kahle.All rights reserved.

#include "miscellaneous/standard_library_include.h"
#include "logging/log_macros.h"
#include "miscellaneous/var_args_helper.h"
#include "miscellaneous/assertion_macros.h"
#include "fkecore_globals.h"

#define FKE_FILE_LINE_DESC FKE_TEXT(" [File: %s] [Line: %i] ")

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		// The lock mutex.
		static mutex log_mutex;
		// The static log buffer.
		static char_t log_static_buffer[8192];

		void log_msg::logf_impl(const char_t* file, int32_t line, const char_t_string& category, log_type type, const char_t* fmt, ...)
		{
#if !FKE_NO_LOGGING
			if (type != log_type::fatal)
			{
				FKE_GROWABLE_LOGF(FKE_GLOBAL_LOG_SINGLETON().log(category, type, buffer));
			}
			else
			{
				char_t message[4096];
				log_mutex.lock();
				FKE_GET_VARARGS(log_static_buffer, FKE_ARRAY_COUNT(log_static_buffer), FKE_ARRAY_COUNT(log_static_buffer) - 1, fmt, fmt);
				c_string::strncpy(message, log_static_buffer, FKE_ARRAY_COUNT(message) - 1);
				message[FKE_ARRAY_COUNT(message) - 1] = '\0';
				log_mutex.unlock();
				FKE_GLOBAL_LOG_SINGLETON().categorized_logf(category, type, FKE_FILE_LINE_DESC FKE_TEXT("%s"), file, line, message);
			}
#endif
		}

		void log_msg::logf_internal_impl(const char_t* file, int32_t line, const char_t_string& category, log_type type, const char_t* fmt, ...)
		{
#if !FKE_NO_LOGGING
			if (type != log_type::fatal)
			{
				FKE_GROWABLE_LOGF(FKE_GLOBAL_LOG_SINGLETON().log(category, type, buffer));
			}
			else
			{
				char_t message[4096];
				log_mutex.lock();
				FKE_GET_VARARGS(log_static_buffer, FKE_ARRAY_COUNT(log_static_buffer), FKE_ARRAY_COUNT(log_static_buffer) - 1, fmt, fmt);
				c_string::strncpy(message, log_static_buffer, FKE_ARRAY_COUNT(message) - 1);
				message[FKE_ARRAY_COUNT(message) - 1] = '\0';
				log_mutex.unlock();
				FKE_GLOBAL_LOG_SINGLETON().categorized_logf(category, type, FKE_FILE_LINE_DESC FKE_TEXT("%s"), file, line, message);
			}
#endif
		}



		void log_msg::logf_impl(const char_t* file, int32_t line, log_type type, const char_t* fmt, ...)
		{
#if !FKE_NO_LOGGING
			if (type != log_type::fatal)
			{
				FKE_GROWABLE_LOGF(FKE_GLOBAL_LOG_SINGLETON().log(type, buffer));
			}
			else
			{
				char_t message[4096];
				log_mutex.lock();
				FKE_GET_VARARGS(log_static_buffer, FKE_ARRAY_COUNT(log_static_buffer), FKE_ARRAY_COUNT(log_static_buffer) - 1, fmt, fmt);
				c_string::strncpy(message, log_static_buffer, FKE_ARRAY_COUNT(message) - 1);
				message[FKE_ARRAY_COUNT(message) - 1] = '\0';
				log_mutex.unlock();
				FKE_GLOBAL_LOG_SINGLETON().logf(type, FKE_FILE_LINE_DESC FKE_TEXT("%s"), file, line, message);
			}
#endif
		}

		void log_msg::logf_internal_impl(const char_t* file, int32_t line, log_type type, const char_t* fmt, ...)
		{
#if !FKE_NO_LOGGING
			if (type != log_type::fatal)
			{
				FKE_GROWABLE_LOGF(FKE_GLOBAL_LOG_SINGLETON().log(type, buffer));
			}
			else
			{
				char_t message[4096];
				log_mutex.lock();
				FKE_GET_VARARGS(log_static_buffer, FKE_ARRAY_COUNT(log_static_buffer), FKE_ARRAY_COUNT(log_static_buffer) - 1, fmt, fmt);
				c_string::strncpy(message, log_static_buffer, FKE_ARRAY_COUNT(message) - 1);
				message[FKE_ARRAY_COUNT(message) - 1] = '\0';
				log_mutex.unlock();
				FKE_GLOBAL_LOG_SINGLETON().logf(type, FKE_FILE_LINE_DESC FKE_TEXT("%s"), file, line, message);
			}
#endif
		}
	}
}