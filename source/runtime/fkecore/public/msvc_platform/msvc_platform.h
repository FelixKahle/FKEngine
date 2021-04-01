// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#if _MSC_FULL_VER >= 191125507 && defined(__cpp_if_constexpr)
	/** 1 if the platform compiler has the if constexpr feature, 0 otherwise. */
	#define FKE_PLATFORM_COMPILER_HAS_IF_CONSTEXPR 1
#else
	/** 1 if the platform compiler has the if constexpr feature, 0 otherwise. */
	#define FKE_PLATFORM_COMPILER_HAS_IF_CONSTEXPR 0
#endif