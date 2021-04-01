# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# This is the top level file of the CMake build tree that builds the FKEngine.
# But each module has its own settings. To chance these edit the settings file of the module to edit.

# The FKEngine project.
project(FKEngine)

# !!!
# The order of this includes is important.
# Any change to this order can lead to build errors.
# !!!

# Include the file that contains the message exentension (fkemessage).
include(tools/cmake/logging.cmake)

# This line is used to make the console more readable.
fkeseperateline()

# Include the build settings for the FKEngine.
include(build_settings.cmake)

# Print out some information about the buidling progress.
fkemessage(STATUS "The build settings have been loaded.")

# Include the file that contains checks for important settings and variables.
include(tools/cmake/check_command_line_arguments.cmake)

# Include the configuration of CMake for building the FKEngine.
include(tools/CMake/configure_cmake.cmake)

# Include the build instructiuons.
include(tools/CMake/build.cmake)