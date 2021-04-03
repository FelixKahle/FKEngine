// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "miscellaneous/standard_library_include.h"

#define FKE_NAME_NONE FKE_TEXT("")

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		/** Base class for all log categories. **/
		struct FKECORE_API log_category
		{
			log_category(const char_t_string& name)
				: category_name(name)
			{}

			const char_t_string& get_name() const
			{
				return category_name;
			}

		private:

			char_t_string category_name;
		};
	}
}