// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef DIALOGVIDEOGENERATOR_POS_ARITH_H
#define DIALOGVIDEOGENERATOR_POS_ARITH_H

#include <functional>
#include <vector>
#include <common613/assert.h>
#include <common613/checked_cast.h>
#include <common613/compat/cpp17.h>
#include <common613/vector_definitions.h>

namespace common613 {

namespace internal {

/// @internal
template <bool A, bool B, class IntT, std::size_t N, std::size_t... IND>
COMMON613_NODISCARD
constexpr bool equalHelper(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs,
                           std::integer_sequence<std::size_t, IND...>) {
  return COMMON613_FOLD_RIGHT((lhs.arr[IND] == rhs.arr[IND]), &&);
}

/// @internal
template <bool A, class IntT, std::size_t N, class UnaryFunc, std::size_t... IND>
COMMON613_NODISCARD
constexpr ArrNi<A, IntT, N> unaryHelper(const ArrNi<A, IntT, N>& operand, UnaryFunc&& f,
                                        std::integer_sequence<std::size_t, IND...>) {
  return ArrNi<A, IntT, N>::of(f(operand.arr[IND])...);
}

/// @internal
template <bool RET, bool A, bool B, class IntT, std::size_t N, class BinaryFunc, std::size_t... IND>
COMMON613_NODISCARD
constexpr ArrNi<RET, IntT, N> binaryHelper(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs, BinaryFunc&& f,
                                           std::integer_sequence<std::size_t, IND...>) {
  return ArrNi<RET, IntT, N>::of(f(lhs.arr[IND], rhs.arr[IND])...);
}

}

/// @related ArrNi
template <bool A, class IntT, std::size_t N>
COMMON613_NODISCARD
inline bool operator==(const ArrNi<A, IntT, N>& lhs, const ArrNi<A, IntT, N>& rhs) {
  return internal::equalHelper(lhs, rhs, std::make_index_sequence<N>{});
}

/// @related ArrNi
template <bool A, class IntT, std::size_t N>
COMMON613_NODISCARD
inline bool operator!=(const ArrNi<A, IntT, N>& lhs, const ArrNi<A, IntT, N>& rhs) {
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
inline ArrNi<A == B, IntT, N> operator-(const ArrNi<A, IntT, N>& lhs, const ArrNi<B, IntT, N>& rhs) {
  static_assert(!A || B, "Vector - Point is not allowed.");
  return internal::binaryHelper<A == B>(lhs, rhs, std::minus<>(), std::make_index_sequence<N>{});
}

/// @related ArrNi
template <class IntT, std::size_t N>
COMMON613_NODISCARD
inline ArrNi<true, IntT, N> operator*(const ArrNi<true, IntT, N>& operand, IntT mul) {
  return internal::unaryHelper(operand, [mul](IntT i) { return i * mul; }, std::make_index_sequence<N>{});
}

/// @related ArrNi
/// @note Performs integer division.
template <class IntT, std::size_t N>
COMMON613_NODISCARD
inline ArrNi<true, IntT, N> operator/(const ArrNi<true, IntT, N>& operand, IntT rhs) {
  return internal::unaryHelper(operand, [rhs](IntT i) { return i / rhs; }, std::make_index_sequence<N>{});
}

}

#endif //DIALOGVIDEOGENERATOR_POS_ARITH_H
