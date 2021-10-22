// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <gtest/gtest.h>
#include <common613/file_utils.h>

using namespace std;
using namespace common613::file;

TEST(FileUtilsOpennerTest, open) {
  string filename = tmpnam(nullptr);
  auto openR = [&filename]{ File file = open(filename, "r"); };
  ASSERT_ANY_THROW(openR());
  auto openW = [&filename]{ File file = open(filename, "w"); };
  ASSERT_NO_FATAL_FAILURE(openW());
  ASSERT_NO_FATAL_FAILURE(openR());
  auto openPath = [&filename]{ File file = open(filesystem::path(filename), "r"); };
  ASSERT_NO_FATAL_FAILURE(openPath());
  remove(filename.c_str());
}

class FileUtilsRWTest : public ::testing::Test {
protected:
  void SetUp() override {
    file.reset(std::tmpfile());
  }

  File file;
};

TEST_F(FileUtilsRWTest, readChars) {
  seek(file, 0, SEEK_SET);
  char buffer[] = "123456789";
  ASSERT_NO_FATAL_FAILURE(write(file, &buffer));
  seek(file, 0, SEEK_SET);
  char newBuffer[10] = { '\0' };
  read(file, newBuffer, 4);
  ASSERT_STREQ("1234", newBuffer);
}

TEST_F(FileUtilsRWTest, readCharsOvercount) {
  seek(file, 0, SEEK_SET);
  char buffer[] = "123456789";
  ASSERT_NO_FATAL_FAILURE(write(file, &buffer));
  seek(file, 0, SEEK_SET);
  char newBuffer[10] = { '\0' };
  ASSERT_ANY_THROW(read(file, newBuffer, 12));
  ASSERT_TRUE(eof(file));
}

TEST_F(FileUtilsRWTest, readAll) {
  seek(file, 0, SEEK_SET);
  char buffer[] = "123456789";
  ASSERT_EQ(1, write(file, &buffer, std::nothrow)); // together with '\0'
  seek(file, 0, SEEK_SET);
  common613::Memory memory = readAll(file);
  ASSERT_EQ(sizeof(buffer) / sizeof(buffer[0]), memory.size());
  ASSERT_STREQ(buffer, reinterpret_cast<char*>(memory.data()));
}
