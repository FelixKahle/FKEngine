// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"
#include "generic_platform/generic_platform_stricmp.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		/**
		 * Generic string implementation for most platforms
		 */
		struct generic_platform_string : public generic_platform_stricmp
		{
			FKE_STATIC_STRUCT(generic_platform_string)

				template <typename encoding>
			static bool is_valid_char(encoding Ch)
			{
				return true;
			}

			template <typename dest_encoding, typename source_encoding>
			static bool can_convert_char(source_encoding ch)
			{
				return is_valid_char(ch) && (source_encoding)(dest_encoding)ch == ch && is_valid_char((dest_encoding)ch);
			}

			template <typename encoding>
			static const char_t* get_encoding_type_name();

			static const ansichar_t* get_encoding_name()
			{
#if FKE_PLATFORM_TCHAR_IS_4_BYTES
				return "UTF-32LE";
#else
				return "UTF-16LE";
#endif
			}

			static FKE_CONSTEXPR bool is_unicode_encoded = FKE_UNICODE;

			template <bool dummy, typename t>
			struct is_fixed_width_encoding_helper
			{
				enum { value = false };
			};

			template <bool dummy> struct is_fixed_width_encoding_helper<dummy, ansichar_t> { enum { value = true }; };
			template <bool dummy> struct is_fixed_width_encoding_helper<dummy, widechar_t> { enum { value = true }; };
			template <bool dummy> struct is_fixed_width_encoding_helper<dummy, ucs2char_t> { enum { value = true }; };
#if FKE_PLATFORM_TCHAR_IS_CHAR16
			template <bool dummy> struct is_fixed_width_encoding_helper<dummy, wchar_t> { enum { value = true }; };
#endif

			template <typename t>
			struct is_fixed_width_encoding : is_fixed_width_encoding_helper<false, t>
			{
			};

			template <typename encoding_a, typename encoding_b>
			struct are_encodings_compatible
			{
				enum { value = is_fixed_width_encoding<encoding_a>::value && is_fixed_width_encoding<encoding_b>::value && sizeof(encoding_a) == sizeof(encoding_b) };
			};

			template <typename source_encoding, typename dest_encoding>
			static FKE_FORCEINLINE typename enable_if<are_encodings_compatible<source_encoding, dest_encoding>::value, dest_encoding*>::type Convert(dest_encoding* dest, int32_t dest_size, const source_encoding* src, int32_t src_size, dest_encoding bogus_char = (dest_encoding)'?')
			{
				if (dest_size < src_size)
				{
					return nullptr;
				}

				return (dest_encoding*)memcpy(dest, src, src_size * sizeof(source_encoding)) + src_size;
			}

			template <typename source_encoding, typename dest_encoding>
			static typename enable_if<!are_encodings_compatible<source_encoding, dest_encoding>::value&& is_fixed_width_encoding<source_encoding>::value, dest_encoding*>::type convert(dest_encoding* dest, int32_t dest_size, const source_encoding* src, int32_t src_size, dest_encoding bogus_char = (dest_encoding)'?')
			{
				const int32_t size_t = dest_size <= src_size ? dest_size : src_size;
				bool invalid_chars = false;
				for (int i = 0; i < size_t; ++i)
				{
					source_encoding src_ch = src[i];
					dest[i] = (dest_encoding)src_ch;
					invalid_chars |= !can_convert_char<dest_encoding>(src_ch);
				}

				if (invalid_chars)
				{
					for (int i = 0; i < size_t; ++i)
					{
						if (!can_convert_char<dest_encoding>(src[i]))
						{
							dest[i] = bogus_char;
						}
					}

					// log_bogus_chars<dest_encoding>(src, size_t);
				}

				return dest_size < src_size ? nullptr : dest + size_t;
			}

			template <typename dest_encoding, typename source_encoding>
			static typename enable_if<is_fixed_width_encoding<source_encoding>::value&& is_fixed_width_encoding<dest_encoding>::value, int32_t>::type converted_length(const source_encoding* src, int32_t src_size)
			{
				return src_size;
			}
		};

		template <>
		inline bool generic_platform_string::is_valid_char<ansichar_t>(ansichar_t ch)
		{
			return ch >= 0x00 && ch <= 0x7F;
		}
	}
}