// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "generic_platform/generic_platform.h"
#include <sal.h>

#if defined(__clang__)
	#include "clang_platform/clang_platform.h"
#else
	#include "windows_platform/windows_platform.h"
#endif

#define FKE_PLATFORM_DESKTOP 1
#if defined(_WIN64)
	/** 1 if 64-bit, 0 otherwise. */
	#define FKE_PLATFORM_64BITS 1
#else
	/** 1 if 64-bit, 0 otherwise. */
	#define FKE_PLATFORM_64BITS 0
#endif

#if defined(__clang__)
	// @todo clang: Clang compiler on Windows doesn't support SEH exception handling yet (__try/__except)
	#define FKE_PLATFORM_SEH_EXCEPTIONS_DISABLED 1
	// @todo clang: Clang compiler on Windows doesn't support C++ exception handling yet (try/throw/catch)
	#define FKE_PLATFORM_EXCEPTIONS_DISABLED 1
#endif

// Base defines, defaults are commented out.
#if defined(__clang__)
	// @todo clang: Clang compiler on Windows doesn't support SEH exception handling yet (__try/__except)
	#define FKE_PLATFORM_SEH_EXCEPTIONS_DISABLED 1
	// @todo clang: Clang compiler on Windows doesn't support C++ exception handling yet (try/throw/catch)
	#define FKE_PLATFORM_EXCEPTIONS_DISABLED 1
#endif
#define FKE_PLATFORM_SUPPORTS_PRAGMA_PACK 1
#define FKE_PLATFORM_ENABLE_VECTORINTRINSICS 1
#ifndef FKE_PLATFORM_MAYBE_HAS_SSE4_1
	#define FKE_PLATFORM_MAYBE_HAS_SSE4_1 1
#endif
// Current unreal minspec is sse2, not sse4, so on windows any calling code must check _cpuid before calling SSE4 instructions;
// If called on a platform for which _cpuid for SSE4 returns false, attempting to call SSE4 intrinsics will crash
// If your title has raised the minspec to sse4, you can define FKE_PLATFORM_ALWAYS_HAS_SSE4_1 to 1
#ifndef FKE_PLATFORM_ALWAYS_HAS_SSE4_1
	#define FKE_PLATFORM_ALWAYS_HAS_SSE4_1 0
#endif
#define FKE_PLATFORM_USES_MICROSOFT_LIBC_FUNCTIONS 1
#define FKE_PLATFORM_COMPILER_HAS_TCHAR_WMAIN 1
#define FKE_PLATFORM_COMPILER_HAS_DECLTYPE_AUTO 1

#define FKE_LINE_TERMINATOR FKE_WIDE_TEXT("\r\n")
#define FKE_LINE_TERMINATOR_ANSI "\r\n"
#define FKE_PLATFORM_CACHE_LINE_SIZE 64

// STL setup.
//#if FKE_BUILD_DEVELOPMENT || FKE_BUILD_DEBUG
//	#define _ITERATOR_DEBUG_LEVEL 2
//#elif FKE_BUILD_SHIPPING
//	#define _ITERATOR_DEBUG_LEVEL 0
//#endif
//#if !defined(_ITERATOR_DEBUG_LEVEL)
//	#error _ITERATOR_DEBUG_LEVEL was not defined
//#endif

#include <intrin.h>

// VS' debug engine has a bug where it will silently swallow explicit
// breakpoint interrupts when single-step debugging either line-by-line or
// over call instructions. This can hide legitimate reasons to trap. Asserts
// for example, which can appear as if the did not fire, leaving a programmer
// unknowingly debugging an undefined process.
#define FKE_PLATFORM_BREAK() (__nop(), __debugbreak())

/** Functions with variable arguments */
#define FKE_VARARGS __cdecl
/** Standard C function */
#define FKE_CDECL __cdecl
/** Standard calling convention */
#define FKE_STDCALL __stdcall
/** Force code to be inline */
#define FKE_FORCEINLINE __forceinline
/** Force code to not be inline */
#define FKE_FORCENOINLINE __declspec(noinline)
/** Indicate that the function never returns. */
#define FKE_FUNCTION_NO_RETURN_START __declspec(noreturn)
/** Wrap a function signature in these (FKE_FUNCTION_NON_NULL_RETURN_START, FUNCTION_NON_NULL_RETURN_END) to indicate that the function never returns nullptr. */
#define FKE_FUNCTION_NON_NULL_RETURN_START _Ret_notnull_

#if !defined(__clang__) || defined(_MSC_VER)	// Clang only supports __assume when using -fms-extensions
	/** Hints compiler that expression is true; generally restricted to comparisons against constants. */
	#define FKE_ASSUME(expr) __assume(expr)
#endif

/** Define a 64 bit immediate int. */
#define FKE_DECLARE_UINT64(x) x

