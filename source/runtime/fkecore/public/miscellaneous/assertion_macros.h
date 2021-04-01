// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/c_string.h"
#include "miscellaneous/var_args.h"
#include "hardware_abstraction_layer/platform_misc.h"
#include "templates/is_valid_variadic_function_arg.h"
#include "templates/is_array_or_ref_of_type.h"

#if (FKE_DO_CHECK || FKE_DO_GUARD_SLOW || FKE_DO_ENSURE) && !FKE_PLATFORM_CPU_ARM_FAMILY
	// We'll put all assert implementation code into a separate section in the linked
	// executable. This code should never execute so using a separate section keeps
	// it well off the hot path and hopefully out of the instruction cache. It also
	// facilitates reasoning about the makeup of a compiled/linked binary.
	#define FKE_DEBUG_SECTION FKE_PLATFORM_CODE_SECTION(".fkedbg")
#else
	// On ARM we can't do this because the executable will require jumps larger
	// than the branch instruction can handle. Clang will only generate
	// the trampolines in the .text segment of the binary. If the fkedbg segment
	// is present it will generate code that it cannot link.
	#define FKE_DEBUG_SECTION
#endif

/** The namespace of the FKEngine. */
namespace fkengine
{
	struct FKECORE_API debug
	{
		FKE_STATIC_STRUCT(debug)

#if FKE_DO_CHECK
	private:

		static void FKE_VARARGS check_verify_failed_impl(const char_t* expr, const char_t* file, int32_t line, const char_t* format, ...);

	public:

		template <typename fmt_type, typename... types>
		static void FKE_DEBUG_SECTION check_verify_failed(const char_t* expr, const char_t* file, int32_t line, const fmt_type& format, types... Args);

#endif
	};

#if FKE_DO_CHECK
	template <typename fmt_type, typename... types>
	void FKE_FORCENOINLINE FKE_DEBUG_SECTION debug::check_verify_failed(
		const char_t* expr,
		const char_t* file,
		const int line,
		const fmt_type& format,
		types... args)
	{
		static_assert(is_array_or_ref_of_type<fmt_type, char_t>::value, "Formatting string must be a char_t array.");
		static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to check_verify_failed()");

		return check_verify_failed_impl(expr, file, line, format, args...);
	}

