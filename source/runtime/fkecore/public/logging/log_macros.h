// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "logging/log_type.h"
#include "logging/log_category.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	struct FKECORE_API log
	{
		FKE_STATIC_STRUCT(log)

		/** Log function */
		template <typename fmt_type, typename... types>
		static void logf(const char_t* file, int32_t line, const char_t_string& category, log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to log::logf");

			logf_impl(file, line, category, type, fmt, args...);
		}

		/** Log function */
		template <typename fmt_type, typename... types>
		static void logf(const char_t* file, int32_t line, log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to log::logf");

			logf_impl(file, line, type, fmt, args...);
		}

		/** Internal version of log function. Should be used only in logging macros, as it relies on caller to call assert on fatal error */
		template <typename fmt_type, typename... types>
		static void logf_internal(const char_t* file, int32_t line, const char_t_string& category, log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to log::logf_internal");

			logf_internal_impl(file, line, category, type, fmt, args...);
		}

		/** Internal version of log function. Should be used only in logging macros, as it relies on caller to call assert on fatal error */
		template <typename fmt_type, typename... types>
		static void logf_internal(const char_t* file, int32_t line, log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to log::logf_internal");

			logf_internal_impl(file, line, type, fmt, args...);
		}

	private:

		static void FKE_VARARGS logf_impl(const char_t* file, int32_t line, const char_t_string& category, log_type type, const char_t* fmt, ...);
		static void FKE_VARARGS logf_impl(const char_t* file, int32_t line, log_type type, const char_t* fmt, ...);
		static void FKE_VARARGS logf_internal_impl(const char_t* file, int32_t line, const char_t_string& category, log_type type, const char_t* fmt, ...);
		static void FKE_VARARGS logf_internal_impl(const char_t* file, int32_t line, log_type type, const char_t* fmt, ...);
	};

#define FKE_LOG_EXPAND_IS_FATAL(type, active_block, inactive_block) FKE_PREPROCESSOR_JOIN(FKE_LOG_EXPAND_IS_FATAL_, type)(active_block, inactive_block)

#if FKE_DO_CHECK
	#define FKE_LOG_SOURCE_FILE(file) FKE_TEXT(file)
#else
	#define FKE_LOG_SOURCE_FILE(file) FKE_TEXT("Unknown")
#endif

#define FKE_LOG_EXPAND_IS_FATAL_fatal(active_block, inactive_block) active_block
#define FKE_LOG_EXPAND_IS_FATAL_rrror(active_block, inactive_block) inactive_block
#define FKE_LOG_EXPAND_IS_FATAL_warning(active_block, inactive_block) inactive_block
#define FKE_LOG_EXPAND_IS_FATAL_display(active_block, inactive_block) inactive_block
#define FKE_LOG_EXPAND_IS_FATAL_log(active_block, inactive_block) inactive_block

#if FKE_NO_LOGGING
	struct no_logging_category {};

	#define FKE_LOG(category, type, fmt, ...)
	#define FKE_CLOG(condition, category_name, type, format, ...)

	#define FKE_DECLARE_LOG_CATEGORY_EXTERN(category_name) extern no_logging_category category_name;
	#define FKE_DEFINE_LOG_CATEGORY(...)
	#define FKE_DEFINE_LOG_CATEGORY_STATIC(...)
	#define FKE_DECLARE_LOG_CATEGORY_CLASS(...)
	#define FKE_DEFINE_LOG_CATEGORY_CLASS(...)

