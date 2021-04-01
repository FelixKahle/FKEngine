// Copyright 2021 Felix Kahle.All rights reserved.

#pragma once

#include "miscellaneous/build.h"

// Check if FKE_UNICODE has been defined by the build system of the FKEngine.
#if !defined(FKE_UNICODE)
	#error FKE_UNICODE was not defined by the build system of the FKEngine.
#endif

/** The namespace of the FKEngine. */
namespace fkengine
{
	/**
	 * Utility for automatically setting up the pointer-sized integer type.
	 *
	 * @template param bits_8 - 8-Bit integer.
	 * @template param bits_16 - 16-Bit integer.
	 * @template param bits_32 - 32-Bit integer.
	 * @template param bits_64 - 64-Bit integer.
	 * @template param PointerSize - The size_t of a pointer.
	 *
	 * @template return Value - The choosen pointer-sized integer type.
	 */
	template<typename bits_8, typename bits_16, typename bits_32, typename bits_64, int pointer_size>
	struct select_int_pointer_type
	{
		// If the partial specializations fail this becomes an error because there is not the Value typedef.
	};

	/**
	 * Utility for automatically setting up the pointer-sized integer type.
	 *
	 * @template param bits_8 - 8-Bit integer.
	 * @template param bits_16 - 16-Bit integer.
	 * @template param bits_32 - 32-Bit integer.
	 * @template param bits_64 - 64-Bit integer.
	 * @template param PointerSize - The size_t of a pointer.
	 *
	 * @template return Value - The choosen pointer-sized integer type.
	 */
	template<typename bits_8, typename bits_16, typename bits_32, typename bits_64>
	struct select_int_pointer_type<bits_8, bits_16, bits_32, bits_64, 8>
	{
		/** The type of the choosen integer pointer. */
		typedef bits_64 type;
	};

	/**
	 * Utility for automatically setting up the pointer-sized integer type.
	 *
	 * @template param bits_8 - 8-Bit integer.
	 * @template param bits_16 - 16-Bit integer.
	 * @template param bits_32 - 32-Bit integer.
	 * @template param bits_64 - 64-Bit integer.
	 * @template param PointerSize - The size_t of a pointer.
	 *
	 * @template return Value - The choosen pointer-sized integer type.
	 */
	template<typename bits_8, typename bits_16, typename bits_32, typename bits_64>
	struct select_int_pointer_type<bits_8, bits_16, bits_32, bits_64, 4>
	{
		/** The type of the choosen integer pointer. */
		typedef bits_32 type;
	};

	/**
	 * Utility for automatically setting up the pointer-sized integer type.
	 *
	 * @template param bits_8 - 8-Bit integer.
	 * @template param bits_16 - 16-Bit integer.
	 * @template param bits_32 - 32-Bit integer.
	 * @template param bits_64 - 64-Bit integer.
	 * @template param PointerSize - The size_t of a pointer.
	 *
	 * @template return Value - The choosen pointer-sized integer type.
	 */
	template<typename bits_8, typename bits_16, typename bits_32, typename bits_64>
	struct select_int_pointer_type<bits_8, bits_16, bits_32, bits_64, 2>
	{
		/** The type of the choosen integer pointer. */
		typedef bits_16 type;
	};

	/**
	 * Utility for automatically setting up the pointer-sized integer type.
	 *
	 * @template param bits_8 - 8-Bit integer.
	 * @template param bits_16 - 16-Bit integer.
	 * @template param bits_32 - 32-Bit integer.
	 * @template param bits_64 - 64-Bit integer.
	 * @template param PointerSize - The size_t of a pointer.
	 *
	 * @template return Value - The choosen pointer-sized integer type.
	 */
	template<typename bits_8, typename bits_16, typename bits_32, typename bits_64>
	struct select_int_pointer_type<bits_8, bits_16, bits_32, bits_64, 1>
	{
		/** The type of the choosen integer pointer. */
		typedef bits_8 type;
	};

	/** Generic types for almost all compilers and platforms. */
	struct generic_platform_types
	{
		generic_platform_types(generic_platform_types&&) = delete;
		generic_platform_types(const generic_platform_types&) = delete;
		generic_platform_types& operator=(const generic_platform_types&) = delete;
		generic_platform_types& operator=(generic_platform_types&&) = delete;
	protected:

		generic_platform_types() {}

	public:

		/** Unsigned 8-Bit integer. */
		typedef unsigned char uint8_t;
		/** Unsigned 16-Bit integer. */
		typedef unsigned short int uint16_t;
		/** Unsigned 32-Bit integer. */
		typedef unsigned int uint32_t;
		/** Unsigned 64-Bit integer. */
		typedef unsigned long long uint64_t;

		/** Signed 8-Bit integer. */
		typedef	signed char int8_t;
		/** Signed 16-Bit integer. */
		typedef signed short int int16_t;
		/** Signed 32-Bit integer. */
		typedef signed int int32_t;
		/** Signed 64-Bit integer. */
		typedef signed long long int64_t;

		/** ANSI character. 8-Bit fixed-width representation of 7-bit character. */
		typedef char ansichar_t;
		/** Wide character. ?-Bit fixed-width representation of the platform's natural wide character set. Could be different sizes on different platforms. */
		typedef wchar_t widechar_t;
#ifndef __cpp_char8_t
		/** 8-Bit character. */
		typedef uint8_t char8_t;
#endif
#ifndef __cpp_unicode_characters
		/** 16-Bit character. */
		typedef uint16_t char16_t;
		/** 32-Bit character. */
		typedef uint32_t char32_t;
#endif

#if FKE_UNICODE
		/** Switchable character. Can be ansichar_t or widechar_t depending on the build settings. */
		typedef widechar_t char_t;
#else
		/** Switchable character. Can be AnsiChar or WideChar depending on the build settings. */
		typedef ansichar_t char_t;
#endif

		/** Unsigned int in the same size as a pointer. */
		typedef select_int_pointer_type<uint8_t, uint16_t, uint32_t, uint64_t, sizeof(void*)>::type uptrint_t;
		/** Signed int in the same size as a pointer. */
		typedef select_int_pointer_type<int8_t, int16_t, int32_t, int64_t, sizeof(void*)>::type ptrint_t;

		/** Unsigned int in the same size_t as a pointer. */
		typedef uptrint_t size_t;
		/** Signed int in the same size_t as a pointer. */
		typedef ptrint_t ssize_t;

		/** The type of NULL. */
		typedef int32_t typeofnull_t;
		/** The type of nullptr. */
		typedef decltype(nullptr) typeofnullptr_t;
	};
}