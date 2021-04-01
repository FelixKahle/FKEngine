# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Confirm that the PLATFORM_NAME macro is defined,
# throw an error otherwise.
if (NOT DEFINED PLATFORM_NAME)
	fkemessage(FATAL_ERROR "PLATFORM_NAME was not set. It has to be set in a toolchain file.")
endif()

# Print out some information about the buidling progress.
fkemessage(STATUS "The platform is: ${PLATFORM_NAME}")