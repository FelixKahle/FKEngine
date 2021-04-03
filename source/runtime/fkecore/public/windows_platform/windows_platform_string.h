// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "generic_platform/microsoft_platform_string.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{

		struct windows_platform_string : public microsoft_platform_string
		{
			FKE_STATIC_STRUCT(windows_platform_string)
		};

		typedef windows_platform_string platform_string;
	}
}

#if FKE_PLATFORM_64BITS
	// size_t format specifier
	#define FKE_SIZE_FMT "I64u"
	// size_t format specifier for lowercase hexadecimal output
	#define FKE_SIZE_x_FMT "I64x"
	// size_t format specifier for uppercase hexadecimal output
	#define FKE_SIZE_X_FMT "I64X"

	// ssize_t format specifier
	#define FKE_SSIZE_FMT "I64d"
	// ssize_t format specifier for lowercase hexadecimal output
	#define FKE_SSIZE_x_FMT "I64x"
	// ssize_t format specifier for uppercase hexadecimal output
	#define FKE_SSIZE_X_FMT "I64X"

	// ptrint_t format specifier for decimal output
	#define FKE_PTRINT_FMT "lld"
	// ptrint_t format specifier for lowercase hexadecimal output
	#define FKE_PTRINT_x_FMT "llx"
	// ptrint_t format specifier for uppercase hexadecimal output
	#define FKE_PTRINT_X_FMT "llX"

	// uptrint_t format specifier for decimal output
	#define FKE_UPTRINT_FMT "llu"
	// uptrint_t format specifier for lowercase hexadecimal output
	#define FKE_UPTRINT_x_FMT "llx"
	// uptrint_t format specifier for uppercase hexadecimal output
	#define FKE_UPTRINT_X_FMT "llX"
#else
	// size_t format specifier
	#define FKE_SIZE_FMT "lu"
	// size_t format specifier for lowercase hexadecimal output
	#define FKE_SIZE_x_FMT "lx"
	// size_t format specifier for uppercase hexadecimal output
	#define FKE_SIZE_X_FMT "lX"

	// ssize_t format specifier
	#define FKE_SSIZE_FMT "ld"
	// ssize_t format specifier for lowercase hexadecimal output
	#define FKE_SSIZE_x_FMT "lx"
	// ssize_t format specifier for uppercase hexadecimal output
	#define FKE_SSIZE_X_FMT "lX"

	// ptrint_t format specifier for decimal output
	#define FKE_PTRINT_FMT "d"
	// ptrint_t format specifier for lowercase hexadecimal output
	#define FKE_PTRINT_x_FMT "x"
	// ptrint_t format specifier for uppercase hexadecimal output
	#define FKE_PTRINT_X_FMT "X"

	// uptrint_t format specifier for decimal output
	#define FKE_UPTRINT_FMT "u"
	// uptrint_t format specifier for lowercase hexadecimal output
	#define FKE_UPTRINT_x_FMT "x"
	// uptrint_t format specifier for uppercase hexadecimal output
	#define FKE_UPTRINT_X_FMT "X"
#endif

// int64_t format specifier for decimal output
#define FKE_INT64_FMT "lld"
// int64_t format specifier for lowercase hexadecimal output
#define FKE_INT64_x_FMT "llx"
// int64_t format specifier for uppercase hexadecimal output
#define FKE_INT64_X_FMT "llX"

// uint64_t format specifier for decimal output
#define FKE_UINT64_FMT "llu"
// uint64_t format specifier for lowercase hexadecimal output
#define FKE_UINT64_x_FMT "llx"
// uint64_t format specifier for uppercase hexadecimal output
#define FKE_UINT64_X_FMT "llX"