// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "logging/log_type.h"
#include "logging/log_category.h"
#include "miscellaneous/standard_library_include.h"
#include "templates/is_array_or_ref_of_type.h"
#include "templates/is_valid_variadic_function_arg.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	// An output device.
	class FKECORE_API output_device
	{
	public:
		output_device(bool auto_register = true)
			: suppress_event_tag(false)
			, auto_emit_line_terminator(true)
		{}

		output_device(output_device&&) = default;
		output_device(const output_device&) = default;
		output_device& operator=(output_device&&) = default;
		output_device& operator=(const output_device&) = default;

		virtual ~output_device() = default;

		virtual void serialize(const char_t* v, log_type type, const char_t_string& category) = 0;
		virtual void serialize(const char_t* v, log_type type, const char_t_string& category, const double time)
		{
			serialize(v, type, category);
		}

		virtual void flush()
		{
		}

		/**
		 * Closes output device and cleans up. This can't happen in the destructor
		 * as we might have to call "delete" which cannot be done for static/ global
		 * objects.
		 */
		virtual void tear_down()
		{
		}

		/**
		 * @return whether this output device can be used on any thread.
		 */
		virtual bool can_be_used_on_any_thread() const
		{
			return false;
		}

		/**
		 * @return whether this output device can be used from multiple threads simultaneously without any locking
		 */
		virtual bool can_be_used_on_multiple_threads() const
		{
			return false;
		}

		void set_suppress_event_tag(bool in_suppress_event_tag)
		{
			suppress_event_tag = in_suppress_event_tag;
		}

		FKE_FORCEINLINE bool get_suppress_event_tag() const { return suppress_event_tag; }

		void set_auto_emit_line_terminator(bool in_auto_emit_line_terminator)
		{
			auto_emit_line_terminator = in_auto_emit_line_terminator;
		}

		FKE_FORCEINLINE bool get_auto_emit_line_terminator() const { return auto_emit_line_terminator; }

		// Simple text printing.
		void log(const char_t* s);
		void log(log_type type, const char_t* s);
		void log(const char_t_string& category, log_type type, const char_t* s);
		void log(const char_t_string& s);
		void log(log_type type, const char_t_string& s);
		void log(const char_t_string& category, log_type type, const char_t_string& s);

	private:
		void FKE_VARARGS logf_impl(const char_t* fmt, ...);
		void FKE_VARARGS logf_impl(log_type type, const char_t* fmt, ...);
		void FKE_VARARGS categorized_logf_impl(const char_t_string& category, log_type type, const char_t* Fmt, ...);

	public:
		template <typename fmt_type>
		void logf(const fmt_type& fmt)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");

			return log(fmt);
		}

		template <typename fmt_type, typename... types>
		FKE_FORCEINLINE void logf(const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to output_device::logf");

			logf_impl(fmt, args...);
		}

		template <typename fmt_type, typename... types>
		FKE_FORCEINLINE void logf(log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to output_device::logf");

			logf_impl(type, fmt, args...);
		}

		template <typename fmt_type, typename... types>
		FKE_FORCEINLINE void categorized_logf(const char_t_string& category, log_type type, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to output_device::categorized_logf");

			categorized_logf_impl(category, type, fmt, args...);
		}

	protected:
		/** Whether to output the 'Log: ' type front... */
		bool suppress_event_tag;
		/** Whether to output a line-terminator after each log call... */
		bool auto_emit_line_terminator;
	};
}