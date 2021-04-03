// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Define all other platforms to be zero.
#if !defined(FKE_PLATFORM_WINDOWS)
	#define FKE_PLATFORM_WINDOWS 0
#endif
#if !defined(FKE_PLATFORM_XBOXONE)
	#define FKE_PLATFORM_XBOXONE 0
#endif
#if !defined(FKE_PLATFORM_MAC)
	#define FKE_PLATFORM_MAC 0
#endif
#if !defined(FKE_PLATFORM_PS4)
	#define FKE_PLATFORM_PS4 0
#endif
#if !defined(FKE_PLATFORM_IOS)
	#define FKE_PLATFORM_IOS 0
#endif
#if !defined(FKE_PLATFORM_TVOS)
	#define FKE_PLATFORM_TVOS 0
#endif
#if !defined(FKE_PLATFORM_ANDROID)
	#define FKE_PLATFORM_ANDROID 0
#endif
#if !defined(FKE_PLATFORM_ANDROID_ARM)
	#define FKE_PLATFORM_ANDROID_ARM 0
#endif
#if !defined(FKE_PLATFORM_ANDROID_ARM64)
	#define FKE_PLATFORM_ANDROID_ARM64 0
#endif
#if !defined(FKE_PLATFORM_ANDROID_X86)
	#define FKE_PLATFORM_ANDROID_X86 0
#endif
#if !defined(FKE_PLATFORM_ANDROID_X64)
	#define FKE_PLATFORM_ANDROID_X64 0
#endif
#if !defined(FKE_PLATFORM_ANDROID_VULKAN)
	#define FKE_PLATFORM_ANDROID_VULKAN 0
#endif
#if !defined(FKE_PLATFORM_QUAIL)
	#define FKE_PLATFORM_QUAIL 0
#endif
#if !defined(FKE_PLATFORM_ANDROIDESDEFERRED)
	#define FKE_PLATFORM_ANDROIDESDEFERRED 0
#endif
#if !defined(FKE_PLATFORM_ANDROIDGL4)
	#define FKE_PLATFORM_ANDROIDGL4 0
#endif
#if !defined(FKE_PLATFORM_LUMINGL4)
	#define FKE_PLATFORM_LUMINGL4 0
#endif
#if !defined(FKE_PLATFORM_LUMIN)
	#define FKE_PLATFORM_LUMIN 0
#endif
#if !defined(FKE_PLATFORM_APPLE)
	#define FKE_PLATFORM_APPLE 0
#endif
#if !defined(FKE_PLATFORM_LINUX)
	#define FKE_PLATFORM_LINUX 0
#endif
#if !defined(FKE_PLATFORM_SWITCH)
	#define FKE_PLATFORM_SWITCH 0
#endif
#if !defined(FKE_PLATFORM_FREEBSD)
	#define FKE_PLATFORM_FREEBSD 0
#endif
#if !defined(FKE_PLATFORM_UNIX)
	#define FKE_PLATFORM_UNIX 0
#endif
#if !defined(FKE_PLATFORM_HOLOLENS)
	#define FKE_PLATFORM_HOLOLENS 0
#endif

#include "hardware_abstraction_layer/preprocessor_helpers.h"

// Include the platform compiler pre setup.
#include FKE_COMPILED_PLATFORM_HEADER(platform_compiler_pre_setup.h)

// Do not move this include somewhere else.
// GenericPlatformCompilerPreSetup.h must be included after the platform-specific compiler pre-setup has been included.
#include "generic_platform/generic_platform_compiler_pre_setup.h"

#ifndef FKE_PLATFORM_CPU_X86_FAMILY
	#if (defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__amd64__) || defined(__x86_64__))
		/** Whether the CPU is x86/x64 (i.e. both 32 and 64-bit variants). */
		#define FKE_PLATFORM_CPU_X86_FAMILY	1
	#else
		/** Whether the CPU is x86/x64 (i.e. both 32 and 64-bit variants). */
		#define FKE_PLATFORM_CPU_X86_FAMILY	0
	#endif
#endif

