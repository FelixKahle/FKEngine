// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    /** 
     * Static value. 
     * 
     * @tparam t - The type of the static value.
     * @tparam val - The value of the static value.
     */
    template<typename t, t val>
    struct static_value
    {
        FKE_CONSTEXPR static_value() = default;
        using value_type = t;
        static FKE_CONSTEXPR value_type value = val;

        FKE_CONSTEXPR operator value_type() const
        {
            return val;
        }

        FKE_CONSTEXPR value_type get() const
        {
            return val;
        }

        friend FKE_CONSTEXPR bool operator==(const static_value& lhs, const value_type rhs)
        {
            return lhs.get() == rhs;
        }

        friend FKE_CONSTEXPR bool operator==(const value_type lhs, const static_value& rhs)
        {
            return rhs == lhs;
        }

        friend FKE_CONSTEXPR bool operator!=(const static_value& lhs, const value_type rhs)
        {
            return !(lhs == rhs);
        }

        friend FKE_CONSTEXPR bool operator!=(const value_type lhs, const static_value& rhs)
        {
            return !(lhs == rhs);
        }
    };

    template<typename t, t val>
    FKE_CONSTEXPR t static_value<t, val>::value;
}