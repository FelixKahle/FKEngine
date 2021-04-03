// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		template <typename t> struct is_character { enum { value = false }; };
		template <> struct is_character<float> { enum { value = false }; };
		template <> struct is_character<double> { enum { value = false }; };
		template <> struct is_character<long double> { enum { value = false }; };
		template <> struct is_character<uint8_t> { enum { value = true }; };
		template <> struct is_character<uint16_t> { enum { value = true }; };
		template <> struct is_character<uint32_t> { enum { value = true }; };
		template <> struct is_character<uint64_t> { enum { value = true }; };
		template <> struct is_character<int8_t> { enum { value = true }; };
		template <> struct is_character<int16_t> { enum { value = true }; };
		template <> struct is_character<int32_t> { enum { value = true }; };
		template <> struct is_character<int64_t> { enum { value = true }; };
		template <> struct is_character<bool> { enum { value = false }; };
		template <> struct is_character<widechar_t> { enum { value = true }; };
		template <> struct is_character<ansichar_t> { enum { value = true }; };

		template <typename t> struct is_character<const t> { enum { value = is_character<t>::value }; };
		template <typename t> struct is_character<volatile t> { enum { value = is_character<t>::value }; };
		template <typename t> struct is_character<const volatile t> { enum { value = is_character<t>::value }; };
	}
}