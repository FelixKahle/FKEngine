// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"
#include "miscellaneous/var_args.h"
#include "miscellaneous/assertion_macros.h"
#include "miscellaneous/char.h"
#include "hardware_abstraction_layer/platform_string.h"
#include "templates/is_array_or_ref_of_type.h"

#define FKE_MAX_SPRINTF 1024

/** The namespace of the FKEngine. */
namespace fkengine
{
	/** Determines case sensitivity options for string comparisons. */
	namespace search_case
	{
		enum type
		{
			/** Case sensitive. Upper/lower casing must match for strings to be considered equal. */
			case_sensitive,

			/** Ignore case. Upper/lower casing does not matter when making a comparison. */
			ignore_case,
		};
	};

	/** Determines search direction for string operations. */
	namespace search_dir
	{
		enum type
		{
			/** Search from the start, moving forward through the string. */
			from_start,

			/** Search from the end, moving backward through the string. */
			from_end,
		};
	}

	/** Helper class used to convert CString into a boolean value. */
	struct FKECORE_API to_bool_helper
	{
		FKE_STATIC_STRUCT(to_bool_helper)

		static bool from_c_string_ansi(const ansichar_t* in_string);
		static bool from_c_string_wide(const widechar_t* in_String);
	};

	/**
	 *	Set of basic string utility functions operating on plain C strings. In addition to the
	 *	wrapped C string API,this struct also contains a set of widely used utility functions that
	 *  operate on c strings.
	 *	There is a specialized implementation for ansichar_t and widechar_t strings provided.
	 */
	template <typename t>
	struct c_string_base
	{
		FKE_STATIC_STRUCT(c_string_base)

		typedef t char_type;

		/**
		 * Returns whether this string contains only pure ansi characters
		 * @param str - string that will be checked
		 **/
		static FKE_FORCEINLINE bool is_pure_ansi(const char_type* str);
		static FKE_FORCEINLINE bool is_pure_ansi(const char_type* str, const size_t str_len);

		/**
		 * Returns whether this string contains only numeric characters
		 * @param str - string that will be checked
		 */
		static bool is_numeric(const char_type* str)
		{
			if (*str == '-' || *str == '+')
			{
				str++;
			}

			bool has_dot = false;
			while (*str != '\0')
			{
				if (*str == '.')
				{
					if (has_dot)
					{
						return false;
					}
					has_dot = true;
				}
				else if (!char_utility_tchar::is_digit(*str))
				{
					return false;
				}

				++str;
			}

			return true;
		}

		/**
		 * strcpy wrapper
		 *
		 * @param dest - destination string to copy to
		 * @param Destcount - size_t of dest in characters
		 * @param src - source string
		 * @return destination string
		 */
		static FKE_FORCEINLINE char_type* strcpy(char_type* dest, size_t dest_count, const char_type* src);

		/**
		 * Copy a string with length checking. Behavior differs from strncpy in that last character is zeroed.
		 *
		 * @param dest - destination buffer to copy to
		 * @param src - source buffer to copy from
		 * @param max_len - max length of the buffer (including null-terminator)
		 * @return pointer to resulting string buffer
		 */
		static FKE_FORCEINLINE char_type* strncpy(char_type* dest, const char_type* src, int32_t max_len);

		static FKE_FORCEINLINE char_type* strnlen(char_type* in_string, const char_type* find);

		static FKE_FORCEINLINE const typename char_type* strnlen(const char_type* in_string, const char_type* find);

		/**
		 * strcpy wrapper
		 * (templated version to automatically handle static destination array case)
		 *
		 * @param dest - destination string to copy to
		 * @param src - source string
		 * @return destination string
		 */
		template<size_t dest_count>
		static FKE_FORCEINLINE char_type* strcpy(char_type(&dest)[dest_count], const char_type* src)
		{
			return strcpy(dest, dest_count, src);
		}

		/**
		 * strcat wrapper
		 *
		 * @param dest - destination string to copy to
		 * @param Destcount - size_t of dest in characters
		 * @param src - source string
		 * @return destination string
		 */
		static FKE_FORCEINLINE char_type* strcat(char_type* dest, size_t dest_count, const char_type* src);

