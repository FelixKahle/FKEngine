// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

// phantom definitions to help VAX parse our VARARG_ * macros(VAX build 1440)
#ifdef VISUAL_ASSIST_HACK
	#define VARARG_DECL( FuncRet, StaticFuncRet, Return, FuncName, Pure, FmtType, ExtraDecl, ExtraCall ) FuncRet FuncName( ExtraDecl FmtType Fmt, ... )
	#define VARARG_BODY( FuncRet, FuncName, FmtType, ExtraDecl ) FuncRet FuncName( ExtraDecl FmtType Fmt, ... )
#endif // VISUAL_ASSIST_HACK


#define FKE_GET_VARARGS(msg, msgsize, len, lastarg, fmt) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		fkengine::fkecore::c_string::get_var_args(msg, msgsize, fmt, ap); \
		va_end(ap); \
	}
#define FKE_GET_VARARGS_WIDE(msg, msgsize, len, lastarg, fmt) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		fkengine::fkecore::c_string_wide::get_var_args(msg, msgsize, fmt, ap); \
		va_end(ap); \
	}
#define FKE_GET_VARARGS_ANSI(msg, msgsize, len, lastarg, fmt) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		fkengine::fkecore::c_string_ansi::get_var_args(msg, msgsize, fmt, ap); \
		va_end(ap); \
	}
#define FKE_GET_VARARGS_RESULT(msg, msgsize, len, lastarg, fmt, result) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		result = fkengine::fkecore::c_string::get_var_args(msg, msgsize, fmt, ap); \
		if (result >= msgsize) \
		{ \
			result = -1; \
		} \
		va_end(ap); \
	}
#define FKE_GET_VARARGS_RESULT_WIDE(msg, msgsize, len, lastarg, fmt, result) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		result = fkengine::fkecore::c_string_wide::get_var_args(msg, msgsize, fmt, ap); \
		if (result >= msgsize) \
		{ \
			result = -1; \
		} \
		va_end(ap); \
	}
#define FKE_GET_VARARGS_RESULT_ANSI(msg, msgsize, len, lastarg, fmt, result) \
	{ \
		va_list ap; \
		va_start(ap, lastarg); \
		result = fkengine::fkecore::c_string_ansi::get_var_args(msg, msgsize, fmt, ap); \
		if (result >= msgsize) \
		{ \
			result = -1; \
		} \
		va_end(ap); \
	}

/*-----------------------------------------------------------------------------
Ugly VarArgs type checking (debug builds only).
-----------------------------------------------------------------------------*/

#define FKE_VARARG_EXTRA(...) __VA_ARGS__,
#define FKE_VARARG_NONE
#define FKE_VARARG_PURE = 0