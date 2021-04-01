# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# The public files/sources of the fkeentities module.
set(FKE_TEST_PUBLIC_SOURCES)

# The private files/sources of the fkeentities module.
set(FKE_TEST_PRIVATE_SOURCES
	${FKE_TEST_DIR}/private/main.cpp
)

# Platform specific sources

set(FKE_TEST_WINDOWS_PUBLIC_SOURCES)
set(FKE_TEST_WINDOWS_PRIVATE_SOURCES)

# Compiler specific sources.

set(FKE_TEST_CLANG_PUBLIC_SOURCES)
set(FKE_TEST_CLANG_PRIVATE_SOURCES)
set(FKE_TEST_MSVC_PUBLIC_SOURCES)
set(FKE_TEST_MSVC_PRIVATE_SOURCES)