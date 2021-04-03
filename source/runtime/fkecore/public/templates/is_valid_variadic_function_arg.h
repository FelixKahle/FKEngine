// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "miscellaneous/standard_library_include.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		/**
		 * Tests if a type is a valid argument to a variadic function, e.g. printf.
		 */
		template <typename t, bool = is_enum<t>::value>
		struct is_valid_variadic_function_arg
		{
		private:
			static uint32_t tester(uint32_t);
			static uint32_t tester(uint8_t);
			static uint32_t tester(int32_t);
			static uint32_t tester(uint64_t);
			static uint32_t tester(int64_t);
			static uint32_t tester(double);
			static uint32_t tester(long);
			static uint32_t tester(unsigned long);
			static uint32_t tester(char_t);
			static uint32_t tester(bool);
			static uint32_t tester(const void*);
			static uint8_t  tester(...);

			static t decl_val_t();

		public:
			enum { value = sizeof(tester(decl_val_t())) == sizeof(uint32_t) };
		};

		template <typename t>
		struct is_valid_variadic_function_arg<t, true>
		{
			enum { value = true };
		};
	}
}