// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <gtest/gtest.h>
#include <common613/assert.h>

TEST(Assertions, Fatal) {
  ASSERT_ANY_THROW(COMMON613_FATAL("expected to die here {}", 2));
}

TEST(Assertions, Success) {
  ASSERT_NO_FATAL_FAILURE(COMMON613_REQUIRE(true, "should not die here {}", "42"));
}

TEST(Assertions, Failure) {
  ASSERT_ANY_THROW(COMMON613_REQUIRE(false, "should die here {}", "abc"));
}
