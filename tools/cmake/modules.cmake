# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# This file adds all modules of the FKEngine.
# That does not mean that they are being linked to the final executeable,
# but they get build and can be linked if needed.

# This line is used to make the console more readable.
fkeseperateline()

# Print out some information about the buidling progress.
fkemessage(STATUS "Third party modules have been loaded")

###################################################################################################################################################

fkeseperateline()

# The core module.
add_subdirectory(${FKENGINE_SOURCE_DIR}/runtime/fkecore)

# This line is used to make the console more readable.
fkeseperateline()

# The entities module.
add_subdirectory(${FKENGINE_SOURCE_DIR}/runtime/fkeentities)

# This line is used to make the console more readable.
fkeseperateline()

# Print out some information about the buidling progress.
fkemessage(STATUS "Modules have been loaded")