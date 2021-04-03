// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    namespace fkecore
    {
        /** Contains algorithm functions. */
        namespace algorithm
        {
            /**
             * Compares a range for equality.
             *
             * @tparam lhs_it - Left hand side type.
             * @tparam rhs_it - Right hand side type.
             *
             * @param lhs_begin - Begin of the left hand side range.
             * @param lhs_end - End of the left hand side range.
             * @param rhs_begin - Begin of the right hand side range.
             * @param rhs_end - End of the right hand side range.
             *
             * @return - True, if the two ranges are equal, false otherwise.
             */
            template<typename lhs_it, typename rhs_it>
            FKE_CONSTEXPR bool equal_range(lhs_it lhs_begin, lhs_it lhs_end, rhs_it rhs_begin, rhs_it rhs_end)
            {
                return (lhs_begin != lhs_end && rhs_begin != rhs_begin) ? *lhs_begin == *rhs_begin &&
                    equal_range(lhs_begin + 1, lhs_end, rhs_begin + 1, rhs_end) : (lhs_begin == lhs_end && rhs_begin == rhs_end);
            }
        }
    }
}