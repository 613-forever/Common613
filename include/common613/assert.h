// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_ASSERT_H
#define COMMON613_ASSERT_H

#include <cstdio>
#include <fmt/format.h>
#include <boost/log/trivial.hpp>

/// @internal
#define COMMON613_STRINGIZE_DETAIL(x) #x
/// @internal
#define COMMON613_STRINGIZE(x) COMMON613_STRINGIZE_DETAIL(x)

/// @def COMMON613_TRACE
/// @brief Prints stack trace if COMMON613_STACKTRACE_DEBUG is defined.
#if defined(COMMON613_STACKTRACE_DEBUG) && COMMON613_STACKTRACE_DEBUG == 1

# include <boost/stacktrace.hpp>

# define COMMON613_TRACE() do { BOOST_LOG_TRIVIAL(debug) << boost::stacktrace::stacktrace() << std::endl; } while(0)
#else
# define COMMON613_TRACE() ((void) 0)

#endif

/// @def COMMON613_FATAL
/// @brief Prints fatal message and abort.
/// @def COMMON613_REQUIRE
/// @brief Prints fatal if requirement @a cond is not satisfied.

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
#endif

#endif //COMMON613_ASSERT_H
