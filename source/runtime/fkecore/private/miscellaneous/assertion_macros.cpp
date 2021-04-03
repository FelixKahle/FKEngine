// Copyright 2021 Felix Kahle.All rights reserved.

#include "fkecore_types.h"
#include "miscellaneous/assertion_macros.h"
#include "templates/array_count.h"
#include "hardware_abstraction_layer/platform_misc.h"
#include "fkecore_globals.h"

#define FKE_FILE_LINE_DESC FKE_TEXT(" [File: %s] [Line: %i] ")

// TODO: Propper time logging.

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
#if FKE_DO_CHECK
		static void assert_failed_impl_v(const char_t* expr, const char_t* file, int32_t line, const char_t* format, va_list args)
		{
			char_t description_string[4096];
			c_string::get_var_args(description_string, FKE_ARRAY_COUNT(description_string), format, args);

			char_t error_string[FKE_MAX_SPRINTF];
			c_string::sprintf(error_string, FKE_TEXT("%s"), expr);

			FKE_GLOBAL_LOG_SINGLETON().logf(log_type::fatal, FKE_TEXT("Assertion failed: %s") FKE_FILE_LINE_DESC FKE_TEXT("\n%s\n"), error_string, file, line, description_string);

			// Make sure the error message (assertion message) as well as all other logs get logged.
			FKE_GLOBAL_LOG_SINGLETON().flush();
		}

		void FKE_FORCENOINLINE debug::check_verify_failed_impl(const char_t* expr, const char_t* file, const int line, const char_t* format, ...)
		{
			va_list args;

			va_start(args, format);
			assert_failed_impl_v(expr, file, line, format, args);
			va_end(args);
		}
#endif
	}
}