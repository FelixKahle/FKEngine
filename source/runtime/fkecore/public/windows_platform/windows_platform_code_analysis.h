// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#if defined( _PREFAST_ ) || defined( PVS_STUDIO )
	/** 1 if code analysis is used, 0 otherwise. */
	#define FKE_USING_CODE_ANALYSIS 1
#else
	/** 1 if code analysis is used, 0 otherwise. */
	#define FKE_USING_CODE_ANALYSIS 0
#endif

#if FKE_USING_CODE_ANALYSIS
	/** Input argument. */
	#define FKE_CA_IN __in

	/** Output argument. */
	#define FKE_CA_OUT __out

	/** Specifies that a function parameter may only be read from, never written. */
	#define FKE_CA_READ_ONLY [Pre(Access=Read)]

	/** Specifies that a function parameter may only be written to, never read. */
	#define FKE_CA_WRITE_ONLY [Pre(Access=Write)]

	/** 
	 * Incoming pointer parameter must not be NULL and must point to a valid location in memory.
	 * Place before a function parameter's type name.
	 */
	#define FKE_CA_VALID_POINTER [Pre(Null=No,Valid=Yes)]

	/** 
	 * Caller must check the return value. 
	 * Place before the return value in a function declaration. 
	 */
	#define FKE_CA_CHECK_RETVAL [returnvalue:Post(MustCheck=Yes)]

	/** Function is expected to never return. */
	#define FKE_CA_NO_RETURN __declspec(noreturn)

	/**
	 * Suppresses a warning for a single occurrence. Should be used only for code analysis warnings on Windows platform.
	 *
	 * @param WarningNumber - The warning number.
	 */
	#define FKE_CA_SUPPRESS(WarningNumber) __pragma( warning( suppress: WarningNumber ) )

	/**
	 * Tells the code analysis engine to assume the statement to be true. Useful for suppressing false positive warnings.
	 *
	 * @param Expr - The expression.
	 */
	#define FKE_CA_ASSUME(Expr) __analysis_assume( !!( Expr ) )

	/**
	 * Does a simple 'if (Condition)', but disables warnings about using constants in the condition. Helps with some macro expansions.
	 *
	 * @param Condition - The condition.
	 */
	#define FKE_CA_CONSTANT_IF(Condition) __pragma(warning(push)) __pragma(warning(disable:6326)) if (Condition) __pragma(warning(pop))

	#pragma warning(disable : 6255) // warning C6255: _alloca indicates failure by raising a stack overflow exception. Consider using _malloca instead.
	#pragma warning(disable : 6102) // warning C6102: Using 'variable' from failed function call at line 'line'.
	#pragma warning(disable : 6320) // warning C6320: Exception-filter expression is the constant EXCEPTION_EXECUTE_HANDLER. This might mask exceptions that were not intended to be handled.
	#pragma warning(disable : 6326) // warning C6326 : Potential comparison of a constant with another constant.
	#pragma warning(disable : 6240) // warning C6240 : (<expression> && <non-zero constant>) always evaluates to the result of <expression>. Did you intend to use the bitwise-and operator?
#endif