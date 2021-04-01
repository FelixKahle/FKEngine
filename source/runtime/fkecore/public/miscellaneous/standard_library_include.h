// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include <stdint.h>
#include "hardware_abstraction_layer/platform.h"
#include "fkecore_module.h"

#include <vector>
#include <array>
#include <memory>
#include <type_traits>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstddef>
#include <array>
#include <functional>
#include <optional>
#include <utility>
#include <sstream>

/** The namespace of the FKEngine. */
namespace fkengine
{
	using namespace std;

	// vector<t>
	template<typename t, typename allo = allocator<t>>
	using dynamic_array = vector<t, allo>;

	using char_t_string = basic_string<char_t>;
	using ansi_string = string;
	using wide_string = wstring;
}