#ifndef FKE_PLATFORM_CPU_ARM_FAMILY
	#if (defined(__arm__) || defined(_M_ARM) || defined(__aarch64__) || defined(_M_ARM64))
		/** Whether the CPU is AArch32/AArch64 (i.e. both 32 and 64-bit variants). */
		#define FKE_PLATFORM_CPU_ARM_FAMILY	1
	#else
		/** Whether the CPU is AArch32/AArch64 (i.e. both 32 and 64-bit variants). */
		#define FKE_PLATFORM_CPU_ARM_FAMILY	0
	#endif
#endif

#if FKE_PLATFORM_APPLE
	// needed for size_t
	#include <stddef.h>
#endif

#include "generic_platform/generic_platform.h"

#ifndef FKE_PLATFORM_COMPILER_CLANG
	#if defined(__clang__)
		#define FKE_PLATFORM_COMPILER_CLANG	1
	#else
		#define FKE_PLATFORM_COMPILER_CLANG	0
	#endif
#endif

#if FKE_PLATFORM_WINDOWS
	#include "windows_platform/windows_platform_code_analysis.h"
#elif FKE_PLATFORM_COMPILER_CLANG
	#include "clang_platform/clang_platform_code_analysis.h"
#endif

#ifndef FKE_USING_ADDRESS_SANITISER
	#define FKE_USING_ADDRESS_SANITISER 0
#endif

// Platform header.
#include FKE_COMPILED_PLATFORM_HEADER(platform.h)

// Base defines, must define these for the platform, there are no defaults.
#ifndef FKE_PLATFORM_DESKTOP
	#error "FKE_PLATFORM_DESKTOP must be defined"
#endif
#ifndef FKE_PLATFORM_64BITS
	#error "FKE_PLATFORM_64BITS must be defined"
#endif

// Base defines, these have defaults.
#ifndef FKE_PLATFORM_EXCEPTIONS_DISABLED
	#define FKE_PLATFORM_EXCEPTIONS_DISABLED !FKE_PLATFORM_DESKTOP
#endif
#ifndef FKE_PLATFORM_SEH_EXCEPTIONS_DISABLED
	#define FKE_PLATFORM_SEH_EXCEPTIONS_DISABLED 0
#endif
#ifndef FKE_PLATFORM_SUPPORTS_PRAGMA_PACK
	#define FKE_PLATFORM_SUPPORTS_PRAGMA_PACK 0
#endif

#ifndef FKE_PLATFORM_ENABLE_VECTORINTRINSICS
	#define FKE_PLATFORM_ENABLE_VECTORINTRINSICS	0
#endif
#ifndef FKE_PLATFORM_MAYBE_HAS_SSE4_1
	#define FKE_PLATFORM_MAYBE_HAS_SSE4_1 0
#endif
#ifndef FKE_PLATFORM_ALWAYS_HAS_SSE4_1
	#define FKE_PLATFORM_ALWAYS_HAS_SSE4_1 0
#endif
#ifndef FKE_PLATFORM_MAYBE_HAS_AVX
	#define FKE_PLATFORM_MAYBE_HAS_AVX 0
#endif
#ifndef FKE_PLATFORM_ALWAYS_HAS_AVX
	#define FKE_PLATFORM_ALWAYS_HAS_AVX 0
#endif

#ifndef FKE_PLATFORM_HAS_CPUID
	#if defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__x86_64__) || defined (__amd64__)
		#define FKE_PLATFORM_HAS_CPUID 1
	#else
		#define FKE_PLATFORM_HAS_CPUID 0
	#endif
#endif
#ifndef FKE_PLATFORM_ENABLE_POPCNT_INTRINSIC
	#define FKE_PLATFORM_ENABLE_POPCNT_INTRINSIC 0
#endif
#ifndef FKE_PLATFORM_ENABLE_VECTORINTRINSICS_NEON
	#define FKE_PLATFORM_ENABLE_VECTORINTRINSICS_NEON 0
#endif
#ifndef FKE_PLATFORM_USE_SYSTEM_VSWPRINTF
	#define FKE_PLATFORM_USE_SYSTEM_VSWPRINTF 1
#endif
#ifndef FKE_PLATFORM_COMPILER_DISTINGUISHES_INT_AND_LONG
	#define FKE_PLATFORM_COMPILER_DISTINGUISHES_INT_AND_LONG 0
