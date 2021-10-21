// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_STRUCT_SIZE_CHECK_H
#define COMMON613_STRUCT_SIZE_CHECK_H

/// @brief Generates a static const field "size" to mark the size of a struct.
#define COMMON613_INJECT_SIZE_FIELD(sz) public: constexpr static const std::size_t size = sz
/// @brief Checks if a type has the asserted size of its static const field "size".
#define COMMON613_CHECK_SIZE(type) static_assert(sizeof(type) == type::size, "Size is incorrect: " #type ".")

#endif //COMMON613_STRUCT_SIZE_CHECK_H
