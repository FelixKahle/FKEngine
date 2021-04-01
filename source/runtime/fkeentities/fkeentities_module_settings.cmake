# Copyright 2019 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# The version of the fkeentities module.
set(FKE_ENTITIES_VERSION 0.0.0.1)

# The link type of the fkeentities module. (STATIC = static linking, SHARED = dynamic linking, MODULE = load at runtime).
# The fkeentities module should never be MODULE, because that would not be performant.
set(FKE_ENTITIES_LINK_TYPE SHARED)

# The dependencies.
set(FKE_ENTITIES_DEPENDENCIES fkecore)