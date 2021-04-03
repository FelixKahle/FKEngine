// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    namespace fkecore
    {
        template<typename t>
        struct type_tag
        {
            FKE_CONSTEXPR type_tag() = default;
            using type = t;
        };
    }
}