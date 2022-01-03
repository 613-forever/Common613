// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

/// @file
/// @brief Utilities for integer vector arithmetics, note that they are all integer operations, especially division.

#pragma once
#ifndef COMMON613_VECTOR_ARITH_UTILS_H
#define COMMON613_VECTOR_ARITH_UTILS_H

#include <functional>
#include <vector>
#include <common613/assert.h>
#include <common613/checked_cast.h>
#include <common613/compat/cpp17.h>
#include <common613/vector_definitions.h>

namespace common613 {

/// @cond
namespace internal {

template <bool A, bool B, class IntT, std::size_t N, std::size_t... IND>
COMMON613_NODISCARD
constexpr bool equalHelper(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs,
                           std::integer_sequence<std::size_t, IND...>) {
  return COMMON613_FOLD_RIGHT((lhs.arr[IND] == rhs.arr[IND]), &&);
}

template <bool A, class IntT, std::size_t N, class UnaryFunc, std::size_t... IND>
COMMON613_NODISCARD
constexpr ArrNi<A, IntT, N> unaryHelper(const ArrNi<A, IntT, N>& operand, UnaryFunc&& f,
                                        std::integer_sequence<std::size_t, IND...>) {
  return ArrNi<A, IntT, N>::of(f(operand.arr[IND])...);
}

template <bool RET, bool A, bool B, class IntT, std::size_t N, class BinaryFunc, std::size_t... IND>
COMMON613_NODISCARD
constexpr ArrNi<RET, IntT, N> binaryHelper(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs, BinaryFunc&& f,
                                           std::integer_sequence<std::size_t, IND...>) {
  return ArrNi<RET, IntT, N>::of(f(lhs.arr[IND], rhs.arr[IND])...);
}

}
/// @endcond

/// @related ArrNi
template <bool A, class IntT, std::size_t N>
COMMON613_NODISCARD
constexpr bool operator==(const ArrNi<A, IntT, N>& lhs, const ArrNi<A, IntT, N>& rhs) {
  return internal::equalHelper(lhs, rhs, std::make_index_sequence<N>{});
}

/// @related ArrNi
template <bool A, class IntT, std::size_t N>
COMMON613_NODISCARD
constexpr bool operator!=(const ArrNi<A, IntT, N>& lhs, const ArrNi<A, IntT, N>& rhs) {
  return !(lhs == rhs);
}

/// @related ArrNi
template <bool A, bool B, class IntT, std::size_t N>
COMMON613_NODISCARD
constexpr ArrNi<A && B, IntT, N> operator+(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs) {
  static_assert(A || B, "Point + Point is not allowed.");
  return internal::binaryHelper<A && B>(lhs, rhs, std::plus<>{}, std::make_index_sequence<N>{});
}

/// @related ArrNi
template <bool A, bool B, class IntT, std::size_t N>
COMMON613_NODISCARD
constexpr ArrNi<A == B, IntT, N> operator-(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs) {
  static_assert(!A || B, "Vector - Point is not allowed.");
  return internal::binaryHelper<A == B>(lhs, rhs, std::minus<>(), std::make_index_sequence<N>{});
}

/// @related ArrNi
template <class IntT, class NumT, std::size_t N>
COMMON613_NODISCARD
constexpr ArrNi<true, IntT, N> operator*(const ArrNi<true, IntT, N>& operand, NumT mul) {
  return internal::unaryHelper(operand, [mul](IntT i) { return i * mul; }, std::make_index_sequence<N>{});
}

/// @related ArrNi
/// @note Performs integer division when @p NumT is integral.
template <class IntT, class NumT, std::size_t N>
COMMON613_NODISCARD
constexpr ArrNi<true, IntT, N> operator/(const ArrNi<true, IntT, N>& operand, NumT rhs) {
  return internal::unaryHelper(operand, [rhs](IntT i) { return i / rhs; }, std::make_index_sequence<N>{});
}

/// @related ArrNi
template <bool A, class IntT>
COMMON613_NODISCARD
constexpr bool operator<(const ArrNi<A, IntT, 1>& lhs, const ArrNi<A, IntT, 1>& rhs) {
  return lhs.arr[0] < rhs.arr[0];
}

/// @related ArrNi
template <bool A, class IntT>
COMMON613_NODISCARD
constexpr bool operator<=(const ArrNi<A, IntT, 1>& lhs, const ArrNi<A, IntT, 1>& rhs) {
  return lhs.arr[0] <= rhs.arr[0];
}

/// @related ArrNi
template <bool A, class IntT>
COMMON613_NODISCARD
constexpr bool operator>(const ArrNi<A, IntT, 1>& lhs, const ArrNi<A, IntT, 1>& rhs) {
  return lhs.arr[0] > rhs.arr[0];
}

/// @related ArrNi
template <bool A, class IntT>
COMMON613_NODISCARD
constexpr bool operator>=(const ArrNi<A, IntT, 1>& lhs, const ArrNi<A, IntT, 1>& rhs) {
  return lhs.arr[0] >= rhs.arr[0];
}

}

#endif //COMMON613_VECTOR_ARITH_UTILS_H
