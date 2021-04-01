// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#if defined(__clang__)
	#ifdef _WIN64
		#ifndef FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
				#define FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING \
				_Pragma("pack(push)") \
				_Pragma("pack(16)")
		#endif
	#else
		#ifndef FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
			#define FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING \
					_Pragma("pack(push)") \
					_Pragma("pack(8)")
		#endif
	#endif

	#ifndef FKE_PRAGMA_POP_PLATFORM_DEFAULT_PACKING
		#define FKE_PRAGMA_POP_PLATFORM_DEFAULT_PACKING \
				_Pragma("pack(pop)")
	#endif

	#include "ClangPlatform/ClangPlatformCompilerPreSetup.h"

	#ifndef FKE_THIRD_PARTY_INCLUDES_START
		#define FKE_THIRD_PARTY_INCLUDES_START \
				FKE_PRAGMA_DISABLE_REORDER_WARNINGS \
				FKE_PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS \
				FKE_PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				FKE_PRAGMA_DISABLE_DEPRECATION_WARNINGS \
				FKE_PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS \
				FKE_PRAGMA_DISABLE_MISSING_BRACES_WARNINGS
	#endif

	#ifndef FKE_THIRD_PARTY_INCLUDES_END
		#define FKE_THIRD_PARTY_INCLUDES_END \
				FKE_PRAGMA_DISABLE_MISSING_BRACES_WARNINGS \
				FKE_PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS \
				FKE_PRAGMA_ENABLE_DEPRECATION_WARNINGS \
				FKE_PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				FKE_PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS \
				FKE_PRAGMA_ENABLE_REORDER_WARNINGS
	#endif
