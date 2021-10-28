// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#pragma once
#ifndef COMMON613_FILE_UTILS_H
#define COMMON613_FILE_UTILS_H

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4996)
#endif

#include <cstdio>
#include <memory>
#include <type_traits>
#include <common613/assert.h>
#include <common613/memory.h>
#include <common613/compat/cpp17.h>
#include <common613/compat/file_system.h>

namespace common613 { namespace file {

/// @internal
struct Closer {
  void operator()(FILE* p) {
    std::fclose(p);
  }
};

/// @brief RAII-style wrapper for FILE*.
using File = std::unique_ptr<FILE, Closer>;

/// @overload
COMMON613_NODISCARD inline File open(const char* filePath, const char* mode, std::nothrow_t) {
  std::FILE* file = std::fopen(filePath, mode);
  return File(file);
}

/// @brief Opens a file and wrap it in RAII style.
COMMON613_NODISCARD inline File open(const char* filePath, const char* mode) {
  File file = open(filePath, mode, std::nothrow);
  COMMON613_REQUIRE(file != nullptr, "Failed to open file: {}. Please check it again.", filePath);
  return file;
}

/// @overload
COMMON613_NODISCARD inline File open(const std::string& filePath, const char* mode, std::nothrow_t) {
  return open(filePath.c_str(), mode, std::nothrow);
}

/// @overload
COMMON613_NODISCARD inline File open(const std::string& filePath, const char* mode) {
  return open(filePath.c_str(), mode);
}

namespace detail {
template <class TChar>
struct WcstombsWrapper{
  constexpr static size_t call(char* buffer, const TChar* path, size_t bufferSize) { return 0; }
};

template <>
struct WcstombsWrapper<wchar_t>{
  inline static size_t call(char* buffer, const wchar_t* path, int bufferSize) {
    return std::wcstombs(buffer, path, bufferSize);
  }
};
}

/// @overload
COMMON613_NODISCARD inline File open(const filesystem::path& filePath, const char* mode, std::nothrow_t) {
  COMMON613_CONSTEXPR_IF(std::is_same<filesystem::path::value_type, wchar_t>::value) {
    auto size = filePath.string().size() * 3;
    std::vector<char> buffer(size + 1);
    auto ret = detail::WcstombsWrapper<filesystem::path::value_type>::call(buffer.data(), filePath.c_str(), size + 1);
    COMMON613_REQUIRE(ret != -1, "Path conversion error.");
    return open(buffer.data(), mode, std::nothrow);
  } else {
    return open(filePath.c_str(), mode, std::nothrow);
  }
}

/// @overload
COMMON613_NODISCARD inline File open(const filesystem::path& filePath, const char* mode) {
  File file = open(filePath, mode, std::nothrow);
  COMMON613_REQUIRE(file != nullptr, "Failed to open file: {}. Please check it again.");
  return file;
}

/// @override
template <class T>
COMMON613_NODISCARD inline size_t read(const File& file, T* buffer, std::nothrow_t, size_t count = 1) {
  return std::fread(buffer, sizeof(T), count, file.get());
}

/// @brief Reads @a count data units from @a file, each filling @a *buffer.
template <class T>
inline void read(const File& file, T* buffer, size_t count = 1) {
  size_t countRead = read(file, buffer, std::nothrow, count);
  COMMON613_REQUIRE(countRead == count,
                          "Failed to read required count. Read: {}. Required: {}. Error code: {}.",
                          countRead, count, std::ferror(file.get()));
}

/// @override
template <class T>
COMMON613_NODISCARD inline size_t write(const File& file, T* buffer, std::nothrow_t, size_t count = 1) {
  return std::fwrite(buffer, sizeof(T), count, file.get());
}

/// @brief Writes @a count data units to @a file, each sharing the size of @a &buffer.
template <class T>
inline void write(const File& file, T* buffer, size_t count = 1) {
  size_t countRead = write(file, buffer, std::nothrow, count);
  COMMON613_REQUIRE(countRead == count,
                          "Failed to write required count. Read: {}. Required: {}. Error code: {}.",
                          countRead, count, std::ferror(file.get()));
}

/// @brief Calls fseek, with result checked.
inline void seek(const File& file, long offset, int orig) {
  int ret = std::fseek(file.get(), offset, orig);
  COMMON613_REQUIRE(ret == 0, "Failed to seek in file. Error code: {}.", std::ferror(file.get()));
}

/// @brief Reads all data from @file.
COMMON613_NODISCARD inline Memory readAll(const File& file) {
  FILE* pFile = file.get();
  seek(file, 0, SEEK_END);
  size_t size = ftell(pFile);
  Memory buffer(size);
  std::rewind(pFile);
  std::fread(buffer.data(), size, 1, pFile);
  return buffer;
}

/// @brief Calls feof.
COMMON613_NODISCARD inline bool eof(const File& file) {
  return std::feof(file.get());
}

}

using file::File;

}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif //COMMON613_FILE_UTILS_H
