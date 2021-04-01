// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "templates/is_character.h"
#include "miscellaneous/standard_library_include.h"

// TODO: Implement support for non uint64_t type hashes.

/** FNV basis uint64_t. */
#define FKE_FNV_BASIS 14695981039346656037ull

/** FNV prime uint64_t. */
#define FKE_FNV_PRIME 1099511628211ull

/** The namespace of the FKEngine. */
namespace fkengine
{
    /** Contains hash functions. */
    struct hashing
    {
        FKE_STATIC_STRUCT(hashing)

        /**
         * Computes a hash.
         * If its possible, the hash is computed during compile time.
         * 
         * @tparam char_type - The character type to use.
         * @tparam hash_type - The hash type to use.
         * @param n - n.
         * @param str - The string to compute the hash from.
         * @param hash - Hash. 14695981039346656037ull default.
         */
        template<typename char_type = char_t, typename hash_type = uint64_t, typename = typename enable_if<is_arithmetic<hash_type>::value && is_character<char_type>::value, hash_type>::type>
        static FKE_CONSTEXPR hash_type fnv1a_hash(size_t n, const char_type* str, hash_type hash = FKE_FNV_BASIS)
        {
            static_assert(is_same<hash_type, uint64_t>::value, "Currently are only uint64_t hashes are supported.");
            return n > 0 ? fnv1a_hash(n - 1, str + 1, (hash ^ *str) * FKE_FNV_PRIME) : hash;
        }

        /**
         * Computes a hash.
         * If its possible, the hash is computed during compile time.
         * 
         * @tparam n - N.
         * @tparam char_type - The character type to use.
         * @tparam hash_type - The hash type to use.
         * @param array - The array to compute the hash from.
         */
        template<size_t n, typename char_type = char_t, typename hash_type = uint64_t, typename = typename enable_if<is_arithmetic<hash_type>::value&& is_character<char_type>::value, hash_type>::type>
        static FKE_CONSTEXPR hash_type fnv1a_hash(const char_type(&array)[n])
        {
            static_assert(is_same<hash_type, uint64_t>::value, "Currently are only uint64_t hashes are supported.");
            return fnv1a_hash<char_type, hash_type>(n - 1, &array[0]);
        }
    };
}