		/**
		 * strcat wrapper
		 * (templated version to automatically handle static destination array case)
		 *
		 * @param dest - destination string to copy to
		 * @param src - source string
		 * @return destination string
		 */
		template<size_t dest_count>
		static FKE_FORCEINLINE char_type* strcat(char_type(&dest)[dest_count], const char_type* src)
		{
			return strcat(dest, dest_count, src);
		}

		/**
		 * Concatenate a string with length checking.
		 *
		 * @param dest - destination buffer to append to
		 * @param src - source buffer to copy from
		 * @param max_len - max length of the buffer
		 * @return pointer to resulting string buffer
		 */
		static inline char_type* strncat(char_type* dest, const char_type* src, int32_t max_len)
		{
			int32_t len = strlen(dest);
			char_type* new_dest = dest + len;
			if ((max_len -= len) > 0)
			{
				strncpy(new_dest, src, max_len);
			}
			return dest;
		}

		/**
		 * strupr wrapper
		 *
		 * @param dest - destination string to convert
		 * @param Destcount - size_t of dest in characters
		 * @return destination string
		 */
		static FKE_FORCEINLINE char_type* strupr(char_type* dest, size_t dest_count);


		/**
		 * strupr wrapper
		 * (templated version to automatically handle static destination array case)
		 *
		 * @param dest - destination string to convert
		 * @return destination string
		 */
		template<size_t dest_count>
		static FKE_FORCEINLINE char_type* strupr(char_type(&dest)[dest_count])
		{
			return strupr(dest, dest_count);
		}

		/**
		 * strcmp wrapper
		 **/
		static FKE_FORCEINLINE int32_t strcmp(const char_type* string_1, const char_type* string_2);

		/**
		 * strncmp wrapper
		 */
		static FKE_FORCEINLINE int32_t strncmp(const char_type* string_1, const char_type* string_2, size_t Count);

		/**
		 * strnicmp wrapper
		 */
		static FKE_FORCEINLINE int32_t strnicmp(const char_type* string_1, const char_type* string_2, size_t count);

		/**
		 * stricmp wrapper
		 */
		static FKE_FORCEINLINE int32_t stricmp(const char_type* string_1, const char_type* string_2);

		/**
		 * strifind wrapper
		 */
		static FKE_FORCEINLINE int32_t strifind(const char_type* string_1, const char_type* string_2, size_t Count);

		/**
		 * Returns a static string that is filled with a variable number of spaces
		 *
		 * @param num_spaces Number of spaces to put into the string, max of 255
		 *
		 * @return The string of num_spaces spaces.
		 */
		static const char_type* spc(int32_t num_spaces);

		/**
		 * Returns a static string that is filled with a variable number of tabs
		 *
		 * @param num_tabs Number of tabs to put into the string, max of 255
		 *
		 * @return The string of num_tabs tabs.
		 */
		static const char_type* tab(int32_t num_tabs);

		/**
		 * find string in string, case sensitive, requires non-alphanumeric lead-in.
		 */
		static const char_type* strfind(const char_type* str, const char_type* find, bool skip_quoted_chars = false);

		/**
		 * find string in string, case insensitive, requires non-alphanumeric lead-in.
		 */
		static const char_type* strifind(const char_type* str, const char_type* find, bool skip_quoted_chars = false);

		/**
		 * Finds string in string, case insensitive, requires the string be surrounded by one the specified
		 * delimiters, or the start or end of the string.
		 */
		static const char_type* strfind_delim(const char_type* str, const char_type* find, const char_type* delim = FKE_LITERAL(char_type, " \t,"));

		/**
		 * Finds string in string, case insensitive
		 * @param str The string to look through
		 * @param find The string to find inside str
		 * @return Position in str if find was found, otherwise, NULL
		 */
		static const char_type* stristr(const char_type* str, const char_type* find);

		/**
		 * Finds string in string, case insensitive (non-const version)
		 * @param str The string to look through
		 * @param find The string to find inside str
		 * @return Position in str if find was found, otherwise, NULL
		 */
		static char_type* stristr(char_type* str, const char_type* find) { return (char_type*)stristr((const char_type*)str, find); }

		/**
		 * strlen wrapper
		 */
		static FKE_FORCEINLINE int32_t strlen(const char_type* in_string);

