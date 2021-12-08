// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <gtest/gtest.h>
#include <common613/arith_utils.h>
using common613::checked_cast;

TEST(ArithUtils, Common) {
  long long l = 5LL;
  int i;
  ASSERT_NO_FATAL_FAILURE(i = checked_cast<int>(l));
  ASSERT_EQ(5, i);
}

TEST(ArithUtils, Bad) {
  long long l = 400'0000'0000LL;
  int i;
  EXPECT_ANY_THROW(i = checked_cast<int>(l));
  l = -400'0000'0000LL;
  EXPECT_ANY_THROW(i = checked_cast<int>(l));
}
