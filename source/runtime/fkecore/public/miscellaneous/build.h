// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

// Build configuration coming from CMake, do not modify.

// Set any configuration not defined by CMake to zero.
#ifndef FKE_BUILD_DEBUG
	#define FKE_BUILD_DEBUG 0
#endif
#ifndef FKE_BUILD_DEVELOPMENT
	#define FKE_BUILD_DEVELOPMENT 0
#endif
#ifndef FKE_BUILD_TEST
	#define FKE_BUILD_TEST 0
#endif
#ifndef FKE_BUILD_SHIPPING
	#define FKE_BUILD_SHIPPING 0
#endif
#ifndef FKE_EDITOR
	#define FKE_EDITOR 0
#endif
#ifndef FKE_BUILD_SHIPPING_WITH_EDITOR
	#define FKE_BUILD_SHIPPING_WITH_EDITOR 0
#endif
#ifndef FKE_SERVER
	/** Whether compiling for dedicated server or not. */
	#define FKE_SERVER 0
#endif

 // Ensure that we have one, and only one build config coming from CMake.
#if FKE_BUILD_DEBUG + FKE_BUILD_DEVELOPMENT + FKE_BUILD_TEST + FKE_BUILD_SHIPPING != 1
	#error Exactly one of [FKE_BUILD_DEBUG FKE_BUILD_DEVELOPMENT FKE_BUILD_TEST FKE_BUILD_SHIPPING] should be defined to be 1
#endif

#ifndef FKE_WITH_EDITOR
	/** Whether compiling with the editor. */
	#define FKE_WITH_EDITOR	0
#endif

#ifndef FKE_WITH_ENGINE
	/** Whether compiling with the engine. */
	#define FKE_WITH_ENGINE	1
#endif

#ifndef FKE_DO_CHECK
	#define FKE_DO_CHECK FKE_BUILD_DEBUG || FKE_BUILD_DEVELOPMENT
#endif

#ifndef FKE_ONLY_LOG_FATAL_ERRORS
	#define FKE_ONLY_LOG_FATAL_ERRORS 1
#endif

#ifndef FKE_NO_LOGGING
	#define FKE_NO_LOGGING !FKE_ONLY_LOG_FATAL_ERRORS
#endif