#endif
#ifdef _MSC_VER
	#define FKE_PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES 1
	#ifndef __clang__
		#pragma deprecated("FKE_PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES")
	#endif
#else
	#define FKE_PLATFORM_COMPILER_HAS_AUTO_RETURN_TYPES 1
#endif
#ifndef FKE_PLATFORM_COMPILER_HAS_GENERIC_KEYWORD
	#define FKE_PLATFORM_COMPILER_HAS_GENERIC_KEYWORD 0
#endif
#ifdef _MSC_VER
	#define FKE_PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS 1
	#ifndef __clang__
		#pragma deprecated("FKE_PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS")
	#endif
#else
	#define FKE_PLATFORM_COMPILER_HAS_DEFAULTED_FUNCTIONS 1
#endif

#ifndef FKE_PLATFORM_COMPILER_HAS_TCHAR_WMAIN
	#define FKE_PLATFORM_COMPILER_HAS_TCHAR_WMAIN 0
#endif
#ifndef FKE_PLATFORM_COMPILER_HAS_DECLTYPE_AUTO
	#define FKE_PLATFORM_COMPILER_HAS_DECLTYPE_AUTO 1
#endif
#ifndef FKE_PLATFORM_COMPILER_HAS_IF_CONSTEXPR
	#define FKE_PLATFORM_COMPILER_HAS_IF_CONSTEXPR 1
#endif

#ifndef FKE_PLATFORM_TCHAR_IS_1_BYTE
	#define FKE_PLATFORM_TCHAR_IS_1_BYTE 0
#endif
#ifndef FKE_PLATFORM_TCHAR_IS_4_BYTES
	#define FKE_PLATFORM_TCHAR_IS_4_BYTES 0
#endif
#ifndef FKE_PLATFORM_WCHAR_IS_4_BYTES
	#define FKE_PLATFORM_WCHAR_IS_4_BYTES 0
#endif
#ifndef FKE_PLATFORM_TCHAR_IS_CHAR16
	#define FKE_PLATFORM_TCHAR_IS_CHAR16 0
#endif

// These is computed, not predefined.
#define FKE_PLATFORM_32BITS	(!FKE_PLATFORM_64BITS)

#ifndef FKE_VARARGS
	/** Functions with variable arguments */
	#define FKE_VARARGS
#endif
#ifndef FKE_CDECL
	/** Standard C function */
	#define FKE_CDECL
#endif
#ifndef FKE_STDCALL
	/** Standard calling convention */
	#define FKE_STDCALL
#endif
#ifndef FKE_FORCEINLINE
	/** Force code to be inline */
	#define FKE_FORCEINLINE
#endif
#ifndef FKE_FORCENOINLINE
	/** Force code to not be inline */
	#define FKE_FORCENOINLINE
#endif
#ifndef FKE_RESTRICT
	/** Indicates that a symbol is not aliased in the current scope. */
	#define FKE_RESTRICT __restrict
#endif

#ifndef FKE_FUNCTION_CHECK_RETURN_START
	/** Wrap a function signature in these (FKE_FUNCTION_CHECK_RETURN_START, FKE_FUNCTION_CHECK_RETURN_END) to warn that callers should not ignore the return value. */
	#define FKE_FUNCTION_CHECK_RETURN_START
#endif
#ifndef FKE_FUNCTION_CHECK_RETURN_END
	/** Wrap a function signature in these (FKE_FUNCTION_CHECK_RETURN_START, FKE_FUNCTION_CHECK_RETURN_END) to warn that callers should not ignore the return value. */
	#define FKE_FUNCTION_CHECK_RETURN_END
#endif

#ifndef FKE_FUNCTION_NO_RETURN_START
	/** Wrap a function signature in these (FKE_FUNCTION_NO_RETURN_START, FKE_FUNCTION_NO_RETURN_END) to indicate that the function never returns. */
	#define FKE_FUNCTION_NO_RETURN_START
#endif
#ifndef FKE_FUNCTION_NO_RETURN_END
	/** Wrap a function signature in these (FKE_FUNCTION_NO_RETURN_START, FKE_FUNCTION_NO_RETURN_END) to indicate that the function never returns. */
	#define FKE_FUNCTION_NO_RETURN_END
