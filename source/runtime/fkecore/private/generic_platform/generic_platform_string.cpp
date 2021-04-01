// Copyright 2021 Felix Kahle. All rights reserved.

#include "generic_platform/generic_platform_string.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	template <> const char_t* generic_platform_string::get_encoding_type_name<ansichar_t>() { return FKE_TEXT("ANSICHAR"); }
	template <> const char_t* generic_platform_string::get_encoding_type_name<widechar_t>() { return FKE_TEXT("WIDECHAR"); }
	template <> const char_t* generic_platform_string::get_encoding_type_name<ucs2char_t>() { return FKE_TEXT("UCS2CHAR"); }
#if FKE_PLATFORM_TCHAR_IS_CHAR16
	template <> const char_t* generic_platform_string::get_encoding_type_name<wchar_t>() { return FKE_TEXT("WCHAR_T"); }
#endif
}