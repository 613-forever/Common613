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

/// @brief Opens a file and wrap it in RAII style.
COMMON613_NODISCARD inline File open(const char* filePath, const char* mode) {
  std::FILE* file = std::fopen(filePath, mode);
  COMMON613_REQUIRE(file != nullptr, "Failed to open file: {}. Please check it again.", filePath);
  return File(file);
}

/// @overload
COMMON613_NODISCARD inline File open(const std::string& filePath, const char* mode) {
  return open(filePath.c_str(), mode);
}

/// @overload
COMMON613_NODISCARD inline File open(const filesystem::path& filePath, const char* mode) {
  COMMON613_CONSTEXPR_IF(std::is_same<filesystem::path::value_type, wchar_t>::value) {
    auto size = filePath.string().size() * 3;
    std::vector<char> buffer(size + 1);
    auto ret = std::wcstombs(buffer.data(), filePath.c_str(), size + 1);
    COMMON613_REQUIRE(ret != -1, "Path conversion error.");
    return open(buffer.data(), mode);
  } else {
    return open(filePath.c_str(), mode);
  }
}

template <class T>
COMMON613_NODISCARD inline size_t read(const File& file, T* buffer, std::nothrow_t, size_t count = 1) {
  return std::fread(buffer, sizeof(T), count, file.get());
}

template <class T>
inline void read(const File& file, T* buffer, size_t count = 1) {
  size_t countRead = std::fread(buffer, sizeof(T), count, file.get());
  COMMON613_REQUIRE(countRead == count,
                          "Failed to read required count. Read: {}. Required: {}. Error code: {}.",
                          countRead, count, std::ferror(file.get()));
}

template <class T>
COMMON613_NODISCARD inline size_t write(const File& file, T* buffer, std::nothrow_t, size_t count = 1) {
  return std::fwrite(buffer, sizeof(T), count, file.get());
}

template <class T>
inline void write(const File& file, T* buffer, size_t count = 1) {
  size_t countRead = std::fwrite(buffer, sizeof(T), count, file.get());
  COMMON613_REQUIRE(countRead == count,
                          "Failed to write required count. Read: {}. Required: {}. Error code: {}.",
                          countRead, count, std::ferror(file.get()));
}

inline void seek(const File& file, long offset, int orig) {
  int ret = std::fseek(file.get(), offset, orig);
  COMMON613_REQUIRE(ret == 0, "Failed to seek in file. Error code: {}.", std::ferror(file.get()));
}

COMMON613_NODISCARD inline Memory readAll(const File& file) {
  FILE* pFile = file.get();
  seek(file, 0, SEEK_END);
  size_t size = ftell(pFile);
  Memory buffer(size);
  std::rewind(pFile);
  std::fread(buffer.data(), size, 1, pFile);
  return buffer;
}

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
