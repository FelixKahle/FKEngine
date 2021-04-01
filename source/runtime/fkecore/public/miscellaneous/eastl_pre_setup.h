// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** Overrides the operator new for the EASTL library. */
#define FKE_EASTL_OPERATOR_NEW_OVERRIDE \
		void* operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) \
		{ \
			return new uint8_t[size]; \
		} \
		void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) \
		{ \
			return new uint8_t[size]; \
		}
