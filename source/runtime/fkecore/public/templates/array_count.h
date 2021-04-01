// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
#ifdef __clang__
	template <typename T>
	auto array_count_helper(T& t) -> typename TEnableIf<__is_array(T), char(&)[sizeof(t) / sizeof(t[0]) + 1]>::Type;
#else
	template <typename T, uint32_t N>
	char(&array_count_helper(const T(&)[N]))[N + 1];
#endif
}

#define FKE_ARRAY_COUNT(array) (sizeof(fkengine::array_count_helper(array)) - 1)