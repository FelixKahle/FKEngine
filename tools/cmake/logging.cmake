# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Logs a message.
#
# @param mode - The logging mode. The modes are equivalent to the CMake message modes.
# @param message - The message to output.
macro(fkemessage mode message)
	message(${mode} "[FKEngine Build System] -- ${mode} -- " ${message})
endmacro()

# Prints a line to the console that should make the console more readable.
macro(fkeseperateline)
	fkemessage(STATUS "--------------------------------------------------------------------")
endmacro()