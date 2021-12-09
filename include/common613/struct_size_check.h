// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_STRUCT_SIZE_CHECK_H
#define COMMON613_STRUCT_SIZE_CHECK_H

/// @brief Provides convenient modification for injected field name.
#define COMMON613_INJECTED_SIZE injected_size
/// @brief Generates a static const field "size" to mark the size of a struct.
#define COMMON613_INJECT_SIZE_FIELD(sz) \
public: constexpr static const std::size_t COMMON613_INJECTED_SIZE = (sz)
/// @brief Generates a static const field "size" to mark the size of a struct.
#define COMMON613_INHERIT_SIZE_FIELD(parent) \
public: using parent::COMMON613_INJECTED_SIZE
/// @brief Checks if a type has the asserted size of its static const field "size".
#define COMMON613_CHECK_SIZE(type) \
static_assert(sizeof(type) == (type::COMMON613_INJECTED_SIZE), "Size is incorrect: " #type ".")
/// @brief Checks if a type is a standard-layout type.
#define COMMON613_CHECK_STANDARD_LAYOUT(type) \
static_assert(std::is_standard_layout<type>::value, "Not standard layout: " #type ".")
/// @brief Checks if a type can be used in binary interactions.
#define COMMON613_CHECK_BINARY_USABLE(type) \
COMMON613_CHECK_SIZE(type); COMMON613_CHECK_STANDARD_LAYOUT(type)

namespace common613 {}

#endif //COMMON613_STRUCT_SIZE_CHECK_H
