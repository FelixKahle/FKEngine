// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include <miscellaneous/standard_library_include.h>
#include "templates/fkengine_template.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace scope_exit_support
	{
		/**
		 * Not meant for direct consumption : use FKE_ON_SCOPE_EXIT instead.
		 *
		 * RAII class that calls a lambda when it is destroyed.
		 */
		template <typename func_type>
		class scope_guard : public noncopyable
		{
		public:
			// Given a lambda, constructs an RAII scope guard.
			explicit scope_guard(func_type&& in_func)
				: func(move(in_func))
			{
			}

			// This constructor needs to be available for the code to compile.
			// It will be almost definitely be RVOed out (even in DEBUG).
			scope_guard(scope_guard&& other)
				: func(move(other.func))
			{
				other.func.reset();
			}

			// Causes
			~scope_guard()
			{
				if (func.has_value())
				{
					func.value()();
				}
			}

		private:
			// The lambda to be executed when this guard goes out of scope.
			optional<func_type> func;
		};

		struct scope_guard_syntax_support
		{
			template <typename func_type>
			scope_guard<func_type> operator+(func_type&& in_func)
			{
				return scope_guard<func_type>(forward<func_type>(in_func));
			}
		};
	}
}

#define FKE_ON_SCOPE_EXIT const auto FKE_ANONYMOUS_VARIABLE(scope_guard_) = ::fkengine::scope_exit_support::scope_guard_syntax_support() + [&]()