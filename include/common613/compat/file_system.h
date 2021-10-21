// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_COMPAT_FILE_SYSTEM_H
#define COMMON613_COMPAT_FILE_SYSTEM_H

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
