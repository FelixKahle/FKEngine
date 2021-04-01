# Copyright 2021 Felix Kahle. All rights reserved.

# Command line argumnents are beeing checked here.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Check if a configuration is set.
if (NOT DEFINED FKENGINE_CONFIGURATION)
	message(FATAL_ERROR "FKENGINE_CONFIGURATION hast to be set to Release or Debug")
endif()

# Print out some information about the buidling progress.
fkemessage(STATUS "The command line argumets have been checked")