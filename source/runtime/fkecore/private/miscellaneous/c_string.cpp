// Copyright 2021 Felix Kahle.All rights reserved.

#include "fkecore_types.h"
#include "miscellaneous/c_string.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		// 4 lines of 64 chars each, plus a null terminator
		template <>
		FKECORE_API const ansichar_t c_string_spc_helper<ansichar_t>::spc_array[c_string_spc_helper::max_spaces + 1] =
			FKE_ANSI_TEXT("                                                                ")
			FKE_ANSI_TEXT("                                                                ")
			FKE_ANSI_TEXT("                                                                ")
			FKE_ANSI_TEXT("                                                               ");

		template <>
		FKECORE_API const widechar_t c_string_spc_helper<widechar_t>::spc_array[c_string_spc_helper::max_spaces + 1] =
			FKE_WIDE_TEXT("                                                                ")
			FKE_WIDE_TEXT("                                                                ")
			FKE_WIDE_TEXT("                                                                ")
			FKE_WIDE_TEXT("                                                               ");

		template <>
		FKECORE_API const ansichar_t c_string_spc_helper<ansichar_t>::tab_array[max_tabs + 1] =
			FKE_ANSI_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_ANSI_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_ANSI_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_ANSI_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

		template <>
		FKECORE_API const widechar_t c_string_spc_helper<widechar_t>::tab_array[max_tabs + 1] =
			FKE_WIDE_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_WIDE_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_WIDE_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			FKE_WIDE_TEXT("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

		bool to_bool_helper::from_c_string_ansi(const ansichar_t* in_string)
		{
			if (c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("true")) == 0 || c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("yes")) == 0 || c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("on")) == 0)
			{
				return true;
			}
			else if (c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("false")) == 0 || c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("no")) == 0 || c_string_ansi::stricmp(in_string, FKE_ANSI_TEXT("off")) == 0)
			{
				return false;
			}
			else
			{
				return c_string_ansi::atoi(in_string) ? true : false;
			}
		}

		bool to_bool_helper::from_c_string_wide(const widechar_t* in_string)
		{
			if (c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("true")) == 0 || c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("yes")) == 0 || c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("on")) == 0)
			{
				return true;
			}
			else if (c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("false")) == 0 || c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("no")) == 0 || c_string_wide::stricmp(in_string, FKE_WIDE_TEXT("off")) == 0)
			{
				return false;
			}
			else
			{
				return c_string_wide::atoi(in_string) ? true : false;
			}
		}
	}
}