// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Code analysis features
#if defined( __clang_analyzer__ )
	#define FKE_USING_CODE_ANALYSIS 1
#else
	#define FKE_USING_CODE_ANALYSIS 0
#endif

//
// NOTE: To suppress a single occurrence of a code analysis warning:
//
// 		FKE_CA_SUPPRESS( <WarningNumber> )
//		...code that triggers warning...
//

//
// NOTE: To disable all code analysis warnings for a section of code (such as include statements
//       for a third party library), you can use the following:
//
// 		#if FKE_USING_CODE_ANALYSIS
// 			FKE_MSVC_PRAGMA( warning( push ) )
// 			FKE_MSVC_PRAGMA( warning( disable : ALL_CODE_ANALYSIS_WARNINGS ) )
// 		#endif	// USING_CODE_ANALYSIS
//
//		<code with warnings>
//
// 		#if FKE_USING_CODE_ANALYSIS
// 			FKE_MSVC_PRAGMA( warning( pop ) )
// 		#endif	// FKE_USING_CODE_ANALYSIS
//

#if FKE_USING_CODE_ANALYSIS

	// Input argument
	// Example:  void SetValue( FKE_CA_IN bool bReadable );
	#define FKE_CA_IN

	// Output argument
	// Example:  void FillValue( FKE_CA_OUT bool& bWriteable );
	#define FKE_CA_OUT

	// Specifies that a function parameter may only be read from, never written.
	// NOTE: FKE_CA_READ_ONLY is inferred automatically if your parameter is has a const qualifier.
	// Example:  void SetValue( FKE_CA_READ_ONLY bool bReadable );
	#define FKE_CA_READ_ONLY

	// Specifies that a function parameter may only be written to, never read.
	// Example:  void FillValue( FKE_CA_WRITE_ONLY bool& bWriteable );
	#define FKE_CA_WRITE_ONLY

	// Incoming pointer parameter must not be NULL and must point to a valid location in memory.
	// Place before a function parameter's type name.
	// Example:  void SetPointer( FKE_CA_VALID_POINTER void* Pointer );
	#define FKE_CA_VALID_POINTER

	// Caller must check the return value.  Place before the return value in a function declaration.
	// Example:  FKE_CA_CHECK_RETVAL int32_t GetNumber();
	#define FKE_CA_CHECK_RETVAL

	// Function is expected to never return
	#define FKE_CA_NO_RETURN __attribute__((analyzer_noreturn))

	// Suppresses a warning for a single occurrence.  Should be used only for code analysis warnings on Windows platform!
	#define FKE_CA_SUPPRESS( warning_number )

	// Tells the code analysis engine to assume the statement to be true.  Useful for suppressing false positive warnings.
	// NOTE: We use a double operator not here to avoid issues with passing certain class objects directly into __analysis_assume (which may cause a bogus compiler warning)
	#define FKE_CA_ASSUME( expr )

	// Does a simple 'if (Condition)', but disables warnings about using constants in the condition.  Helps with some macro expansions.
	#define FKE_CA_CONSTANT_IF(condition) if (condition)


	//
	// Disable some code analysis warnings that we are NEVER interested in
	//

	// NOTE: Please be conservative about adding new suppressions here!  If you add a suppression, please
	//       add a comment that explains the rationale.

#endif

#if defined(__has_feature) && __has_feature(address_sanitizer)
	#define FKE_USING_ADDRESS_SANITISER 1
#else
	#define FKE_USING_ADDRESS_SANITISER 0
#endif

#if defined(__has_feature) && __has_feature(thread_sanitizer)
	#define FKE_USING_THREAD_SANITISER 1
#else
	#define FKE_USING_THREAD_SANITISER 0
#endif

// Clang does not expose __has_feature(undefined_behavior_sanitizer) so this define comes directly from UBT.
#ifndef FKE_USING_UNDEFINED_BEHAVIOR_SANITISER
	#define FKE_USING_UNDEFINED_BEHAVIOR_SANITISER 0
#endif

#if FKE_USING_THREAD_SANITISER

	// Function attribute to disable thread sanitiser validation on specific functions that assume non-atomic load/stores are implicitly atomic
	// This is only safe for int32_t/uint32_t/int64_t/uint64_t/uintptr_t/intptr_t/void* types on x86/x64 strongly-consistent memory systems.
	#define FKE_TSAN_SAFE __attribute__((no_sanitize("thread")))

// Thread-sanitiser annotation functions.
#ifdef __cplusplus
extern "C" {
#endif
	void AnnotateHappensBefore(const char* f, int l, void* addr);
	void AnnotateHappensAfter(const char* f, int l, void* addr);
#ifdef __cplusplus
}
#endif

	// Annotate that previous load/stores occur before addr 
	#define FKE_TSAN_BEFORE(addr) AnnotateHappensBefore(__FILE__, __LINE__, (void*)(addr))

	// Annotate that previous load/stores occur after addr 
	#define FKE_TSAN_AFTER(addr) AnnotateHappensAfter(__FILE__, __LINE__, (void*)(addr))

	// Because annotating the global bools is tiresome...
	#ifdef __cplusplus
		#include <atomic>
		#define FKE_TSAN_ATOMIC(Type) std::atomic<Type>
	#endif

#endif