#endif

#ifndef FKE_FUNCTION_NON_NULL_RETURN_START
	/** Wrap a function signature in these (FKE_FUNCTION_NON_NULL_RETURN_START, FUNCTION_NON_NULL_RETURN_END) to indicate that the function never returns nullptr. */
	#define FKE_FKE_FUNCTION_NON_NULL_RETURN_START
#endif
#ifndef FUNCTION_NON_NULL_RETURN_END
	/** Wrap a function signature in these (FKE_FUNCTION_NON_NULL_RETURN_START, FUNCTION_NON_NULL_RETURN_END) to indicate that the function never returns nullptr. */
	#define FKE_FUNCTION_NON_NULL_RETURN_END
#endif

#ifndef FKE_ASSUME
	/** Hints compiler that expression is true; generally restricted to comparisons against constants. */
	#define FKE_ASSUME(...)
#endif

/** Branch prediction hints */
#ifndef FKE_LIKELY
	#if ( defined(__clang__) || defined(__GNUC__) ) && (FKE_PLATFORM_UNIX)
		/** Hints compiler that expression is likely to be true, much softer than ASSUME - allows (penalized by worse performance) expression to be false. */
		#define FKE_LIKELY(X) __builtin_expect(!!(X), 1)
	#else
		/** Hints compiler that expression is likely to be true, much softer than ASSUME - allows (penalized by worse performance) expression to be false. */
		#define FKE_LIKELY(X) (X)
	#endif
#endif

#ifndef FKE_UNLIKELY
	#if ( defined(__clang__) || defined(__GNUC__) ) && (FKE_PLATFORM_UNIX)
		/** Hints compiler that expression is unlikely to be true, allows (penalized by worse performance) expression to be true. */
		#define FKE_UNLIKELY(x) __builtin_expect(!!(x), 0)
	#else
		/** Hints compiler that expression is unlikely to be true, allows (penalized by worse performance) expression to be true. */
		#define FKE_UNLIKELY(x) (x)
	#endif
#endif

// Optimization macros (uses __pragma to enable inside a #define).
#ifndef FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
	#define FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
	#define FKE_PRAGMA_ENABLE_OPTIMIZATION_ACTUAL
#endif

#ifndef FKE_DISABLE_FUNCTION_OPTIMIZATION
	/** Disable optimization of a specific function. */
	#define FKE_DISABLE_FUNCTION_OPTIMIZATION
#endif

/** Enable/disable optimizations for a specific function to improve build times. */
#define FKE_BEGIN_FUNCTION_BUILD_OPTIMIZATION FKE_PRAGMA_DISABLE_OPTIMIZATION
/** Enable/disable optimizations for a specific function to improve build times. */
#define FKE_END_FUNCTION_BUILD_OPTIMIZATION FKE_PRAGMA_ENABLE_OPTIMIZATION

#ifndef FKE_FORCEINLINE_DEBUGGABLE_ACTUAL
	#define FKE_FORCEINLINE_DEBUGGABLE_ACTUAL inline
#endif

#ifndef FKE_DECLARE_UINT64
	/** Define a 64 bit immediate int. */
	#define FKE_DECLARE_UINT64(x) x##ULL
#endif

#ifndef FKE_TYPENAME_OUTSIDE_TEMPLATE
	/** Backwater of the spec.All compilers support this except microsoft, and they will soon. */
	#define FKE_TYPENAME_OUTSIDE_TEMPLATE	typename
#endif

#ifndef FKE_ABSTRACT
	#define FKE_ABSTRACT
#endif
#ifndef FKE_CONSTEXPR
	#define FKE_CONSTEXPR constexpr
#endif

// String constants
#ifndef FKE_LINE_TERMINATOR
	#define FKE_LINE_TERMINATOR TEXT("\n")
#endif
#ifndef FKE_LINE_TERMINATOR_ANSI
	#define FKE_LINE_TERMINATOR_ANSI "\n"
#endif

// Alignment.
#ifndef FKE_GCC_PACK
	#define FKE_GCC_PACK(n)
#endif
#ifndef FKE_GCC_ALIGN
	#define FKE_GCC_ALIGN(n)
