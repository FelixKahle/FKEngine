// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "templates/array_count.h"
#include "miscellaneous/c_string.h"
#include "miscellaneous/var_args.h"

#define FKE_GROWABLE_LOGF(serialize_func) \
	int32_t	buffer_size	= 1024; \
	char_t*	buffer		= NULL; \
	int32_t	result		= -1; \
	/* allocate some stack space to use on the first pass, which matches most strings */ \
	char_t	stack_buffer[512]; \
	char_t*	allocated_buffer = NULL; \
\
	/* first, try using the stack buffer */ \
	buffer = stack_buffer; \
	FKE_GET_VARARGS_RESULT( buffer, FKE_ARRAY_COUNT(stack_buffer), FKE_ARRAY_COUNT(stack_buffer) - 1, fmt, fmt, result ); \
\
	/* if that fails, then use heap allocation to make enough space */ \
	while(result == -1) \
	{ \
		free(allocated_buffer); \
		/* We need to use malloc here directly as GMalloc might not be safe. */ \
		buffer = allocated_buffer = (char_t*) malloc( buffer_size * sizeof(char_t) ); \
		if (buffer == NULL) \
		{ \
			return; \
		} \
		FKE_GET_VARARGS_RESULT( buffer, buffer_size, buffer_size-1, fmt, fmt, result ); \
		buffer_size *= 2; \
	}; \
	buffer[result] = 0; \
	; \
\
	serialize_func; \
	free(allocated_buffer)