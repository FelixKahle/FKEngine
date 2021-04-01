// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "templates/is_character.h"
#include "miscellaneous/standard_library_include.h"
#include "hash/hash.h"
#include "algorithm/equal_range.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    /**
     * A string which gets evaluated at compile time.
     * 
     * @tparam char_type - The underlying character type to use. Has to be a character type.
     */
	template<typename char_type, typename = typename enable_if<is_character<char_type>::value, char_type>>
	class basic_compile_time_string
	{
    public:
        template<size_t n>
        FKE_CONSTEXPR basic_compile_time_string(const char_type(&str)[n]) :
            basic_compile_time_string{ &str[0], n - 1 }
        {}

        FKE_CONSTEXPR basic_compile_time_string(const char_type* begin, size_t length) :
            actual_string{ begin },
            string_length{ length }
        {}

        FKE_CONSTEXPR basic_compile_time_string(const char_type* begin, const char_type* end) :
            basic_compile_time_string{ begin, static_cast<size_t>(end - begin) }
        {}

        FKE_CONSTEXPR basic_compile_time_string(const char_type* begin) :
            basic_compile_time_string{ begin, length(begin) }
        {}

        static FKE_CONSTEXPR size_t length(const char_type* str)
        {
            return *str ? 1 + length(str + 1) : 0;
        }

        FKE_CONSTEXPR size_t length() const
        {
            return string_length;
        }

        FKE_CONSTEXPR size_t size() const
        {
            return length();
        }

        FKE_CONSTEXPR uint64_t hash() const
        {
            return hashing::fnv1a_hash<char_type, uint64_t>(length(), begin());
        }

        typename conditional<is_same<char_type, widechar_t>::value, wide_string, ansi_string>::type cppstring() const
        {
            return { begin(), end() };
        }

        typename conditional<is_same<char_type, widechar_t>::value, wide_string, ansi_string>::type str() const
        {
            return cppstring();
        }

        FKE_CONSTEXPR const char_type* begin() const
        {
            return actual_string;
        }

        FKE_CONSTEXPR const char_type* end() const
        {
            return actual_string + string_length;
        }

        FKE_CONSTEXPR char_type operator[](size_t i) const
        {
            return actual_string[i];
        }

        FKE_CONSTEXPR const char_type* operator()(size_t i) const
        {
            return actual_string + i;
        }

        FKE_CONSTEXPR basic_compile_time_string operator()(size_t begin, size_t end) const
        {
            return { actual_string + begin, actual_string + end };
        }

        FKE_CONSTEXPR basic_compile_time_string pad(size_t begin_offset, size_t end_offset) const
        {
            return operator()(begin_offset, size() - end_offset);
        }

    private:
        const char_type* actual_string;
        size_t string_length;
	};

    template<typename char_type>
    FKE_CONSTEXPR bool operator==(const basic_compile_time_string<char_type>& lhs, const basic_compile_time_string<char_type>& rhs)
    {
        return algorithm::equal_range(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<typename char_type>
    FKE_CONSTEXPR bool operator!=(const basic_compile_time_string<char_type>& lhs, const basic_compile_time_string<char_type>& rhs)
    {
        return !(lhs == rhs);
    }

    typedef basic_compile_time_string<char_t> compile_time_char_t_string;
    typedef basic_compile_time_string<widechar_t> compile_time_wide_string;
    typedef basic_compile_time_string<ansichar_t> compile_time_ansi_string;
}