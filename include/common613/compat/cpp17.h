#pragma once
#ifndef COMMON613_COMPAT_CPP17_H
#define COMMON613_COMPAT_CPP17_H

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

#if __cplusplus >= 201703L
#define COMMON613_CONSTEXPR_IF if constexpr
#else
#define COMMON613_CONSTEXPR_IF if
#endif

#endif //COMMON613_COMPAT_CPP17_H
