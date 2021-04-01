// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"
#include "templates/is_character.h"
#include <iomanip>

/** The namespace of the FKEngine. */
namespace fkengine
{
	/** Contains for function to convert time points to strings. */
	struct FKECORE_API time_conversation
	{
		FKE_STATIC_STRUCT(time_conversation)

		template<typename char_type>
		static basic_string<char_type> time_point_to_string(const chrono::system_clock::time_point& time, const char_t* format)
		{
			time_t tt = chrono::system_clock::to_time_t(time);
			tm tm;
			gmtime_s(&tm, &tt); // GMT(UTC)
			basic_stringstream<char_type, char_traits<char_type>, allocator<char_type>> ss;
			ss << put_time<char_type>(&tm, format);
			return ss.str();
		}
	};
}