#else
	#ifndef FKE_DISABLE_DEPRECATION
		#define FKE_PRAGMA_DISABLE_DEPRECATION_WARNINGS \
				__pragma (warning(push)) \
				__pragma (warning(disable: 4995)) /* 'function': name was marked as #pragma deprecated */ \
				__pragma (warning(disable: 4996)) /* The compiler encountered a deprecated declaration. */

		#define FKE_PRAGMA_ENABLE_DEPRECATION_WARNINGS \
				__pragma (warning(pop))
	#endif

	#ifndef FKE_PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS
		#define FKE_PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS \
				__pragma (warning(push)) \
				__pragma (warning(disable: 4456)) /* declaration of 'LocalVariable' hides previous local declaration */ \
				__pragma (warning(disable: 4457)) /* declaration of 'LocalVariable' hides function parameter */ \
				__pragma (warning(disable: 4458)) /* declaration of 'LocalVariable' hides class member */ \
				__pragma (warning(disable: 4459)) /* declaration of 'LocalVariable' hides global declaration */ \
				__pragma (warning(disable: 6244)) /* local declaration of <variable> hides previous declaration at <line> of <file> */
	#endif

	#ifndef FKE_PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS
		#define FKE_PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS \
				__pragma(warning(pop))
	#endif

	#ifndef FKE_PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS
		#define FKE_PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				__pragma(warning(push)) \
				__pragma(warning(disable: 4668)) /* 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives' */
	#endif

	#ifndef FKE_PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS
		#define FKE_PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				__pragma(warning(pop))
	#endif

	#ifndef FKE_PRAGMA_DISABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS
		#define FKE_PRAGMA_DISABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
				__pragma(warning(push)) \
				__pragma(warning(disable: 4265)) /* class' : class has virtual functions, but destructor is not virtual */
	#endif

	#ifndef FKE_PRAGMA_ENABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS
		#define FKE_PRAGMA_ENABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
				__pragma(warning(pop))
	#endif

	#ifndef FKE_PRAGMA_DISABLE_REORDER_WARNINGS
		#define FKE_PRAGMA_DISABLE_REORDER_WARNINGS \
				__pragma(warning(push)) \
				__pragma(warning(disable: 5038)) /* data member 'member1' will be initialized after data member 'member2' data member 'member' will be initialized after base class 'base_class' */
	#endif

	#ifndef FKE_PRAGMA_ENABLE_REORDER_WARNINGS
		#define FKE_PRAGMA_ENABLE_REORDER_WARNINGS \
				__pragma(warning(pop))
	#endif

	#ifndef FKE_PRAGMA_POP
		#define FKE_PRAGMA_POP \
				__pragma(warning(pop))
	#endif

	#ifdef _WIN64
		#ifndef FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
			#define FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING \
					__pragma(pack(push)) \
					__pragma(pack(16))
		#endif
	#else
		#ifndef FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
			#define FKE_PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING \
					__pragma(pack(push)) \
					__pragma(pack(8))
		#endif
	#endif

	#ifndef FKE_PRAGMA_POP_PLATFORM_DEFAULT_PACKING
		#define FKE_PRAGMA_POP_PLATFORM_DEFAULT_PACKING \
				__pragma(pack(pop))
	#endif

	#ifndef FKE_THIRD_PARTY_INCLUDES_START
		#define FKE_THIRD_PARTY_INCLUDES_START \
				__pragma(warning(push)) \
				__pragma(warning(disable: 4510))  /* '<class>': default constructor could not be generated. */ \
				__pragma(warning(disable: 4610))  /* object '<class>' can never be instantiated - user-defined constructor required. */ \
				__pragma(warning(disable: 4800))  /* Implicit conversion from '<type>' to bool. Possible information loss. */ \
				__pragma(warning(disable: 4946))  /* reinterpret_cast used between related classes: '<class1>' and '<class1>' */ \
				__pragma(warning(disable: 4996))  /* '<obj>' was declared deprecated. */ \
				__pragma(warning(disable: 6011))  /* Dereferencing NULL pointer '<ptr>'. */ \
				__pragma(warning(disable: 6101))  /* Returning uninitialized memory '<expr>'.  A successful path through the function does not set the named _Out_ parameter. */ \
				__pragma(warning(disable: 6287))  /* Redundant code:  the left and right sub-expressions are identical. */ \
				__pragma(warning(disable: 6308))  /* 'realloc' might return null pointer: assigning null pointer to 'X', which is passed as an argument to 'realloc', will cause the original memory block to be leaked. */ \
				__pragma(warning(disable: 6326))  /* Potential comparison of a constant with another constant. */ \
				__pragma(warning(disable: 6340))  /* Mismatch on sign: Incorrect type passed as parameter in call to function. */ \
				__pragma(warning(disable: 6385))  /* Reading invalid data from '<ptr>':  the readable size_t is '<num1>' bytes, but '<num2>' bytes may be read. */ \
				__pragma(warning(disable: 6386))  /* Buffer overrun while writing to '<ptr>':  the writable size_t is '<num1>' bytes, but '<num2>' bytes might be written. */ \
				__pragma(warning(disable: 28182)) /* Dereferencing NULL pointer. '<ptr1>' contains the same NULL value as '<ptr2>' did. */ \
				__pragma(warning(disable: 28251)) /* Inconsistent annotation for '<func>': this instance has no annotations. */ \
				__pragma(warning(disable: 28252)) /* Inconsistent annotation for '<func>': return/function has '<annotation>' on the prior instance. */ \
				__pragma(warning(disable: 28253)) /* Inconsistent annotation for '<func>': _Param_(<num>) has '<annotation>' on the prior instance. */ \
				__pragma(warning(disable: 28301)) /* No annotations for first declaration of '<func>'. */ \
				FKE_PRAGMA_DISABLE_REORDER_WARNINGS \
				FKE_PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				FKE_PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS \
				FKE_PRAGMA_DISABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
				FKE_PRAGMA_DISABLE_DEPRECATION_WARNINGS
	#endif

	#ifndef FKE_THIRD_PARTY_INCLUDES_END
		#define FKE_THIRD_PARTY_INCLUDES_END \
				FKE_PRAGMA_ENABLE_DEPRECATION_WARNINGS \
				FKE_PRAGMA_ENABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
				FKE_PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS \
				FKE_PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS \
				FKE_PRAGMA_ENABLE_REORDER_WARNINGS \
				__pragma(warning(pop))
	#endif

	#define FKE_EMIT_CUSTOM_WARNING_AT_LINE(Line, Warning) \
			__pragma(message(FKE_WARNING_LOCATION(Line) ": warning C4996: " Warning))
#endif