# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# If set to TRUE char_t is the same type as widechar_t. If not, char_t is the same type as ansichar_t This is only for supported platforms.
option(FKE_UNICODE "If set to TRUE char_t is the same type as widechar_t. If not, char_t is the same type as ansichar_t This is only for supported platforms." ON)
option(FKE_DO_CHECK "If set to ON, the engine checks expresions." ON)
option(FKE_NO_LOGGING "If set to ON, the engine will ignore all logs." OFF)
option(FKE_ONLY_LOG_FATAL_ERRORS "If set to ON, the engine will only log fatal errors" OFF)
