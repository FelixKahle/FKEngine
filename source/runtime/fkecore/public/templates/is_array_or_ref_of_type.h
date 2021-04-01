// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

/** The namespace of the FKEngine. */
namespace fkengine
{
	/**
	 * Type trait which returns true if the type T is an array or a reference to an array of arr_type.
	 */
	template <typename t, typename arr_type>
	struct is_array_or_ref_of_type
	{
		enum { value = false };
	};

	template <typename arr_type> struct is_array_or_ref_of_type<               arr_type[], arr_type> { enum { value = true }; };
	template <typename arr_type> struct is_array_or_ref_of_type<const          arr_type[], arr_type> { enum { value = true }; };
	template <typename arr_type> struct is_array_or_ref_of_type<      volatile arr_type[], arr_type> { enum { value = true }; };
	template <typename arr_type> struct is_array_or_ref_of_type<const volatile arr_type[], arr_type> { enum { value = true }; };

	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<               arr_type[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<const          arr_type[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<      volatile arr_type[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<const volatile arr_type[n], arr_type> { enum { value = true }; };

	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<               arr_type(&)[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<const          arr_type(&)[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<      volatile arr_type(&)[n], arr_type> { enum { value = true }; };
	template <typename arr_type, unsigned int n> struct is_array_or_ref_of_type<const volatile arr_type(&)[n], arr_type> { enum { value = true }; };
}