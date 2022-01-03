// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

/// @file
/// @brief Provide a runtime (constexpr may produce compile-time checking) casting with range checking.

#pragma once
#ifndef COMMON613_CHECKED_CAST_H
#define COMMON613_CHECKED_CAST_H

#include <common613/assert.h>
#include <common613/compat/cpp17.h>

namespace common613 {

/**
 * @brief Casts variables with range checking.
 * @tparam ToType Type to cast into, compulsory.
 * @tparam FromType Type to cast from.
 * @param i A value to cast.
 * @return The value cast from @p i.
 * @note No underflow checking when @p FromType is an unsigned type.
 */
template <class ToType, class FromType>
COMMON613_NODISCARD
constexpr ToType checked_cast(FromType i) {
  COMMON613_REQUIRE_SILENT(i <= std::numeric_limits<ToType>::max(),
                           "Overflow for coordinates: {} > {}.", i, std::numeric_limits<ToType>::max());
  COMMON613_REQUIRE_SILENT((!std::is_signed<FromType>::value || i >= std::numeric_limits<ToType>::min()),
                           "Underflow for coordinates: {} < {}.", i, std::numeric_limits<ToType>::min());
  return static_cast<ToType>(i);
}

}

#endif //COMMON613_CHECKED_CAST_H
