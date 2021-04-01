# Copyright 2021 Felix Kahle. All rights reserved.

# Definitions for the Preprocessor.
# Some defintions are made somewhere else, where they make more sense.
# All definitions made here have no better place, so they go into this file here.
# But without it the build would not work and the engine would not be build correctly.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Add the definition for the character set.
if (FKE_UNICODE)
	add_compile_definitions(FKE_UNICODE=1)
	add_compile_definitions(UNICODE)
	add_compile_definitions(_UNICODE)
else()
	add_compile_definitions(FKE_UNICODE=0)
endif()

if(FKE_DO_CHECK)
	add_compile_definitions(FKE_DO_CHECK=1)
else()
	add_compile_definitions(FKE_DO_CHECK=0)
endif()

if(FKE_NO_LOGGING)
	add_compile_definitions(FKE_NO_LOGGING=1)
else()
	add_compile_definitions(FKE_NO_LOGGING=0)
endif()

if(FKE_ONLY_LOG_FATAL_ERRORS)
	add_compile_definitions(FKE_ONLY_LOG_FATAL_ERRORS=1)
else()
	add_compile_definitions(FKE_ONLY_LOG_FATAL_ERRORS=0)
endif()

# Print out some information about the buidling progress.
fkemessage(STATUS "Miscellaneous definitions have been made")