		/**
		 * Calculate the length of the string up to the given size_t.
		 * @param in_string A possibly-null-terminated string in a character array with a size_t of at least string_size.
		 * @param string_size The maximum number of characters to read from in_string.
		 * @return length The smaller of string_size and the number of characters in in_string before a null character.
		 */
		static FKE_FORCEINLINE int32_t strnlen(const char_type* in_string, size_t string_size);

		/**
		 * strstr wrapper
		 */
		static FKE_FORCEINLINE const char_type* strstr(const char_type* in_string, const char_type* find);
		static FKE_FORCEINLINE char_type* strstr(char_type* in_string, const char_type* find);

		/**
		 * strchr wrapper
		 */
		static FKE_FORCEINLINE const char_type* strchr(const char_type* in_string, char_type c);
		static FKE_FORCEINLINE char_type* strchr(char_type* in_string, char_type c);

		/**
		 * strrchr wrapper
		 */
		static FKE_FORCEINLINE const char_type* strrchr(const char_type* in_string, char_type c);
		static FKE_FORCEINLINE char_type* strrchr(char_type* in_string, char_type c);

		/**
		 * strrstr wrapper
		 */
		static FKE_FORCEINLINE const char_type* strrstr(const char_type* in_string, const char_type* find);
		static FKE_FORCEINLINE char_type* strrstr(char_type* in_string, const char_type* find);

		/**
		 * strspn wrapper
		 */
		static FKE_FORCEINLINE int32_t strspn(const char_type* in_string, const char_type* mask);

		/**
		 * strcspn wrapper
		 */
		static FKE_FORCEINLINE int32_t strcspn(const char_type* in_string, const char_type* mask);

		/**
		 * atoi wrapper
		 */
		static FKE_FORCEINLINE int32_t atoi(const char_type* in_string);

		/**
		 * atoi64 wrapper
		 */
		static FKE_FORCEINLINE int64_t atoi64(const char_type* in_string);

		/**
		 * atof wrapper
		 */
		static FKE_FORCEINLINE float atof(const char_type* in_string);

		/**
		 * atod wrapper
		 */
		static FKE_FORCEINLINE double atod(const char_type* in_string);

		/**
		 * Converts a string into a boolean value
		 *   1, "True", "Yes", FCoreTexts::True, FCoreTexts::Yes, and non-zero integers become true
		 *   0, "False", "No", FCoreTexts::False, FCoreTexts::No, and unparsable values become false
		 *
		 * @return The boolean value
		 */
		static FKE_FORCEINLINE bool to_bool(const char_type* in_string);

		/**
		 * strtoi wrapper
		 */
		static FKE_FORCEINLINE int32_t strtoi(const char_type* start, char_type** end, int32_t Base);

		/**
		 * strtoi wrapper
		 */
		static FKE_FORCEINLINE int64_t strtoi64(const char_type* start, char_type** end, int32_t Base);

		/**
		 * strtoui wrapper
		 */
		static FKE_FORCEINLINE uint64_t strtoui64(const char_type* start, char_type** end, int32_t Base);

		/**
		 * strtok wrapper
		 */
		static FKE_FORCEINLINE char_type* strtok(char_type* token_string, const char_type* delim, char_type** context);

	private:
		static int32_t FKE_VARARGS sprintf_impl(char_type* dest, const char_type* fmt, ...);
		static int32_t FKE_VARARGS snprintf_impl(char_type* dest, int32_t dest_size, const char_type* fmt, ...);

	public:
		/**
		* Standard string formatted print.
		* @warning: make sure code using FCString::Sprintf allocates enough (>= MAX_SPRINTF) memory for the destination buffer
		*/
		template <typename fmt_type, typename... types>
		static int32_t sprintf(char_type* dest, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_type>::value, "Formatting string must be a literal string of the same character type as template.");

			return sprintf_impl(dest, fmt, args...);
		}

		/**
		 * Safe string formatted print.
		 */
		template <typename fmt_type, typename... types>
		static int32_t snprintf(char_type* dest, int32_t dest_size, const fmt_type& fmt, types... args)
		{
			static_assert(is_array_or_ref_of_type<fmt_type, char_type>::value, "Formatting string must be a literal string of the same character type as template.");
			static_assert(conjunction<is_valid_variadic_function_arg<types>...>::value, "Invalid argument(s) passed to snprintf");

			return snprintf_impl(dest, dest_size, fmt, args...);
		}

