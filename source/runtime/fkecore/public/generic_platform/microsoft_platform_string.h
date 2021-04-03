// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/char.h"
#include "generic_platform/generic_platform_string.h"
#include "generic_platform/generic_platform_stricmp.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <tchar.h>

#pragma warning(push)
#pragma warning(disable : 4996) // 'function' was declared deprecated
#pragma warning(disable : 4995) // 'function' was declared deprecated

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		struct microsoft_platform_string : public generic_platform_string
		{
			FKE_STATIC_STRUCT(microsoft_platform_string)

				static FKE_FORCEINLINE widechar_t* strcpy(widechar_t* dest, size_t dest_count, const widechar_t* src)
			{
				return (widechar_t*)::wcscpy(dest, src);
			}

			static FKE_FORCEINLINE widechar_t* strncpy(widechar_t* dest, const widechar_t* src, size_t max_len)
			{
				::wcsncpy(dest, src, max_len - 1);
				dest[max_len - 1] = 0;
				return dest;
			}

			static FKE_FORCEINLINE widechar_t* strcat(widechar_t* dest, size_t dest_count, const widechar_t* src)
			{
				return (widechar_t*)::wcscat(dest, src);
			}

			static FKE_FORCEINLINE widechar_t* strupr(widechar_t* dest, size_t dest_count)
			{
				return (widechar_t*)::_wcsupr(dest);
			}

			static FKE_FORCEINLINE int32_t strcmp(const widechar_t* in_string_1, const widechar_t* in_string_2)
			{
				return ::wcscmp(in_string_1, in_string_2);
			}

			static FKE_FORCEINLINE int32_t strncmp(const widechar_t* in_string_1, const widechar_t* in_string_2, size_t count)
			{
				return ::wcsncmp(in_string_1, in_string_2, count);
			}

			static FKE_FORCEINLINE int32_t strlen(const widechar_t* in_string)
			{
				return ::wcslen(in_string);
			}

			static FKE_FORCEINLINE const widechar_t* strstr(const widechar_t* in_string, const widechar_t* Find)
			{
				return ::wcsstr(in_string, Find);
			}

			static FKE_FORCEINLINE const widechar_t* strchr(const widechar_t* in_string, widechar_t c)
			{
				return ::wcschr(in_string, c);
			}

			static FKE_FORCEINLINE const widechar_t* strrchr(const widechar_t* in_string, widechar_t c)
			{
				return ::wcsrchr(in_string, c);
			}

			static FKE_FORCEINLINE int32_t atoi(const widechar_t* in_string)
			{
				return ::_wtoi(in_string);
			}

			static FKE_FORCEINLINE int64_t atoi64(const widechar_t* in_string)
			{
				return ::_wtoi64(in_string);
			}

			static FKE_FORCEINLINE float atof(const widechar_t* in_string)
			{
				return ::_wtof(in_string);
			}

			static FKE_FORCEINLINE double atod(const widechar_t* in_string)
			{
				return ::wcstod(in_string, NULL);
			}

			static FKE_FORCEINLINE int32_t strtoi(const widechar_t* start, widechar_t** end, int32_t base)
			{
				return ::wcstoul(start, end, base);
			}

			static FKE_FORCEINLINE int64_t strtoi64(const widechar_t* start, widechar_t** end, int32_t base)
			{
				return ::_wcstoi64(start, end, base);
			}

			static FKE_FORCEINLINE uint64_t strtoui64(const widechar_t* start, widechar_t** end, int32_t base)
			{
				return ::_wcstoui64(start, end, base);
			}

			static FKE_FORCEINLINE widechar_t* strtok(widechar_t* str_token, const widechar_t* delim, widechar_t** context)
			{
				return ::wcstok_s(str_token, delim, context);
			}

			static FKE_FORCEINLINE int32_t get_var_args(widechar_t* dest, size_t dest_size, const widechar_t*& fmt, va_list arg_ptr)
			{
				int32_t result = ::vswprintf(dest, dest_size, fmt, arg_ptr);
				va_end(arg_ptr);
				return result;
			}

			static FKE_FORCEINLINE ansichar_t* strcpy(ansichar_t* dest, size_t dest_count, const ansichar_t* src)
			{
				return (ansichar_t*)::strcpy(dest, src);
			}

			static FKE_FORCEINLINE void strncpy(ansichar_t* dest, const ansichar_t* src, size_t max_len)
			{
				::strncpy(dest, src, max_len);
				dest[max_len - 1] = 0;
			}

			static FKE_FORCEINLINE ansichar_t* strcat(ansichar_t* dest, size_t dest_count, const ansichar_t* src)
			{
				return (ansichar_t*)::strcat(dest, src);
			}

			static FKE_FORCEINLINE ansichar_t* strupr(ansichar_t* dest, size_t dest_count)
			{
				return (ansichar_t*)::_strupr(dest);
			}

			static FKE_FORCEINLINE int32_t strcmp(const ansichar_t* in_string_1, const ansichar_t* in_string_2)
			{
				return ::strcmp(in_string_1, in_string_2);
			}

			static FKE_FORCEINLINE int32_t strncmp(const ansichar_t* in_string_1, const ansichar_t* in_string_2, size_t count)
			{
				return ::strncmp(in_string_1, in_string_2, count);
			}

			static FKE_FORCEINLINE int32_t strlen(const ansichar_t* in_string)
			{
				return ::strlen(in_string);
			}

			static FKE_FORCEINLINE const ansichar_t* strstr(const ansichar_t* in_string, const ansichar_t* Find)
			{
				return ::strstr(in_string, Find);
			}

			static FKE_FORCEINLINE const ansichar_t* strchr(const ansichar_t* in_string, ansichar_t c)
			{
				return ::strchr(in_string, c);
			}

			static FKE_FORCEINLINE const ansichar_t* strrchr(const ansichar_t* in_string, ansichar_t c)
			{
				return ::strrchr(in_string, c);
			}

			static FKE_FORCEINLINE int32_t atoi(const ansichar_t* in_string)
			{
				return ::atoi(in_string);
			}

			static FKE_FORCEINLINE int64_t atoi64(const ansichar_t* in_string)
			{
				return ::_strtoi64(in_string, NULL, 10);
			}

			static FKE_FORCEINLINE float atof(const ansichar_t* in_string)
			{
				return (float)::atof(in_string);
			}

			static FKE_FORCEINLINE double atod(const ansichar_t* in_string)
			{
				return ::atof(in_string);
			}

			static FKE_FORCEINLINE int32_t strtoi(const ansichar_t* start, ansichar_t** end, int32_t base)
			{
				return ::strtol(start, end, base);
			}

			static FKE_FORCEINLINE int64_t strtoi64(const ansichar_t* start, ansichar_t** end, int32_t base)
			{
				return ::_strtoi64(start, end, base);
			}

			static FKE_FORCEINLINE uint64_t strtoui64(const ansichar_t* start, ansichar_t** end, int32_t base)
			{
				return ::_strtoui64(start, end, base);
			}

			static FKE_FORCEINLINE ansichar_t* strtok(ansichar_t* str_token, const ansichar_t* delim, ansichar_t** context)
			{
				return ::strtok_s(str_token, delim, context);
			}

			static FKE_FORCEINLINE int32_t get_var_args(ansichar_t* dest, size_t dest_size, const ansichar_t*& fmt, va_list arg_ptr)
			{
				int32_t result = ::vsnprintf(dest, dest_size, fmt, arg_ptr);
				va_end(arg_ptr);
				return (result != -1 && result < (int32_t)dest_size) ? result : -1;
			}

			/**
			 * UCS2CHAR implementation - this is identical to widechar_t for Windows platforms
			 */
			static FKE_FORCEINLINE int32_t strlen(const ucs2char_t* in_string)
			{
				return ::wcslen((const widechar_t*)in_string);
			}
		};
	}
}

#pragma warning(pop)