#endif
#ifndef FKE_MS_ALIGN
	#define FKE_MS_ALIGN(N)
#endif

// MSVC pragmas - used so other platforms can remove them easily (by not defining this).
#ifndef FKE_MSVC_PRAGMA
	#define FKE_MSVC_PRAGMA(...)
#endif


// Inlining.
#ifndef FKE_PRAGMA_DISABLE_INLINING
	#define FKE_PRAGMA_DISABLE_INLINING
	#define FKE_PRAGMA_ENABLE_INLINING
#endif

// Cache control.
#ifndef FKE_FLUSH_CACHE_LINE
	#define FKE_FLUSH_CACHE_LINE(x)
#endif

// Prefetch
#ifndef FKE_PLATFORM_CACHE_LINE_SIZE
	#define FKE_PLATFORM_CACHE_LINE_SIZE 64
#endif

#if defined(__clang__)
	#define FKE_PRETTY_FUNCTION __PRETTY_FUNCTION__
	#define FKE_SUPPORT_COMPILE_TIME_TYPE_INFO 1
#elif defined(__GNUC__) && !defined(__clang__)
	#define FKE_PRETTY_FUNCTION __PRETTY_FUNCTION__
	#define FKE_SUPPORT_COMPILE_TIME_TYPE_INFO 1
#elif defined(_MSC_VER)
	#define FKE_PRETTY_FUNCTION __FUNCSIG__
	#define FKE_SUPPORT_COMPILE_TIME_TYPE_INFO 1
#else
	#define FKE_SUPPORT_COMPILE_TIME_TYPE_INFO 0
#endif

// Compile-time warnings and errors. Use these as "#pragma COMPILER_WARNING("XYZ")". GCC does not expand macro parameters to _Pragma, so we can't wrap the #pragma part.
#ifdef _MSC_VER
	#define FKE_MSC_FORMAT_DIAGNOSTIC_HELPER_2(x) #x
	#define FKE_MSC_FORMAT_DIAGNOSTIC_HELPER(x) FKE_MSC_FORMAT_DIAGNOSTIC_HELPER_2(x)
	#define FKE_COMPILE_WARNING(x) __pragma(message(__FILE__ "(" FKE_MSC_FORMAT_DIAGNOSTIC_HELPER(__LINE__) "): warning: " x))
	#define FKE_COMPILE_ERROR(x) __pragma(message(__FILE__ "(" FKE_MSC_FORMAT_DIAGNOSTIC_HELPER(__LINE__) "): error: " x))
#else
	#define FKE_GCC_DIAGNOSTIC_HELPER(x) _Pragma(#X)
	#define FKE_COMPILE_WARNING(x) FKE_GCC_DIAGNOSTIC_HELPER(GCC warning x)
	#define FKE_COMPILE_ERROR(x) FKE_GCC_DIAGNOSTIC_HELPER(GCC error x)
#endif

#define FKE_EXIT(code) exit(code)

// Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable.
#ifndef FKE_PLATFORM_CODE_SECTION
	#define FKE_PLATFORM_CODE_SECTION(name)
#endif

// These have to be forced inline on some OSes so the dynamic loader will not
// resolve to our allocators for the system libraries.
#ifndef FKE_OPERATOR_NEW_INLINE
	#define FKE_OPERATOR_NEW_INLINE FKE_FORCEINLINE
#endif

#ifndef FKE_OPERATOR_NEW_THROW_SPEC
	#define FKE_OPERATOR_NEW_THROW_SPEC
#endif
#ifndef FKE_OPERATOR_DELETE_THROW_SPEC
	#define FKE_OPERATOR_DELETE_THROW_SPEC
#endif
#ifndef FKE_OPERATOR_NEW_NOTHROW_SPEC
	#define FKE_OPERATOR_NEW_NOTHROW_SPEC throw()
#endif
#ifndef FKE_OPERATOR_DELETE_NOTHROW_SPEC
	#define FKE_OPERATOR_DELETE_NOTHROW_SPEC throw()
#endif

#ifdef __cpp_variable_templates
	#define FKE_HAS_VARIABLE_TEMPLATES
#endif

// DLL export and import definitions
#ifndef FKE_DLLEXPORT
	#define FKE_DLLEXPORT
	#define FKE_DLLIMPORT
