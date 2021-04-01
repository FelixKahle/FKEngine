# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Print out some information about the buidling progress.
fkemessage(STATUS "The configuration of the build is: ${FKENGINE_CONFIGURATION}")

if (${FKENGINE_CONFIGURATION} STREQUAL "Shipping")
	add_compile_definitions(FKE_BUILD_SHIPPING=1)
elseif(${FKENGINE_CONFIGURATION} STREQUAL "Development")
	add_compile_definitions(FKE_BUILD_DEVELOPMENT=1)
elseif(${FKENGINE_CONFIGURATION} STREQUAL "Debug")
	add_compile_definitions(FKE_BUILD_DEBUG=1)
else()
	fkemessage(FATAL_ERROR "FKENGINE_CONFIGURATION has to be set to be Shipping, Debug, Test or Development")
endif()