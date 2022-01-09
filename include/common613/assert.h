// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

/// @file
/// @brief Boost.Log assisted runtime assertion.

#pragma once
#ifndef COMMON613_ASSERT_H
#define COMMON613_ASSERT_H

#include <cstdio>
#include <fmt/format.h>
#include <boost/log/trivial.hpp>

namespace common613 {}

/// @cond
#define COMMON613_STRINGIZE_DETAIL(x) #x
/// @endcond

/// @def COMMON613_STRINGIZE
/// @brief Stringize an identifier.
#define COMMON613_STRINGIZE(x) COMMON613_STRINGIZE_DETAIL(x)

/// @def COMMON613_TRACE
/// @brief Prints stack trace if @c COMMON613_STACKTRACE_DEBUG is defined.
#if defined(COMMON613_STACKTRACE_DEBUG) && COMMON613_STACKTRACE_DEBUG == 1

# include <boost/stacktrace.hpp>

# define COMMON613_TRACE() do { BOOST_LOG_TRIVIAL(debug) << boost::stacktrace::stacktrace() << std::endl; } while(0)
#else
# define COMMON613_TRACE() ((void) 0)

#endif

/// @def COMMON613_FATAL
/// @brief Prints fatal message and abort.
/// @def COMMON613_REQUIRE
/// @brief Prints fatal if requirement @p cond is not satisfied.
/// @def COMMON613_REQUIRE_SILENT
/// @brief Behaves like @ref COMMON613_REQUIRE but prints nothing to keep it @c constexpr.

#if __cplusplus >= 202002L
# define COMMON613_FATAL(fmtStr, ...) \
  do {                                     \
    BOOST_LOG_TRIVIAL(fatal) << fmt::format( __FILE__ ":" COMMON613_STRINGIZE( __LINE__ ) " " fmtStr __VA_OPT(,)__ __VA_ARGS__); \
    COMMON613_TRACE();               \
    throw std::runtime_error("");          \
  } while(0)

# define COMMON613_REQUIRE(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      BOOST_LOG_TRIVIAL(fatal) << fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr __VA_OPT(,)__ __VA_ARGS__); \
      COMMON613_TRACE();             \
      throw std::runtime_error("");        \
    }                                      \
  } while(0)

# define COMMON613_REQUIRE_SILENT(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      throw std::runtime_error(fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr __VA_OPT(,)__ __VA_ARGS__));        \
    }                                      \
  } while(0)
#elif defined(_MSC_VER)
# define COMMON613_FATAL(fmtStr, ...) \
  do {                                     \
    BOOST_LOG_TRIVIAL(fatal) << fmt::format( __FILE__ ":" COMMON613_STRINGIZE( __LINE__ ) " " fmtStr, __VA_ARGS__); \
    COMMON613_TRACE();               \
    throw std::runtime_error("");          \
  } while(0)

# define COMMON613_REQUIRE(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      BOOST_LOG_TRIVIAL(fatal) << fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr, __VA_ARGS__); \
      COMMON613_TRACE();             \
      throw std::runtime_error("");        \
    }                                      \
  } while(0)

# define COMMON613_REQUIRE_SILENT(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      throw std::runtime_error(fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr, __VA_ARGS__)); \
    }                                      \
  } while(0)
#elif defined(__GNUC__)
# define COMMON613_FATAL(fmtStr, ...) \
  do {                                     \
    BOOST_LOG_TRIVIAL(fatal) << fmt::format( __FILE__ ":" COMMON613_STRINGIZE( __LINE__ ) " " fmtStr, ##__VA_ARGS__); \
    COMMON613_TRACE();               \
    throw std::runtime_error("");          \
  } while(0)

# define COMMON613_REQUIRE(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      BOOST_LOG_TRIVIAL(fatal) << fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr, ##__VA_ARGS__); \
      COMMON613_TRACE();             \
      throw std::runtime_error("");        \
    }                                      \
  } while(0)

# define COMMON613_REQUIRE_SILENT(cond, fmtStr, ...)         \
  do {                                     \
    if (!(cond)) {                         \
      throw std::runtime_error(fmt::format(__FILE__ ":" COMMON613_STRINGIZE(__LINE__) " (" #cond ") " fmtStr, ##__VA_ARGS__)); \
    }                                      \
  } while(0)
#else
# define COMMON613_FATAL(fmtStr, ...)
# define COMMON613_REQUIRE(cond, fmtStr, ...)
# define COMMON613_REQUIRE_SILENT(cond, fmtStr, ...)
# error "Please specify your dialect for pre-C++20 __VA_OPT__."
#endif

#endif //COMMON613_ASSERT_H
