// Copyright 2021 Felix Kahle. All rights reserved.

#include "generic_platform/generic_platform_stricmp.h"
#include "miscellaneous/char.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		static FKE_CONSTEXPR uint8_t lower_ascii[128] =
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
			0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
			0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
			0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
			0x40, 'a',  'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
			'p',  'q',  'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
			0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
			0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
		};

		template<typename char_type_1, typename char_type_2>
		FKE_FORCEINLINE bool both_ascii(char_type_1 c1, char_type_2 c2)
		{
			return (((uint32_t)c1 | (uint32_t)c2) & 0xffffff80) == 0;
		}

		template<typename char_type_1, typename char_type_2>
		int32_t stricmp_impl(const char_type_1* string1, const char_type_2* string2)
		{
			while (true)
			{
				char_type_1 c1 = *string1++;
				char_type_2 c2 = *string2++;

				// Quickly move on if characters are identical but
				// return equals if we found two null terminators
				if (c1 == c2)
				{
					if (c1)
					{
						continue;
					}

					return 0;
				}
				else if (both_ascii(c1, c2))
				{
					if (int32_t diff = lower_ascii[char_utility<char_type_1>::to_unsigned(c1)] - lower_ascii[char_utility<char_type_2>::to_unsigned(c2)])
					{
						return diff;
					}
				}
				else
				{
					return char_utility<char_type_1>::to_unsigned(c1) - char_utility<char_type_2>::to_unsigned(c2);
				}
			}
		}

		template<typename char_type_1, typename char_type_2>
		int32_t strnicmp_impl(const char_type_1* string1, const char_type_2* string2, size_t count)
		{
			for (; count > 0; --count)
			{
				char_type_1 c1 = *string1++;
				char_type_1 c2 = *string2++;

				// Quickly move on if characters are identical but
				// return equals if we found two null terminators
				if (c1 == c2)
				{
					if (c1)
					{
						continue;
					}

					return 0;
				}
				else if (both_ascii(c1, c2))
				{
					if (int32_t diff = lower_ascii[char_utility<char_type_1>::to_unsigned(c1)] - lower_ascii[char_utility<char_type_2>::to_unsigned(c2)])
					{
						return diff;
					}
				}
				else
				{
					return char_utility<char_type_1>::to_unsigned(c1) - char_utility<char_type_2>::to_unsigned(c2);
				}
			}

			return 0;
		}

		int32_t generic_platform_stricmp::stricmp(const ansichar_t* str1, const ansichar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const widechar_t* str1, const widechar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf8char_t* str1, const utf8char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf16char_t* str1, const utf16char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf32char_t* str1, const utf32char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const ansichar_t* str1, const widechar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const ansichar_t* str1, const utf8char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const ansichar_t* str1, const utf16char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const ansichar_t* str1, const utf32char_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const widechar_t* str1, const ansichar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf8char_t* str1, const ansichar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf16char_t* str1, const ansichar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::stricmp(const utf32char_t* str1, const ansichar_t* str2) { return stricmp_impl(str1, str2); }
		int32_t generic_platform_stricmp::strnicmp(const ansichar_t* str1, const ansichar_t* str2, size_t count) { return strnicmp_impl(str1, str2, count); }
		int32_t generic_platform_stricmp::strnicmp(const widechar_t* str1, const widechar_t* str2, size_t count) { return strnicmp_impl(str1, str2, count); }
		int32_t generic_platform_stricmp::strnicmp(const ansichar_t* str1, const widechar_t* str2, size_t count) { return strnicmp_impl(str1, str2, count); }
		int32_t generic_platform_stricmp::strnicmp(const widechar_t* str1, const ansichar_t* str2, size_t count) { return strnicmp_impl(str1, str2, count); }
	}
}