#endif

#ifndef FKE_DLLEXPORT_VTABLE
	#define FKE_DLLEXPORT_VTABLE
	#define FKE_DLLIMPORT_VTABLE
#endif

// int types.
// Can also be found in generic_platform_types.
#include <cstdint>

/** ANSI character. 8-Bit fixed-width representation of 7-bit character. */
typedef fkengine::fkecore::platform_types::ansichar_t ansichar_t;
/** Wide character. ?-Bit fixed-width representation of the platform's natural wide character set. Could be different sizes on different platforms. */
typedef fkengine::fkecore::platform_types::widechar_t widechar_t;

#ifndef __cpp_char8_t
/** 8-Bit character. */
typedef fkengine::fkecore::platform_types::char8_t char8_t;
#endif
#ifndef __cpp_unicode_characters
/** 16-Bit character. */
typedef fkengine::fkecore::platform_types::char16_t char16_t;
/** 32-Bit character. */
typedef fkengine::fkecore::platform_types::char32_t char32_t;
#endif

/** Switchable character. Can be ansichar_t or widechar_t depending on the build settings. */
typedef fkengine::fkecore::platform_types::char_t char_t;
/** An 8-bit character containing a UTF8 (Unicode, 8-bit, variable-width) code unit. */
typedef char8_t	utf8char_t;
/** A 16-bit character containing a UCS2 (Unicode, 16-bit, fixed-width) code unit, used for compatibility with 'Windows TCHAR' across multiple platforms. */
typedef char16_t ucs2char_t;
/** A 16-bit character containing a UTF16 (Unicode, 16-bit, variable-width) code unit. */
typedef char16_t utf16char_t;
/** A 32-bit character containing a UTF32 (Unicode, 32-bit, fixed-width) code unit. */
typedef char32_t utf32char_t;

/** An unsigned integer the same size_t as a pointer. */
typedef fkengine::fkecore::platform_types::uptrint_t uptrint_t;
/** A signed integer the same size_t as a pointer. */
typedef fkengine::fkecore::platform_types::ptrint_t ptrint_t;
/** An unsigned integer the same size_t as a pointer, the same as uptrint_t. */
typedef fkengine::fkecore::platform_types::size_t size_t;
/** An integer the same size_t as a pointer, the same as ptrint_t. */
typedef fkengine::fkecore::platform_types::ssize_t ssize_t;

