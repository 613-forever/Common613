// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

/// @file
/// @brief A utility to import C++17 \<filesystem\> into C++14, with Boost.Filesystem as fallback.

#pragma once
#ifndef COMMON613_COMPAT_FILE_SYSTEM_H
#define COMMON613_COMPAT_FILE_SYSTEM_H

/// @namespace common613::filesystem
/// @brief An alias to @c std::filesystem or @c boost::filesystem according to C++ standards.
#if __cplusplus >= 201703L
# include <filesystem>
namespace common613 {
namespace filesystem = std::filesystem;
}
#else
# include <boost/filesystem.hpp>
namespace common613 {
namespace filesystem = boost::filesystem;
}
#endif

#endif //COMMON613_COMPAT_FILE_SYSTEM_H
