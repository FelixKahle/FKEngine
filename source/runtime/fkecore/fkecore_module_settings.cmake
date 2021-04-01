# Copyright 2019 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# The version of the fkecore module.
set(FKE_CORE_VERSION 0.0.0.1)

# The link type of the fkecore module. (STATIC = static linking, SHARED = dynamic linking, MODULE = load at runtime).
# The fkecore module should never be MODULE, because that would not be performant.
# The best option is STATIC. SHARED is an option too, if there is a need to run many programs that rely on that module.
set(FKE_CORE_LINK_TYPE SHARED)