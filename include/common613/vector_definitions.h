// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_VECTOR_DEFINITIONS_H
#define COMMON613_VECTOR_DEFINITIONS_H

#include <array>
#include <cstdint>
#include <common613/struct_size_check.h>
#include <common613/arith_utils.h>
#include <common613/compat/cpp17.h>

namespace common613 {

namespace internal {

/// @internal
// workaround for std::is_integral<IntT2>::value && ...
template <class... Types>
struct AllIntegralHelper {};

/// @internal
template <class FirstType, class... RemainingTypes>
struct AllIntegralHelper<FirstType, RemainingTypes...> {
  constexpr static const bool value = std::is_integral_v<FirstType> && AllIntegralHelper<RemainingTypes...>::value;
};

/// @internal
template <>
struct AllIntegralHelper<> {
  constexpr static const bool value = true;
};

}

/**
 * @brief A class for integral vectors and points with arithmetic operations.
 * @tparam Vec Whether it is a vector ( @c true ) or a point ( @c false ).
 * @tparam IntT Underlying int type.
 * @tparam N Dimensions.
 */
template <bool Vec, class IntT, std::size_t N>
struct ArrNi {
  static_assert(N != 0, "ArrNi is specialized with length 0!");
  /// @brief Whether it is a vector.
  constexpr static const bool isVector = Vec;
  /// @brief Whether it is a point.
  constexpr static const bool isPoint = !Vec;
  /// @brief Dimensions.
  constexpr static const size_t dimension = N;
  /// @brief Underlying int type.
  using valueType = IntT;

  /// @brief Underlying data.
  std::array<IntT, N> arr;

  /// @brief Returns the 1st component.
  COMMON613_NODISCARD IntT x() const { return arr[0]; }
  /// @overload
  COMMON613_NODISCARD IntT& x() { return arr[0]; }

  /// @brief Returns the 2nd component.
  template <class Enabled = std::enable_if<N >= 2>>
  COMMON613_NODISCARD IntT y() const { return arr[1]; }
  /// @overload
  template <class Enabled = std::enable_if<N >= 2>>
  COMMON613_NODISCARD IntT& y() { return arr[1]; }

  /// @brief Returns the 3rd component.
  template <class Enabled = std::enable_if<N >= 3>>
  COMMON613_NODISCARD IntT z() const { return arr[2]; }
  /// @overload
  template <class Enabled = std::enable_if<N >= 3>>
  COMMON613_NODISCARD IntT& z() { return arr[2]; }

  COMMON613_INJECT_SIZE_FIELD(sizeof(IntT) * N);

  /// @brief Constructs an array of given values.
  template <class... IntT2, class Enabled = std::enable_if_t<N == sizeof...(IntT2) &&
      internal::AllIntegralHelper<IntT2...>::value>>
  constexpr static ArrNi of(IntT2... integers) {
    return ArrNi{checked_cast<IntT>(integers)...};
  }
};

/// @brief Shortcut for 1-D @ref ArrNi.
template <bool Vec, class IntType>
using Arr1i = ArrNi<Vec, IntType, 1>;

/// @brief Shortcut for 2-D @ref ArrNi.
template <bool Vec, class IntType>
using Arr2i = ArrNi<Vec, IntType, 2>;

/// @brief Shortcut for 3-D @ref ArrNi.
template <bool Vec, class IntType>
using Arr3i = ArrNi<Vec, IntType, 3>;

}

#endif //COMMON613_VECTOR_DEFINITIONS_H
