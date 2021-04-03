// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    namespace fkecore
    {
        /**
         * Type trait which yields a signed integer type of a given number of bytes.
         * If there is no such type, the Type member type will be absent, allowing it to be used in SFINAE contexts.
         */
        template <int num_bytes>
        struct signed_int_type
        {
        };

        template <> struct signed_int_type<1> { using type = int8_t; };
        template <> struct signed_int_type<2> { using type = int16_t; };
        template <> struct signed_int_type<4> { using type = int32_t; };
        template <> struct signed_int_type<8> { using type = int64_t; };

        /**
         * Helper for signed_int_type which expands out to the nested Type.
         */
        template <int num_bytes>
        using signed_int_type_T = typename signed_int_type<num_bytes>::type;


        /**
         * Type trait which yields an unsigned integer type of a given number of bytes.
         * If there is no such type, the Type member type will be absent, allowing it to be used in SFINAE contexts.
         */
        template <int num_bytes>
        struct unsigned_int_type
        {
        };

        template <> struct unsigned_int_type<1> { using type = uint8_t; };
        template <> struct unsigned_int_type<2> { using type = uint16_t; };
        template <> struct unsigned_int_type<4> { using type = uint32_t; };
        template <> struct unsigned_int_type<8> { using type = uint64_t; };

        /**
         * Helper for unsigned_int_type which expands out to the nested Type.
         */
        template <int num_bytes>
        using unsigned_int_type_T = typename unsigned_int_type<num_bytes>::type;
    }
}