/** The type of the NULL constant. */
typedef fkengine::fkecore::platform_types::typeofnull_t typeofnull_t;
/** The type of the C++ nullptr keyword. */
typedef fkengine::fkecore::platform_types::typeofnullptr_t typeofnullptr_t;

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		namespace type_tests
		{
			template<typename, typename> struct are_types_equal;

			template <typename A, typename B>
			struct are_types_equal
			{
				static FKE_CONSTEXPR bool value = false;
			};

			template <typename T>
			struct are_types_equal<T, T>
			{
				static FKE_CONSTEXPR bool value = true;
			};

			static_assert(!FKE_PLATFORM_TCHAR_IS_4_BYTES || sizeof(char_t) == 4, "char_t size_t must be 4 bytes.");
			//static_assert(FKE_PLATFORM_TCHAR_IS_4_BYTES || sizeof(char_t) == 2, "char_t size_t must be 2 bytes.");

			static_assert(!FKE_PLATFORM_WCHAR_IS_4_BYTES || sizeof(wchar_t) == 4, "wchar_t size_t must be 4 bytes.");
			static_assert(FKE_PLATFORM_WCHAR_IS_4_BYTES || sizeof(wchar_t) == 2, "wchar_t size_t must be 2 bytes.");

			static_assert(FKE_PLATFORM_32BITS || FKE_PLATFORM_64BITS, "Type tests pointer size_t failed.");
			static_assert(FKE_PLATFORM_32BITS != FKE_PLATFORM_64BITS, "Type tests pointer exclusive failed.");
			static_assert(!FKE_PLATFORM_64BITS || sizeof(void*) == 8, "Pointer size_t is 64bit, but pointers are short.");
			static_assert(FKE_PLATFORM_64BITS || sizeof(void*) == 4, "Pointer size_t is 32bit, but pointers are long.");

			static_assert(char(-1) < char(0), "Unsigned char type test failed.");

			static_assert((!are_types_equal<ansichar_t, widechar_t>::value), "ansichar_t and widechar_t should be different types.");
			static_assert((!are_types_equal<ansichar_t, ucs2char_t>::value), "ansichar_t and char16_t should be different types.");
			static_assert((!are_types_equal<widechar_t, ucs2char_t>::value), "widechar_t and char16_t should be different types.");
			static_assert((are_types_equal<char_t, ansichar_t>::value == true || are_types_equal<char_t, widechar_t>::value == true), "char_t should either be ansichar_t or widechar_t.");

			static_assert(sizeof(uint8_t) == 1, "uint8_t type size_t test failed.");
			static_assert(int32_t(uint8_t(-1)) == 0xFF, "uint8_t type sign test failed.");

			static_assert(sizeof(uint16_t) == 2, "uint16_t type size_t test failed.");
			static_assert(int32_t(uint16_t(-1)) == 0xFFFF, "uint16_t type sign test failed.");

			static_assert(sizeof(uint32_t) == 4, "uint32_t type size_t test failed.");
			static_assert(int64_t(uint32_t(-1)) == int64_t(0xFFFFFFFF), "uint32_t type sign test failed.");

			static_assert(sizeof(uint64_t) == 8, "uint64_t type size_t test failed.");
			static_assert(uint64_t(-1) > uint64_t(0), "uint64_t type sign test failed.");


			static_assert(sizeof(int8_t) == 1, "int8_t type size_t test failed.");
			static_assert(int32_t(int8_t(-1)) == -1, "int8_t type sign test failed.");

			static_assert(sizeof(int16_t) == 2, "int16_t type size_t test failed.");
			static_assert(int32_t(int16_t(-1)) == -1, "int16_t type sign test failed.");

			static_assert(sizeof(int32_t) == 4, "int32_t type size_t test failed.");
			static_assert(int64_t(int32_t(-1)) == int64_t(-1), "int32_t type sign test failed.");

			static_assert(sizeof(int64_t) == 8, "int64_t type size_t test failed.");
			static_assert(int64_t(-1) < int64_t(0), "int64_t type sign test failed.");

			static_assert(sizeof(ansichar_t) == 1, "ansichar_t type size_t test failed.");
			static_assert(int32_t(ansichar_t(-1)) == -1, "ansichar_t type sign test failed.");

			static_assert(sizeof(widechar_t) == 2 || sizeof(widechar_t) == 4, "widechar_t type size_t test failed.");

			static_assert(sizeof(ucs2char_t) == 2, "ucs2char_t type size_t test failed.");

			static_assert(sizeof(ptrint_t) == sizeof(void*), "ptrint_t type size_t test failed.");
			static_assert(ptrint_t(-1) < ptrint_t(0), "ptrint_t type sign test failed.");

			static_assert(sizeof(uptrint_t) == sizeof(void*), "uptrint_t type size_t test failed.");
			static_assert(uptrint_t(-1) > uptrint_t(0), "uptrint_t type sign test failed.");

			static_assert(sizeof(size_t) == sizeof(void*), "size_t type size_t test failed.");
			static_assert(size_t(-1) > size_t(0), "size_t type sign test failed.");
		}
	}
}

// Include the platform-specific compiler setup.
#include FKE_COMPILED_PLATFORM_HEADER(platform_compiler_setup.h)

#ifndef FKE_ANSI_TEXT
	#define FKE_ANSI_TEXT(x) x
#endif

#ifndef FKE_WIDE_TEXT
	#define FKE_WIDE_TEXT(x) L ## x
#endif

#ifndef FKE_TEXT
	#if FKE_UNICODE
		#define FKE_TEXT(x) FKE_WIDE_TEXT(x)
	#else
		#define FKE_TEXT(x) FKE_ANSI_TEXT(x)
	#endif
#endif

#ifndef TEXT
	#if FKE_UNICODE
		#define TEXT(x) FKE_WIDE_TEXT(x)
	#else
		#define TEXT(x) FKE_ANSI_TEXT(x)
	#endif
#endif