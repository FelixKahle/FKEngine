// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "traits/int_type.h"
#include <ctype.h>
#include <wctype.h>
#include <type_traits>

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		/**
		 * Templated literal struct to allow selection of wide or ansi string literals
		 * based on the character type provided, and not on compiler switches.
		 */
		template <typename T> struct literal_selection
		{
			FKE_STATIC_STRUCT(literal_selection)

				static const ansichar_t select(const ansichar_t ansi, const widechar_t) { return ansi; }
			static const ansichar_t* select(const ansichar_t* ansi, const widechar_t*) { return ansi; }
		};

		template <> struct literal_selection<widechar_t>
		{
			FKE_STATIC_STRUCT(literal_selection)

				static const widechar_t select(const ansichar_t, const widechar_t  wide) { return wide; }
			static const widechar_t* select(const ansichar_t*, const widechar_t* wide) { return wide; }
		};

#define FKE_LITERAL(char_type, string_literal) fkengine::fkecore::literal_selection<char_type>::Select(string_literal, FKE_WIDE_TEXT(string_literal))


		template <typename char_type, const unsigned int t_size>
		struct char_utility_base
		{
			FKE_STATIC_STRUCT(char_utility_base)

				static constexpr char_type line_feed = 0xa;
			static constexpr char_type vertical_tab = 0xb;
			static constexpr char_type form_feed = 0xc;
			static constexpr char_type carriage_return = 0xd;
			static constexpr char_type next_line = 0x85;
			static constexpr char_type line_separator = 0x2028;
			static constexpr char_type paragraph_separator = 0x2029;

			static bool is_linebreak(char_type in_char)
			{
				return ((uint32_t(in_char) - line_feed) <= uint32_t(carriage_return - line_feed)) | (in_char == next_line) | (in_char == line_separator) | (in_char == paragraph_separator);
			}

		};

		template <typename char_type>
		struct char_utility_base<char_type, 1>
		{
			FKE_STATIC_STRUCT(char_utility_base)

				static constexpr char_type line_feed = 0xa;
			static constexpr char_type vertical_tab = 0xb;
			static constexpr char_type form_feed = 0xc;
			static constexpr char_type carriage_return = 0xd;

			static bool is_linebreak(char_type in_char)
			{
				return ((uint32_t(in_char) - line_feed) <= uint32_t(carriage_return - line_feed));
			}
		};

		template <typename char_type>
		struct char_utility : char_utility_base<char_type, sizeof(char_type)>
		{
			FKE_STATIC_STRUCT(char_utility)

				/**
				 * Only converts ASCII characters, same as CRT to[w]upper() with standard C locale.
				 */
				static char_type to_upper(char_type in_char)
			{
				return ToUnsigned(in_char) - ((uint32_t(in_char) - 'a' < 26u) << 5);
			}

			/**
			 * Only converts ASCII characters, same as CRT to[w]upper() with standard C locale.
			 */
			static char_type to_lower(char_type in_char)
			{
				return to_unsigned(in_char) + ((uint32_t(in_char) - 'A' < 26u) << 5);
			}

			static bool is_upper(char_type in_char);
			static bool is_lower(char_type in_char);
			static bool is_alpha(char_type in_char);
			static bool is_graph(char_type in_char);
			static bool is_print(char_type in_char);
			static bool is_punct(char_type in_char);
			static bool is_alnum(char_type in_char);
			static bool is_digit(char_type in_char);
			static bool is_hex_digit(char_type in_char);
			static bool is_whitespace(char_type in_char);

			static bool is_oct_digit(char_type in_char)
			{
				return uint32_t(in_char) - '0' < 8u;
			}

			static int32_t convertin_char_digit_to_int(char_type in_char)
			{
				return static_cast<int32_t>(in_char) - static_cast<int32_t>('0');
			}

			static bool is_identifier(char_type in_char)
			{
				return is_alnum(in_char) || is_underscore(in_char);
			}

			static bool is_underscore(char_type in_char)
			{
				return in_char == FKE_LITERAL(char_type, '_');
			}

			/**
			 * Avoid sign extension problems with signed characters smaller than int
			 *
			 * E.g. 'Ö' - 'A' is negative since the char 'Ö' (0xD6) is negative and gets
			 * sign-extended to the 32-bit int 0xFFFFFFD6 before subtraction happens.
			 *
			 * Mainly needed for subtraction and addition.
			 */
			static constexpr FKE_FORCEINLINE uint32_t to_unsigned(char_type in_char)
			{
				return (typename unsigned_int_type<sizeof(char_type)>::type)in_char;
			}
		};

		typedef char_utility<char_t> char_utility_tchar;
		typedef char_utility<widechar_t> char_utility_wide;
		typedef char_utility<ansichar_t> char_utility_ansi;

		template <> inline bool char_utility<widechar_t>::is_upper(widechar_t in_char) { return ::iswupper(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_lower(widechar_t in_char) { return ::iswlower(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_alpha(widechar_t in_char) { return ::iswalpha(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_graph(widechar_t in_char) { return ::iswgraph(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_print(widechar_t in_char) { return ::iswprint(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_punct(widechar_t in_char) { return ::iswpunct(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_alnum(widechar_t in_char) { return ::iswalnum(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_digit(widechar_t in_char) { return ::iswdigit(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_hex_digit(widechar_t in_char) { return ::iswxdigit(in_char) != 0; }
		template <> inline bool char_utility<widechar_t>::is_whitespace(widechar_t in_char) { return ::iswspace(in_char) != 0; }

		template <> inline bool char_utility<ansichar_t>::is_upper(ansichar_t in_char) { return ::isupper((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_lower(ansichar_t in_char) { return ::islower((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_alpha(ansichar_t in_char) { return ::isalpha((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_graph(ansichar_t in_char) { return ::isgraph((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_print(ansichar_t in_char) { return ::isprint((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_punct(ansichar_t in_char) { return ::ispunct((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_alnum(ansichar_t in_char) { return ::isalnum((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_digit(ansichar_t in_char) { return ::isdigit((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_hex_digit(ansichar_t in_char) { return ::isxdigit((unsigned char)in_char) != 0; }
		template <> inline bool char_utility<ansichar_t>::is_whitespace(ansichar_t in_char) { return ::isspace((unsigned char)in_char) != 0; }
	}
}