#define FKE_WIDE_TEXT(x) L ## x
#define FKE_ANSI_TEXT(x) x

#if FKE_UNICODE
	#define FKE_TEXT(x) FKE_WIDE_TEXT(x)
#else
	#define FKE_TEXT(x) FKE_ANSI_TEXT(x)
#endif

#if !defined(__clang__)
	#define FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL __pragma(optimize("",off))
	#define FKE_PRAGMA_ENABLE_OPTIMIZATION_ACTUAL __pragma(optimize("",on))
#elif defined(_MSC_VER)
	#define FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL __pragma(clang optimize off)
	#define FKE_PRAGMA_ENABLE_OPTIMIZATION_ACTUAL __pragma(clang optimize on)
#endif

/** Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable. */
#define FKE_PLATFORM_CODE_SECTION(name) __declspec(code_seg(name)) 

#if !defined(__clang__)
	// Clang expects typename outside template.
	#define FKE_TYPENAME_OUTSIDE_TEMPLATE
#endif

#pragma warning(disable : 4481) // nonstandard extension used: override specifier 'override'

#if defined(__clang__) || _MSC_VER >= 1900
	/** The constexpr keyword if supported. */
	#define FKE_CONSTEXPR constexpr
#else
	/** The constexpr keyword if supported. */
	#define FKE_CONSTEXPR const
#endif
/** The abstract keyword if supported. */
#define FKE_ABSTRACT abstract

// Alignment.
#if defined(__clang__)
	#define FKE_GCC_PACK(n) __attribute__((packed,aligned(n)))
	#define FKE_GCC_ALIGN(n) __attribute__((aligned(n)))
	#if defined(_MSC_VER)
		#define FKE_MS_ALIGN(n) __declspec(align(n))
	#endif
#else
	#define FKE_MS_ALIGN(n) __declspec(align(n))
#endif

#if !defined(__clang__)
	/**
	 * MSVC pragma.
	 *
	 * @param Pragma - The token-string.
	 */
	#define FKE_MSVC_PRAGMA(pragma) __pragma(pragma)
#endif

/** DLL export. */
#define FKE_DLLEXPORT __declspec(dllexport)
/** DLL import. */
#define FKE_DLLIMPORT __declspec(dllimport)

// Define UNICODE.
#if FKE_UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

// Disable this now as it is annoying for generic platform implementations.
#pragma warning(disable : 4100) // unreferenced formal parameter

#include "windows_platform/windows_platform_code_analysis.h"

#if FKE_USING_CODE_ANALYSIS && _MSC_VER == 1900
	/** Wrap a function signature in these (FKE_FUNCTION_CHECK_RETURN_START, FKE_FUNCTION_CHECK_RETURN_END) to warn that callers should not ignore the return value. */
	#define FKE_FUNCTION_CHECK_RETURN_START __pragma(warning(push)) __pragma(warning(disable: 28216)) __declspec("SAL_checkReturn")
	/** Wrap a function signature in these (FKE_FUNCTION_CHECK_RETURN_START, FKE_FUNCTION_CHECK_RETURN_END) to warn that callers should not ignore the return value. */
	#define FKE_FUNCTION_CHECK_RETURN_END __pragma(warning(pop))
#else
	/** Wrap a function signature in these (FKE_FUNCTION_CHECK_RETURN_START, FKE_FUNCTION_CHECK_RETURN_END) to warn that callers should not ignore the return value. */
	#define FKE_FUNCTION_CHECK_RETURN_START __declspec("SAL_checkReturn")
#endif

// Other macros
#ifndef FKE_ENABLE_WIN_ALLOC_TRACKING
	#define FKE_ENABLE_WIN_ALLOC_TRACKING 0
#endif

/** The namespace of the FKEngine. */
namespace fkengine
{
	/** Windows specific types. */
	struct windows_platform_types : public generic_platform_types
	{
		windows_platform_types(windows_platform_types&&) = delete; \
		windows_platform_types(const windows_platform_types&) = delete; \
		windows_platform_types& operator=(const windows_platform_types&) = delete; \
		windows_platform_types& operator=(windows_platform_types&&) = delete; \
	protected:

		windows_platform_types() {}

	public:

#ifdef FKE_PLATFORM_64BITS
		/** Unsigned int in the same size as a pointer. */
		typedef unsigned __int64 size;
		/** Signed int in the same size as a pointer. */
		typedef __int64	ssize;
#else
		/** Unsigned int in the same size as a pointer. */
		typedef unsigned long size;
		/** Signed int in the same size as a pointer. */
		typedef long ssize;
#endif
	};

	typedef windows_platform_types platform_types;
}

#include <Windows.h>

// Define the TEXT macro without the FKE_ naming convention. May be used by other libraries.
#ifndef TEXT
	#define TEXT(x) FKE_TEXT_WIDE(x)
#endif