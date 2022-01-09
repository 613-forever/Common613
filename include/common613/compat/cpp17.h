// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

/// @file
/// @brief Some utilities to import some useful C++17 features into C++14 main projects.

#pragma once
#ifndef COMMON613_COMPAT_CPP17_H
#define COMMON613_COMPAT_CPP17_H

/// @namespace common613
/// @brief Root namespace for project Common613.
namespace common613 {};

/// @def COMMON613_NODISCARD
/// @brief Provide a C++14 fallback for attribute @c [[nodiscard]] .
#if __cplusplus >= 201703L
# define COMMON613_NODISCARD [[nodiscard]]
#else
# if defined(__GNUC__) || defined(__clang__)
#  define COMMON613_NODISCARD __attribute__((warn_unused_result))
# elif _MSC_VER >= 1700
#  define COMMON613_NODISCARD _Check_return_
# else
#  define COMMON613_NODISCARD
# endif
#endif

/// @def COMMON613_CONSTEXPR_IF
/// @brief Provide a C++14 fallback for C++17 constexpr if.
#if __cplusplus >= 201703L
#define COMMON613_CONSTEXPR_IF if constexpr
#else
#define COMMON613_CONSTEXPR_IF if
#endif

/// @def COMMON613_FOLD_RIGHT
/// @brief Provide a C++14 fallback for C++17 fold expression, in the unary right fold form.
#if __cplusplus >= 201703L
#define COMMON613_FOLD_RIGHT(package, op) ((package) op ...)
#else

namespace common613 { namespace internal {
/// @cond
template<class BinaryFunc, class First>
constexpr auto fold_right(BinaryFunc&&, First&& first) {
    return std::forward<First>(first);
}

template<class BinaryFunc, class First, class... Remaining>
constexpr auto fold_right(BinaryFunc&& f, First&& first, Remaining&&... remaining) {
    return f(std::forward<First>(first), fold_right(std::forward<BinaryFunc>(f), std::forward<Remaining>(remaining)...));
}
/// @endcond

} }

#define COMMON613_FOLD_RIGHT(package, op) \
  common613::internal::fold_right([](auto lhs, auto rhs) { return lhs op rhs; }, (package)...)

#endif

#endif //COMMON613_COMPAT_CPP17_H