	// MSVC (v19.00.24215.1 at time of writing) ignores no-inline attributes on
	// lambdas. This can be worked around by calling the lambda from inside this
	// templated (and correctly non-inlined) function.
	template <typename ret_type = void, class inner_type>
	ret_type FKE_FORCENOINLINE FKE_DEBUG_SECTION dispatch_check_verify(inner_type&& inner)
	{
		return inner();
	}
#endif

#if !FKE_BUILD_SHIPPING
	#define FKE_DEBUG_BREAK_AND_PROMPT_FOR_REMOTE() \
		if (platform_misc::is_debugger_present()) { FKE_PLATFORM_BREAK(); }
#else
	#define FKE_DEBUG_BREAK_AND_PROMPT_FOR_REMOTE()
#endif

#if FKE_DO_CHECK
	#define FKE_CHECK_IMPL(expr) \
			{ \
				if (FKE_UNLIKELY(!(expr))) \
				{ \
					struct check_impl \
					{ \
						static void FKE_FORCENOINLINE FKE_DEBUG_SECTION exec_check_impl_internal() \
						{ \
							fkengine::debug::check_verify_failed(FKE_TEXT(#expr), FKE_TEXT(__FILE__), __LINE__, FKE_TEXT("")); \
						} \
					}; \
					check_impl::exec_check_impl_internal(); \
					if (platform_misc::is_debugger_present()) \
					{ \
						FKE_PLATFORM_BREAK(); \
					} \
					FKE_CA_ASSUME(false); \
				} \
			}

	#ifndef FKE_CHECK_CODE
		#define FKE_CHECK_CODE(code) do { code; } while ( false );
	#endif
	#ifndef FKE_VERIFY
		#define FKE_VERIFY(expr) FKE_CHECK_IMPL(expr)
	#endif
	#ifndef FKE_CHECK
		#define FKE_CHECK(expr)	FKE_CHECK_IMPL(expr)
	#endif

	#define FKE_CHECK_F_IMPL(expr, format, ...) \
			{ \
				if(FKE_UNLIKELY(!(expr))) \
				{ \
					fkengine::dispatch_check_verify([&] () FKE_FORCENOINLINE FKE_DEBUG_SECTION \
					{ \
						debug::check_verify_failed(FKE_TEXT(#expr), FKE_TEXT(__FILE__), __LINE__, format, ##__VA_ARGS__); \
					}); \
					if (platform_misc::is_debugger_present()) \
					{ \
						FKE_PLATFORM_BREAK(); \
					} \
					FKE_CA_ASSUME(false); \
				} \
			}

	#ifndef FKE_VERIFYF
		#define FKE_VERIFYF(expr, format,  ...) FKE_CHECK_F_IMPL(expr, format, ##__VA_ARGS__)
	#endif
	#ifndef FKE_CHECKF
		#define FKE_CHECKF(expr, format,  ...) FKE_CHECK_F_IMPL(expr, format, ##__VA_ARGS__)
	#endif

	/**
	 * Denotes code paths that should never be reached.
	 */
	#ifndef FKE_CHECK_NO_ENTRY
		#define FKE_CHECK_NO_ENTRY() FKE_CHECK(!"Enclosing block should never be called")
	#endif

	/**
	 * Denotes code paths that should not be executed more than once.
	 */
	#ifndef FKE_CHECK_NO_REENTRY
		#define FKE_CHECK_NO_REENTRY() \
				{ \
					static bool been_here##__LINE__ = false; \
	                FKE_CHECK( !"Enclosing block was called more than once" || !been_here##__LINE__ ); \
					been_here##__LINE__ = true; \
				}
	#endif

	class recursion_scope_marker
	{
	public: 
		recursion_scope_marker(uint16_t &in_counter) : counter( in_counter ) { ++counter; }
		~recursion_scope_marker() { --counter; }
	private:
		uint16_t& counter;
	};

	/**
	 * Denotes code paths that should never be called recursively.
	 */
	#ifndef FKE_CHECK_NO_RECURSION
		#define checkNoRecursion() \
				static uint16_t recursion_counter##__LINE__ = 0; \
	            FKE_CHECK( !"Enclosing block was entered recursively" || recursion_counter##__LINE__ == 0 );  \
	            const fkengine::recursion_scope_marker ScopeMarker##__LINE__( recursion_counter##__LINE__ )
	#endif

	#ifndef FKE_UNIMPLEMENTED
		#define FKE_UNIMPLEMENTED() FKE_CHECK(!"Unimplemented function called")
	#endif
#else
	#define FKE_CHECK_CODE(...)
	#define FKE_CHECK(expr)					{ FKE_CA_ASSUME(expr); }
	#define FKE_CHECKF(expr, format, ...)	{ FKE_CA_ASSUME(xxpr); }
	#define FKE_CHECK_NO_ENTRY()
	#define FKE_CHECK_NO_REENTRY()
	#define FKE_CHECK_NO_RECURSION()
	#define FKE_VERIFY(expr)				{ if(FKE_UNLIKELY(!(expr))){ FKE_CA_ASSUME(false); } }
	#define FKE_VERIFYF(expr, format, ...)	{ if(FKE_UNLIKELY(!(expr))){ FKE_CA_ASSUME(false); } }
	#define FKE_UNIMPLEMENTED()				{ FKE_CA_ASSUME(false); }
#endif

#define FKE_CALL_FUNCTION_ONLY_FROM_THREAD(thread_id) FKE_CHECKF(this_thread::get_id() == thread_id, FKE_TEXT("%s can not be called from this thread"), FKE_TEXT(FKE_PRETTY_FUNCTION))

}