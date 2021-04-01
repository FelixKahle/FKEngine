# Copyright 2021 Felix Kahle. All rights reserved.

# The general build instructions for the FKEngine.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Include platform.
include(tools/cmake/platform.cmake)

# Check Compiler.
include(tools/cmake/compiler.cmake)

# Build configuration.
include(tools/cmake/configuration.cmake)

# Include the definitions.
include(tools/CMake/definitions.cmake)

# Print out some information about the buidling progress.
fkemessage(STATUS "Load modules...")

# Include the modules.
include(tools/cmake/modules.cmake)

# Build the test.
add_subdirectory(${FKENGINE_SOURCE_DIR}/fketest)

# Print line - the FKEngine build system ends here.
fkeseperateline()