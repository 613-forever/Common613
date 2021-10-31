// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_ARITH_UTILS_H
#define COMMON613_ARITH_UTILS_H

#include <common613/assert.h>
#include <common613/compat/cpp17.h>

namespace common613 {

template <class ToType, class FromType>
COMMON613_NODISCARD
inline ToType checked_cast(FromType i) {
  COMMON613_REQUIRE(i <= std::numeric_limits<ToType>::max(),
                    "Overflow for coordinates: {} > {}.", i, std::numeric_limits<ToType>::max());
  COMMON613_REQUIRE((!std::is_signed<FromType>::value || i >= std::numeric_limits<ToType>::min()),
                    "Underflow for coordinates: {} < {}.", i, std::numeric_limits<ToType>::min());
  return static_cast<ToType>(i);
}

}

#endif //! COMMON613_ARITH_UTILS_H
