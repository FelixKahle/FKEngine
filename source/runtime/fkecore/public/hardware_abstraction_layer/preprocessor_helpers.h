// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Turns an preprocessor token into a real string (see FKE_BUILD_SYSTEM_COMPILED_PLATFORM)
#define FKE_PREPROCESSOR_TO_STRING(X) FKE_PREPROCESSOR_TO_STRING_INNER(X)
#define FKE_PREPROCESSOR_TO_STRING_INNER(X) #X

// Concatenates two preprocessor tokens, performing macro expansion on them first
#define FKE_PREPROCESSOR_JOIN(X, Y) FKE_PREPROCESSOR_JOIN_INNER(X, Y)
#define FKE_PREPROCESSOR_JOIN_INNER(X, Y) X##Y

// Concatenates the first two preprocessor tokens of a variadic list, after performing macro expansion on them
#define FKE_PREPROCESSOR_JOIN_FIRST(X, ...) FKE_PREPROCESSOR_JOIN_FIRST_INNER(X, __VA_ARGS__)
#define FKE_PREPROCESSOR_JOIN_FIRST_INNER(X, ...) X##__VA_ARGS__

// Expands to the second argument or the third argument if the first argument is 1 or 0 respectively
#define FKE_PREPROCESSOR_IF(Cond, X, Y) FKE_PREPROCESSOR_JOIN(FKE_PREPROCESSOR_IF_INNER_, Cond)(X, Y)
#define FKE_PREPROCESSOR_IF_INNER_1(X, Y) X
#define FKE_PREPROCESSOR_IF_INNER_0(X, Y) Y

// Expands to the parameter list of the macro - used for when you need to pass a comma-separated identifier to another macro as a single parameter
#define FKE_PREPROCESSOR_COMMA_SEPARATED(First, Second, ...) First, Second, ##__VA_ARGS__

// Expands to nothing - used as a placeholder
#define FKE_PREPROCESSOR_NOTHING

// Removes a single layer of parentheses from a macro argument if they are present - used to allow
// brackets to be optionally added when the argument contains commas, e.g.:
//
// #define DEFINE_VARIABLE(Type, Name) PREPROCESSOR_REMOVE_OPTIONAL_PARENS(Type) Name;
//
// DEFINE_VARIABLE(int, IntVar)                  // expands to: int IntVar;
// DEFINE_VARIABLE((TPair<int, float>), PairVar) // expands to: TPair<int, float> PairVar;
#define FKE_PREPROCESSOR_REMOVE_OPTIONAL_PARENS(...) FKE_PREPROCESSOR_JOIN_FIRST(FKE_PREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPL,PREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPL __VA_ARGS__)
#define FKE_PREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPL(...) FKE_PREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPL __VA_ARGS__
#define FKE_PREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPLPREPROCESSOR_REMOVE_OPTIONAL_PARENS_IMPL

#ifndef FKE_BUILD_SYSTEM_COMPILED_PLATFORM
	#error FKE_BUILD_SYSTEM_COMPILED_PLATFORM has not been defined by the FKEngine build system
#endif


// setup standardized way of including platform headers from the "uber-platform" headers like PlatformFile.h
#ifdef FKE_OVERRIDE_PLATFORM_HEADER_NAME
	// allow for an override, so compiled platforms Win64 and Win32 will both include Windows
	#define FKE_PLATFORM_HEADER_NAME OVERRIDE_PLATFORM_HEADER_NAME
#else
	// otherwise use the compiled platform name
	#define FKE_PLATFORM_HEADER_NAME FKE_BUILD_SYSTEM_COMPILED_PLATFORM
#endif

#ifndef FKE_PLATFORM_IS_EXTENSION
	#define FKE_PLATFORM_IS_EXTENSION 0
#endif

#if FKE_PLATFORM_IS_EXTENSION
	// Creates a string that can be used to include a header in the platform extension form "PlatformHeader.h", not like below form
	#define FKE_COMPILED_PLATFORM_HEADER(Suffix) FKE_PREPROCESSOR_TO_STRING(FKE_PREPROCESSOR_JOIN(FKE_PLATFORM_HEADER_NAME, Suffix))
#else
	// Creates a string that can be used to include a header in the form "Platform/PlatformHeader.h", like "Windows/WindowsPlatformFile.h"
	#define FKE_COMPILED_PLATFORM_HEADER(Suffix) FKE_PREPROCESSOR_TO_STRING(FKE_PREPROCESSOR_JOIN(FKE_PREPROCESSOR_JOIN(FKE_PLATFORM_HEADER_NAME, _platform)/FKE_PREPROCESSOR_JOIN(FKE_PLATFORM_HEADER_NAME, _), Suffix))
#endif

#if FKE_PLATFORM_IS_EXTENSION
	// Creates a string that can be used to include a header with the platform in its name, like "Pre/Fix/PlatformNameSuffix.h"
	#define FKE_COMPILED_PLATFORM_HEADER_WITH_PREFIX(Prefix, Suffix) FKE_PREPROCESSOR_TO_STRING(Prefix/FKE_PREPROCESSOR_JOIN(FKE_PLATFORM_HEADER_NAME, Suffix))
#else
	// Creates a string that can be used to include a header with the platform in its name, like "Pre/Fix/PlatformName/PlatformNameSuffix.h"
	#define FKE_COMPILED_PLATFORM_HEADER_WITH_PREFIX(Prefix, Suffix) FKE_PREPROCESSOR_TO_STRING(Prefix/FKE_PREPROCESSOR_JOIN(FKE_PREPROCESSOR_JOIN(FKE_PLATFORM_HEADER_NAME, _platform)/FKE_PLATFORM_HEADER_NAME, Suffix))
#endif