		/**
		 * Helper function to write formatted output using an argument list
		 *
		 * @param dest - destination string buffer
		 * @param dest_size - size_t of destination buffer
		 * @param fmt - string to print
		 * @param args - argument list
		 * @return number of characters written or -1 if truncated
		 */
		static FKE_FORCEINLINE int32_t get_var_args(char_type* dest, size_t dest_size, const char_type*& fmt, va_list arg_ptr);
	};

	typedef c_string_base<char_t> c_string;
	typedef c_string_base<ansichar_t> c_string_ansi;
	typedef c_string_base<widechar_t> c_string_wide;

	template <typename char_type = char_t>
	struct c_string_spc_helper
	{
		FKE_STATIC_STRUCT(c_string_spc_helper)

		/** Number of characters to be stored in string. */
		static FKE_CONSTEXPR int32_t max_spaces = 255;

		/** Number of tabs to be stored in string. */
		static FKE_CONSTEXPR int32_t max_tabs = 255;

		static FKECORE_API const char_type spc_array[max_spaces + 1];
		static FKECORE_API const char_type tab_array[max_tabs + 1];
	};

	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::spc(int32_t num_spaces)
	{
		//FKE_CHECK(num_spaces >= 0 && num_spaces <= c_string_spc_helper<t>::max_spaces);
		return c_string_spc_helper<t>::spc_array + c_string_spc_helper<t>::max_spaces - num_spaces;
	}

	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::tab(int32_t num_tabs)
	{
		//FKE_CHECK(num_tabs >= 0 && num_tabs <= c_string_spc_helper<t>::max_tabs);
		return c_string_spc_helper<t>::tab_array + c_string_spc_helper<t>::max_tabs - num_tabs;
	}

	//
	// find string in string, case sensitive, requires non-alphanumeric lead-in.
	//
	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::strfind(const char_type* str, const char_type* find, bool skip_quoted_chars)
	{
		if (find == NULL || str == NULL)
		{
			return NULL;
		}

		bool alnum = 0;
		char_type f = *find;
		int32_t length = strlen(find++) - 1;
		char_type c = *str++;
		if (skip_quoted_chars)
		{
			bool in_quoted_str = false;
			while (c)
			{
				if (!in_quoted_str && !alnum && c == f && !strncmp(str, find, length))
				{
					return str - 1;
				}
				alnum = (c >= FKE_LITERAL(char_type, 'A') && c <= FKE_LITERAL(char_type, 'Z')) ||
					(c >= FKE_LITERAL(char_type, 'a') && c <= FKE_LITERAL(char_type, 'z')) ||
					(c >= FKE_LITERAL(char_type, '0') && c <= FKE_LITERAL(char_type, '9'));
				if (c == FKE_LITERAL(char_type, '"'))
				{
					in_quoted_str = !in_quoted_str;
				}
				c = *str++;
			}
		}
		else
		{
			while (c)
			{
				if (!alnum && c == f && !strncmp(str, find, length))
				{
					return str - 1;
				}
				alnum = (c >= FKE_LITERAL(char_type, 'A') && c <= FKE_LITERAL(char_type, 'Z')) ||
					(c >= FKE_LITERAL(char_type, 'a') && c <= FKE_LITERAL(char_type, 'z')) ||
					(c >= FKE_LITERAL(char_type, '0') && c <= FKE_LITERAL(char_type, '9'));
				c = *str++;
			}
		}
		return NULL;
	}

	//
	// find string in string, case insensitive, requires non-alphanumeric lead-in.
	//
	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::strifind(const char_type* str, const char_type* find, bool skip_quoted_chars)
	{
		if (find == NULL || str == NULL)
		{
			return NULL;
		}

		bool alnum = 0;
		char_type f = (*find < FKE_LITERAL(char_type, 'a') || *find > FKE_LITERAL(char_type, 'z')) ? (*find) : (*find + FKE_LITERAL(char_type, 'A') - FKE_LITERAL(char_type, 'a'));
		int32_t length = strlen(find++) - 1;
		char_type c = *str++;

		if (skip_quoted_chars)
		{
			bool in_quoted_str = false;
			while (c)
			{
				if (c >= FKE_LITERAL(char_type, 'a') && c <= FKE_LITERAL(char_type, 'z'))
				{
					c += FKE_LITERAL(char_type, 'A') - FKE_LITERAL(char_type, 'a');
				}
				if (!in_quoted_str && !alnum && c == f && !strnicmp(str, find, length))
				{
					return str - 1;
				}
				alnum = (c >= FKE_LITERAL(char_type, 'A') && c <= FKE_LITERAL(char_type, 'Z')) ||
					(c >= FKE_LITERAL(char_type, '0') && c <= FKE_LITERAL(char_type, '9'));
				if (c == FKE_LITERAL(char_type, '"'))
				{
					in_quoted_str = !in_quoted_str;
				}
				c = *str++;
			}
		}
		else
		{
			while (c)
			{
				if (c >= FKE_LITERAL(char_type, 'a') && c <= FKE_LITERAL(char_type, 'z'))
				{
					c += FKE_LITERAL(char_type, 'A') - FKE_LITERAL(char_type, 'a');
				}
				if (!alnum && c == f && !strnicmp(str, find, length))
				{
					return str - 1;
				}
				alnum = (c >= FKE_LITERAL(char_type, 'A') && c <= FKE_LITERAL(char_type, 'Z')) ||
					(c >= FKE_LITERAL(char_type, '0') && c <= FKE_LITERAL(char_type, '9'));
				c = *str++;
			}
		}
		return NULL;
	}

	//
	// Finds string in string, case insensitive, requires the string be surrounded by one the specified
	// delimiters, or the start or end of the string.
	//
	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::strfind_delim(const char_type* str, const char_type* find, const char_type* delim)
	{
		if (find == NULL || str == NULL)
		{
			return NULL;
		}

		int32_t length = strlen(find);
		const t* found = stristr(str, find);
		if (found)
		{
			// //FKE_CHECK if this occurrence is delimited correctly
			if ((found == str || strchr(delim, found[-1]) != NULL) &&								// either first char, or following a delim
				(found[length] == FKE_LITERAL(char_type, '\0') || strchr(delim, found[length]) != NULL))	// either last or with a delim following
			{
				return found;
			}

			// start searching again after the first matched character
			for (;;)
			{
				str = found + 1;
				found = stristr(str, find);

				if (found == NULL)
				{
					return NULL;
				}

				// //FKE_CHECK if the next occurrence is delimited correctly
				if ((strchr(delim, found[-1]) != NULL) &&												// match is following a delim
					(found[length] == FKE_LITERAL(char_type, '\0') || strchr(delim, found[length]) != NULL))	// either last or with a delim following
				{
					return found;
				}
			}
		}

		return NULL;
	}

	/**
	 * Finds string in string, case insensitive
	 * @param str The string to look through
	 * @param find The string to find inside str
	 * @return Position in str if find was found, otherwise, NULL
	 */
	template <typename t>
	const typename c_string_base<t>::char_type* c_string_base<t>::stristr(const char_type* str, const char_type* find)
	{
		// both strings must be valid
		if (find == NULL || str == NULL)
		{
			return NULL;
		}

		// get upper-case first letter of the find string (to reduce the number of full strnicmps)
		char_type find_initial = char_utility<char_type>::to_upper(*find);
		// get length of find string, and increment past first letter
		int32_t   length = strlen(find++) - 1;
		// get the first letter of the search string, and increment past it
		char_type str_char = *str++;
		// while we aren't at end of string...
		while (str_char)
		{
			// make sure it's upper-case
			str_char = char_utility<char_type>::to_upper(str_char);
			// if it matches the first letter of the find string, do a case-insensitive string compare for the length of the find string
			if (str_char == find_initial && !strnicmp(str, find, length))
			{
				// if we found the string, then return a pointer to the beginning of it in the search string
				return str - 1;
			}
			// go to next letter
			str_char = *str++;
		}

		// if nothing was found, return NULL
		return NULL;
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strcpy(char_type* dest, size_t dest_count, const char_type* src)
	{
		return platform_string::strcpy(dest, dest_count, src);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strncpy(char_type* dest, const char_type* src, int32_t max_len)
	{
		//FKE_CHECK(max_len > 0);
		platform_string::strncpy(dest, src, max_len);
		return dest;
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strcat(char_type* dest, size_t dest_count, const char_type* src)
	{
		return platform_string::strcat(dest, dest_count, src);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strupr(char_type* dest, size_t dest_count)
	{
		return platform_string::strupr(dest, dest_count);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strcmp(const char_type* string_1, const char_type* string_2)
	{
		return platform_string::strcmp(string_1, string_2);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strncmp(const char_type* string_1, const char_type* string_2, size_t Count)
	{
		return platform_string::strncmp(string_1, string_2, Count);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::stricmp(const char_type* string_1, const char_type* string_2)
	{
		return platform_string::stricmp(string_1, string_2);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strnicmp(const char_type* string_1, const char_type* string_2, size_t Count)
	{
		return platform_string::strnicmp(string_1, string_2, Count);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strlen(const char_type* in_string)
	{
		return platform_string::strlen(in_string);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strnlen(const char_type* in_string, size_t string_size)
	{
		return platform_string::strnlen(in_string, string_size);
	}

	template <typename t> FKE_FORCEINLINE
		const typename c_string_base<t>::char_type* c_string_base<t>::strnlen(const char_type* in_string, const char_type* find)
	{
		return platform_string::strnlen(in_string, find);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strnlen(char_type* in_string, const char_type* find)
	{
		return (char_type*)platform_string::strnlen(in_string, find);
	}

	template <typename t> FKE_FORCEINLINE
		const typename c_string_base<t>::char_type* c_string_base<t>::strchr(const char_type* in_string, char_type c)
	{
		return platform_string::strchr(in_string, c);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strchr(char_type* in_string, char_type c)
	{
		return (char_type*)platform_string::strchr(in_string, c);
	}

	template <typename t> FKE_FORCEINLINE
		const typename c_string_base<t>::char_type* c_string_base<t>::strrchr(const char_type* in_string, char_type c)
	{
		return platform_string::strrchr(in_string, c);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strrchr(char_type* in_string, char_type c)
	{
		return (char_type*)platform_string::strrchr(in_string, c);
	}

	template <typename t> FKE_FORCEINLINE
		const typename c_string_base<t>::char_type* c_string_base<t>::strrstr(const char_type* in_string, const char_type* find)
	{
		return strrstr((char_type*)in_string, find);
	}

	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strrstr(char_type* in_string, const char_type* find)
	{
		if (*find == (char_type)0)
		{
			return in_string + strlen(in_string);
		}

		char_type* result = nullptr;
		for (;;)
		{
			char_type* found = strnlen(in_string, find);
			if (!found)
			{
				return result;
			}

			result = found;
			in_string = found + 1;
		}
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strspn(const char_type* in_string, const char_type* mask)
	{
		const char_type* string_it = in_string;
		while (*string_it)
		{
			for (const char_type* mask_it = mask; *mask_it; ++mask_it)
			{
				if (*string_it == *mask_it)
				{
					goto next_char;
				}
			}

			return FKE_PTRDIFF_TO_INT32(string_it - in_string);

		next_char:
			++string_it;
		}

		return FKE_PTRDIFF_TO_INT32(string_it - in_string);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strcspn(const char_type* in_string, const char_type* mask)
	{
		const char_type* string_it = in_string;
		while (*string_it)
		{
			for (const char_type* mask_it = mask; *mask_it; ++mask_it)
			{
				if (*string_it == *mask_it)
				{
					return string_it - in_string;
				}
			}

			++string_it;
		}

		return string_it - in_string;
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::atoi(const char_type* in_string)
	{
		return platform_string::atoi(in_string);
	}

	template <typename t> FKE_FORCEINLINE
		int64_t c_string_base<t>::atoi64(const char_type* in_string)
	{
		return platform_string::atoi64(in_string);
	}

	template <typename t> FKE_FORCEINLINE
		float c_string_base<t>::atof(const char_type* in_string)
	{
		return platform_string::atof(in_string);
	}

	template <typename t> FKE_FORCEINLINE
		double c_string_base<t>::atod(const char_type* in_string)
	{
		return platform_string::atod(in_string);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::strtoi(const char_type* start, char_type** end, int32_t Base)
	{
		return platform_string::strtoi(start, end, Base);
	}

	template <typename t> FKE_FORCEINLINE
		int64_t c_string_base<t>::strtoi64(const char_type* start, char_type** end, int32_t Base)
	{
		return platform_string::strtoi64(start, end, Base);
	}

	template <typename t> FKE_FORCEINLINE
		uint64_t c_string_base<t>::strtoui64(const char_type* start, char_type** end, int32_t Base)
	{
		return platform_string::strtoui64(start, end, Base);
	}


	template <typename t> FKE_FORCEINLINE
		typename c_string_base<t>::char_type* c_string_base<t>::strtok(char_type* token_string, const char_type* delim, char_type** context)
	{
		return platform_string::strtok(token_string, delim, context);
	}

	template <typename t> FKE_FORCEINLINE
		int32_t c_string_base<t>::get_var_args(char_type* dest, size_t dest_size, const char_type*& fmt, va_list arg_ptr)
	{
		return platform_string::get_var_args(dest, dest_size, fmt, arg_ptr);
	}


	/*-----------------------------------------------------------------------------
		c_string_base<WIDECHAR> specializations
	-----------------------------------------------------------------------------*/
	template <> FKE_FORCEINLINE
		bool c_string_base<widechar_t>::is_pure_ansi(const char_type* str)
	{
		for (; *str; str++)
		{
			if (*str > 0x7f)
			{
				return false;
			}
		}
		return true;
	}


	template <> FKE_FORCEINLINE
		bool c_string_base<widechar_t>::is_pure_ansi(const char_type* str, const size_t StrLen)
	{
		for (size_t Idx = 0; Idx < StrLen; Idx++, str++)
		{
			if (*str > 0x7f)
			{
				return false;
			}
		}
		return true;
	}


	template <>
	inline int32_t c_string_base<widechar_t>::sprintf_impl(char_type* dest, const char_type* fmt, ...)
	{
		int32_t	result = -1;
		FKE_GET_VARARGS_RESULT_WIDE(dest, FKE_MAX_SPRINTF, MAX_SPRINTF - 1, fmt, fmt, result);
		return result;
	}

	template <>
	inline int32_t c_string_base<widechar_t>::snprintf_impl(char_type* dest, int32_t dest_size, const char_type* fmt, ...)
	{
		int32_t	result = -1;
		FKE_GET_VARARGS_RESULT_WIDE(dest, dest_size, dest_size - 1, fmt, fmt, result);
		return result;
	}

	template <>
	FKE_FORCEINLINE bool c_string_base<widechar_t>::to_bool(const widechar_t* str)
	{
		return to_bool_helper::from_c_string_wide(str);
	}

	/*-----------------------------------------------------------------------------
		c_string_base<ansichar_t> specializations
	-----------------------------------------------------------------------------*/
	template <> FKE_FORCEINLINE
		bool c_string_base<ansichar_t>::is_pure_ansi(const char_type* str)
	{
		return true;
	}

	template <> FKE_FORCEINLINE
		bool c_string_base<ansichar_t>::is_pure_ansi(const char_type* str, const size_t StrLen)
	{
		return true;
	}

	template <>
	inline int32_t c_string_base<ansichar_t>::sprintf_impl(char_type* dest, const char_type* fmt, ...)
	{
		int32_t	result = -1;
		FKE_GET_VARARGS_RESULT_ANSI(dest, FKE_MAX_SPRINTF, FKE_MAX_SPRINTF - 1, fmt, fmt, result);
		return result;
	}

	template <>
	inline int32_t c_string_base<ansichar_t>::snprintf_impl(char_type* dest, int32_t dest_size, const char_type* fmt, ...)
	{
		int32_t	result = -1;
		FKE_GET_VARARGS_RESULT_ANSI(dest, dest_size, dest_size - 1, fmt, fmt, result);
		return result;
	}

	template <>
	FKE_FORCEINLINE bool c_string_base<ansichar_t>::to_bool(const ansichar_t* str)
	{
		return to_bool_helper::from_c_string_ansi(str);
	}
}