#elif FKE_ONLY_LOG_FATAL_ERRORS
	#define FKE_LOG(category_name, type, format, ...) \
			FKE_LOG_EXPAND_IS_FATAL(type, \
				auto FKE_LOG_noinline_lambda = [](const auto& l_format, const auto&... FKE_LOG_args) FKE_FORCENOINLINE \
				{ \
					log::logf_internal(FKE_LOG_SOURCE_FILE(__FILE__), __LINE__, log_type::fatal, l_format, FKE_LOG_args...); \
					FKE_DEBUG_BREAK_AND_PROMPT_FOR_REMOTE(); \
				}; \
				FKE_LOG_noinline_lambda(format, ##__VA_ARGS__); \
				FKE_LOG_EXPAND_IS_FATAL(type, FKE_CA_ASSUME(false);, FKE_PREPROCESSOR_NOTHING), \
			FKE_PREPROCESSOR_NOTHING \
			)

	/**
	 * A macro to declare a logging category as a C++ "extern", usually declared in the header and paired with FKE_DEFINE_LOG_CATEGORY in the source. Accessible by all files that include the header.
	 * @param category_name, category to declare
	 **/
	#define FKE_DECLARE_LOG_CATEGORY_EXTERN(category_name) \
			extern struct log_category##category_name : public log_category \
			{ \
				FKE_FORCEINLINE log_category##category_name() : log_category(FKE_TEXT(#category_name)) {} \
			} category_name

	 /**
	  * A macro to define a logging category, usually paired with FKE_DECLARE_LOG_CATEGORY_EXTERN from the header.
	  * @param category_name, category to define
	 **/
	#define FKE_DEFINE_LOG_CATEGORY(category_name) log_category##category_name category_name

	 /**
	  * A macro to define a logging category as a C++ "static". This should ONLY be declared in a source file. Only accessible in that single file.
	  * @param category_name, category to declare
	 **/
	#define FKE_DEFINE_LOG_CATEGORY_STATIC(category_name) \
			static struct log_category##category_name : public log_category \
			{ \
				FKE_FORCEINLINE log_category##category_name() : log_category(FKE_TEXT(#category_name)) {} \
			} category_name

	 /**
	  * A macro to declare a logging category as a C++ "class static"
	  * @param category_name, category to declare
	 **/
	#define FKE_DECLARE_LOG_CATEGORY_CLASS(category_name) \
			FKE_DEFINE_LOG_CATEGORY_STATIC(category_name)

	 /**
	  * A macro to define a logging category, usually paired with DECLARE_LOG_CATEGORY_CLASS from the header.
	  * @param category_name, category to define
	  */
	#define FKE_DEFINE_LOG_CATEGORY_CLASS(in_class, category_name) in_class::log_category##category_name in_class::category_name
#else
	#define FKE_LOG(category_name, type, format, ...) \
			{ \
				auto FKE_LOG_noinline_lambda = [](const auto& l_category_name, const auto& l_format, const auto&... FKE_LOG_args) FKE_FORCENOINLINE \
				{ \
					FKE_LOG_EXPAND_IS_FATAL(type, \
						{ \
							log::logf_internal(FKE_LOG_SOURCE_FILE(__FILE__), __LINE__, l_category_name.get_name(), log_type::fatal, l_format, FKE_LOG_args...); \
							FKE_DEBUG_BREAK_AND_PROMPT_FOR_REMOTE(); \
						}, \
						{ \
							log::logf_internal(nullptr, 0, l_category_name.get_name(), type, l_format, FKE_LOG_args...); \
						} \
					) \
				}; \
				FKE_LOG_noinline_lambda(category_name, format, ##__VA_ARGS__); \
				FKE_LOG_EXPAND_IS_FATAL(type, FKE_CA_ASSUME(false);, FKE_PREPROCESSOR_NOTHING) \
			}

#	define FKE_CLOG(condition, category_name, type, format, ...) \
			{ \
				if (condition) \
				{ \
					auto FKE_LOG_noinline_lambda = [](const auto& l_category_name, const auto& l_format, const auto&... FKE_LOG_args) FKE_FORCENOINLINE \
					{ \
						FKE_LOG_EXPAND_IS_FATAL(type, \
							{ \
								log::logf_internal(FKE_LOG_SOURCE_FILE(__FILE__), __LINE__, l_category_name.get_name(), log_type::fatal, l_format, FKE_LOG_args...); \
								FKE_DEBUG_BREAK_AND_PROMPT_FOR_REMOTE(); \
							}, \
							{ \
								log::logf_internal(nullptr, 0, l_category_name.get_name(), type, l_format, FKE_LOG_args...); \
							} \
						) \
					}; \
					FKE_LOG_noinline_lambda(category_name, format, ##__VA_ARGS__); \
					FKE_LOG_EXPAND_IS_FATAL(type, FKE_CA_ASSUME(false);, FKE_PREPROCESSOR_NOTHING) \
				} \
			}

	/**
	 * A macro to declare a logging category as a C++ "extern", usually declared in the header and paired with FKE_DEFINE_LOG_CATEGORY in the source. Accessible by all files that include the header.
	 * @param category_name, category to declare
	 **/
	#define FKE_DECLARE_LOG_CATEGORY_EXTERN(category_name) \
			extern struct log_category##category_name : public log_category \
			{ \
				FKE_FORCEINLINE log_category##category_name() : log_category(FKE_TEXT(#category_name)) {} \
			} category_name

	 /**
	  * A macro to define a logging category, usually paired with FKE_DECLARE_LOG_CATEGORY_EXTERN from the header.
	  * @param category_name, category to define
	 **/
	#define FKE_DEFINE_LOG_CATEGORY(category_name) log_category##category_name category_name

	 /**
	  * A macro to define a logging category as a C++ "static". This should ONLY be declared in a source file. Only accessible in that single file.
	  * @param category_name, category to declare
	 **/
	#define FKE_DEFINE_LOG_CATEGORY_STATIC(category_name) \
			static struct log_category##category_name : public log_category \
			{ \
				FKE_FORCEINLINE log_category##category_name() : log_category(FKE_TEXT(#category_name)) {} \
			} category_name

	 /**
	  * A macro to declare a logging category as a C++ "class static"
	  * @param category_name, category to declare
	 **/
	#define FKE_DECLARE_LOG_CATEGORY_CLASS(category_name) \
			FKE_DEFINE_LOG_CATEGORY_STATIC(category_name)

	 /**
	  * A macro to define a logging category, usually paired with DECLARE_LOG_CATEGORY_CLASS from the header.
	  * @param category_name, category to define
	  */
	#define FKE_DEFINE_LOG_CATEGORY_CLASS(in_class, category_name) in_class::log_category##category_name in_class::category_name
#endif
}