// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore.h"
#include "fkeentities_module.h"
#include "types/types_forward.h"
#include "types/entity.h"
#include "types/shared_component_values.h"

#define FKE_BLOCK_MEMORY_16K 16384
#define FKE_BLOCK_MEMORY_8K 8192

namespace fkengine
{
    namespace fkeentities
    {
        enum class chunk_flags
        {
            none = 0,
            unused_0 = 1 << 0,
            unused_1 = 1 << 1,
            temp_assert_will_destroy_all_in_linked_entity_group = 1 << 2
        };
    }
}