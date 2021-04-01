# Copyright 2021 Felix Kahle. All rights reserved.

# Current compiler.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Get the compiler and set the FKE_COMPILER variable.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(FKE_COMPILER "Clang")
	add_compile_definitions(FKE_PLATFORM_COMPILER_CLANG=1)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(FKE_COMPILER "GCC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
	set(FKE_COMPILER "Intel")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(FKE_COMPILER "MSVC")
	include(tools/cmake/compiler/msvc_compiler.cmake)
endif()

# Print out some information about the configuration and the platform.
fkemessage(STATUS "The compiler is: ${FKE_COMPILER}")