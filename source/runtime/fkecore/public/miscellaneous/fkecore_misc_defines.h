// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "hardware_abstraction_layer/preprocessor_helpers.h"

#ifndef RC_INVOKED

    // Set up optimization control macros, now that we have both the build settings and the platform macros
    #define FKE_PRAGMA_DISABLE_OPTIMIZATION	FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
    #if FKE_BUILD_DEBUG
        #define FKE_PRAGMA_ENABLE_OPTIMIZATION FKE_PRAGMA_DISABLE_OPTIMIZATION_ACTUAL
    #else
        #define FKE_PRAGMA_ENABLE_OPTIMIZATION FKE_PRAGMA_ENABLE_OPTIMIZATION_ACTUAL
    #endif


    // Code analysis features.
    #ifndef FKE_USING_CODE_ANALYSIS
        #define FKE_USING_CODE_ANALYSIS 0
    #endif

    #if FKE_USING_CODE_ANALYSIS
        #if !defined( FKE_CA_IN ) || !defined( FKE_CA_OUT ) || !defined( FKE_CA_READ_ONLY ) || !defined( FKE_CA_WRITE_ONLY ) || !defined( FKE_CA_VALID_POINTER ) || !defined( FKE_CA_CHECK_RETVAL ) || !defined( FKE_CA_NO_RETURN ) || !defined( FKE_CA_SUPPRESS ) || !defined( FKE_CA_ASSUME )
            #error Code analysis macros are not configured correctly for this platform
        #endif
    #else
        #define FKE_CA_IN 
        #define FKE_CA_OUT
        #define FKE_CA_READ_ONLY
        #define FKE_CA_WRITE_ONLY
        #define FKE_CA_VALID_POINTER
        #define FKE_CA_CHECK_RETVAL
        #define FKE_CA_NO_RETURN
        #define FKE_CA_SUPPRESS(warningNumber)
        #define FKE_CA_ASSUME(expr)
        #define FKE_CA_CONSTANT_IF(condition) if (condition)
    #endif

    #ifndef FKE_USING_THREAD_SANITISER
        #define FKE_USING_THREAD_SANITISER 0
    #endif

    #if FKE_USING_THREAD_SANITISER
        #if !defined( FKE_TSAN_SAFE ) || !defined( FKE_TSAN_BEFORE ) || !defined( FKE_TSAN_AFTER ) || !defined( FKE_TSAN_ATOMIC )
            #error Thread Sanitiser macros are not configured correctly for this platform
        #endif
    #else
        #define FKE_TSAN_SAFE
        #define FKE_TSAN_BEFORE(addr)
        #define FKE_TSAN_AFTER(addr)
        #define FKE_TSAN_ATOMIC(type) type
    #endif
#endif



// When passed to pragma message will result in clickable warning in VS
#define FKE_WARNING_LOCATION(line) __FILE__ "(" FKE_PREPROCESSOR_TO_STRING(line) ")"

// Push and pop macro definitions
#ifdef __clang__
    #define FKE_PUSH_MACRO(name) _Pragma(FKE_PREPROCESSOR_TO_STRING(push_macro(FKE_PREPROCESSOR_TO_STRING(name))))
    #define FKE_POP_MACRO(name) _Pragma(FKE_PREPROCESSOR_TO_STRING(pop_macro(FKE_PREPROCESSOR_TO_STRING(name))))
#else
    #define FKE_PUSH_MACRO(name) __pragma(push_macro(FKE_PREPROCESSOR_TO_STRING(name)))
    #define FKE_POP_MACRO(name) __pragma(pop_macro(FKE_PREPROCESSOR_TO_STRING(name)))
#endif


#ifdef __COUNTER__
    /** Created a variable with a unique name. */
    #define FKE_ANONYMOUS_VARIABLE(name) FKE_PREPROCESSOR_JOIN(name, __COUNTER__)
#else
    /** Created a variable with a unique name. Less reliable than the __COUNTER__ version. */
    #define FKE_ANONYMOUS_VARIABLE(name) FKE_PREPROCESSOR_JOIN(name, __LINE__)
#endif

/**
 * Macro for marking up deprecated code, functions and types.
 *
 * This should be used as syntactic replacement for the [[deprecated]] attribute
 * which provides a FKE version number.
 *
 * Features that are marked as deprecated are removed in future releases. If you are using a deprecated feature in your code, you should
 * replace it before upgrading to the next release.
 *
 * @param Version - The release number in which the feature was marked deprecated.
 * @param Message - A message containing upgrade notes.
 */
#define FKE_DEPRECATED(version, message) [[deprecated(message " Please update your code to the new API.")]]

 // These defines are used to mark a difference between two pointers as expected to fit into the specified range
 // while still leaving something searchable if the surrounding code is updated to work with a 64 bit count/range
 // in the future
#define FKE_PTRDIFF_TO_INT32(argument) static_cast<int32_t>(argument)
#define FKE_PTRDIFF_TO_UINT32(argument) static_cast<uint32_t>(argument)

/**
 * Makes a type non-copyable and non-movable by deleting copy/move constructors and assignment/move operators.
 * The macro should be placed in the public section of the type for better compiler diagnostic messages.
 */
#define FKE_NONCOPYABLE(type_name) \
	    type_name(type_name&&) = delete; \
	    type_name(const type_name&) = delete; \
	    type_name& operator=(const type_name&) = delete; \
	    type_name& operator=(type_name&&) = delete

#define FKE_STATIC_CLASS(type_name) \
        type_name(type_name&&) = delete; \
	    type_name(const type_name&) = delete; \
	    type_name& operator=(const type_name&) = delete; \
	    type_name& operator=(type_name&&) = delete; \
        protected: \
        type_name() {} \
        private:

#define FKE_STATIC_STRUCT(type_name) \
        type_name(type_name&&) = delete; \
	    type_name(const type_name&) = delete; \
	    type_name& operator=(const type_name&) = delete; \
	    type_name& operator=(type_name&&) = delete; \
        protected : \
        type_name() {} \
        public:

#define FKE_AUTO_CALL_FUNCTION(func) \
        struct auto_call_##func \
        { \
            FKE_FORCEINLINE auto_call_##func() \
            { \
                func(); \
            } \
        } FKE_ANONYMOUS_VARIABLE(variable_auto_call_##func)

#define FKE_AUTO_CALL_EXPRESSION(call, expr) \
        struct auto_call_##call \
        { \
            FKE_FORCEINLINE auto_call_##call() \
            { \
                expr; \
            } \
        } FKE_ANONYMOUS_VARIABLE(variable_auto_call_##call)

#define FKE_USE_FKENIGNE_NAMESPACE using namespace fkengine