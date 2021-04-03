// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "container/compile_time_string.h"
#include "hash/hash.h"
#include "algorithm/equal_range.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	namespace fkecore
	{
		/**
		 * Contains name filter functions.
		 * Primarily meant to be used by the compile-time type info
		 */
		template<typename char_type>
		struct name_filters;

		template<>
		struct name_filters<ansichar_t>
		{
			FKE_STATIC_STRUCT(name_filters)


			static FKE_CONSTEXPR compile_time_ansi_string filter_prefix(const compile_time_ansi_string& str, const compile_time_ansi_string& prefix)
			{
				return str.size() >= prefix.size() ? (str(0, prefix.size()) == prefix ? str(prefix.size(), str.size()) : str) : str;
			}

			static FKE_CONSTEXPR compile_time_ansi_string leftpad(const compile_time_ansi_string& str)
			{
				return (str.size() > 0 && str[0] == ' ') ? leftpad(str(1, str.size())) : str;
			}

			static FKE_CONSTEXPR compile_time_ansi_string filter_class(const compile_time_ansi_string& type_name)
			{
				return leftpad(filter_prefix(leftpad(type_name), "class"));
			}

			static FKE_CONSTEXPR compile_time_ansi_string filter_struct(const compile_time_ansi_string& type_name)
			{
				return leftpad(filter_prefix(leftpad(type_name), "struct"));
			}

			static FKE_CONSTEXPR compile_time_ansi_string filter_typename_prefix(const compile_time_ansi_string& type_name)
			{
				return filter_struct(filter_class(type_name));
			}

			static FKE_CONSTEXPR const ansichar_t* find_ith(const compile_time_ansi_string& name, const compile_time_ansi_string& substring, std::size_t i)
			{
				return find_ith_impl(name, substring, name.end(), i);
			}

			static FKE_CONSTEXPR const ansichar_t* find_last(const compile_time_ansi_string& name, const compile_time_ansi_string& substring)
			{
				return find_ith_impl(name, substring, name.end(), -1, true);
			}

			static FKE_CONSTEXPR const ansichar_t* find(const compile_time_ansi_string& name, const compile_time_ansi_string& substring)
			{
				return find_ith(name, substring, 0);
			}

		private:

			static FKE_CONSTEXPR const ansichar_t* find_ith_impl(const compile_time_ansi_string& name, const compile_time_ansi_string& substring, const ansichar_t* res, std::size_t i, bool infinite = false)
			{
				return (name.length() >= substring.length()) ?
					((name(0, substring.length()) == substring) ?
						((i == 0) ?
							name.begin()
							:
							find_ith_impl(name(substring.length(), name.length()), substring, name.begin(), i - 1, infinite))
						:
						find_ith_impl(name(1, name.length()), substring, res, i, infinite))
					:
					(!infinite) ? name.end() : res;
			}
		};

		template<>
		struct name_filters<widechar_t>
		{
			FKE_STATIC_STRUCT(name_filters)


				static FKE_CONSTEXPR compile_time_wide_string filter_prefix(const compile_time_wide_string& str, const compile_time_wide_string& prefix)
			{
				return str.size() >= prefix.size() ? (str(0, prefix.size()) == prefix ? str(prefix.size(), str.size()) : str) : str;
			}

			static FKE_CONSTEXPR compile_time_wide_string leftpad(const compile_time_wide_string& str)
			{
				return (str.size() > 0 && str[0] == ' ') ? leftpad(str(1, str.size())) : str;
			}

			static FKE_CONSTEXPR compile_time_wide_string filter_class(const compile_time_wide_string& type_name)
			{
				return leftpad(filter_prefix(leftpad(type_name), FKE_WIDE_TEXT("class")));
			}

			static FKE_CONSTEXPR compile_time_wide_string filter_struct(const compile_time_wide_string& type_name)
			{
				return leftpad(filter_prefix(leftpad(type_name), FKE_WIDE_TEXT("struct")));
			}

			static FKE_CONSTEXPR compile_time_wide_string filter_typename_prefix(const compile_time_wide_string& type_name)
			{
				return filter_struct(filter_class(type_name));
			}

			static FKE_CONSTEXPR const widechar_t* find_ith(const compile_time_wide_string& name, const compile_time_wide_string& substring, size_t i)
			{
				return find_ith_impl(name, substring, name.end(), i);
			}

			static FKE_CONSTEXPR const widechar_t* find_last(const compile_time_wide_string& name, const compile_time_wide_string& substring)
			{
				return find_ith_impl(name, substring, name.end(), -1, true);
			}

			static FKE_CONSTEXPR const widechar_t* find(const compile_time_wide_string& name, const compile_time_wide_string& substring)
			{
				return find_ith(name, substring, 0);
			}

		private:

			static FKE_CONSTEXPR const widechar_t* find_ith_impl(const compile_time_wide_string& name, const compile_time_wide_string& substring, const widechar_t* res, size_t i, bool infinite = false)
			{
				return (name.length() >= substring.length()) ?
					((name(0, substring.length()) == substring) ?
						((i == 0) ?
							name.begin()
							:
							find_ith_impl(name(substring.length(), name.length()), substring, name.begin(), i - 1, infinite))
						:
						find_ith_impl(name(1, name.length()), substring, res, i, infinite))
					:
					(!infinite) ? name.end() : res;
			}
		};
	}
}