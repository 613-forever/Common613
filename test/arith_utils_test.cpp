// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <gtest/gtest.h>
#include <common613/arith_utils.h>
using common613::checked_cast;

TEST(ArithUtils, Common) {
  long long l = 5LL;
  unsigned long long u = 10ULL;
  int i = 0;

  EXPECT_NO_FATAL_FAILURE(i = checked_cast<int>(l));
  EXPECT_EQ(5, i);

  EXPECT_NO_FATAL_FAILURE(i = checked_cast<int>(u));
  EXPECT_EQ(10, i);

  EXPECT_NO_FATAL_FAILURE(i = checked_cast<unsigned int>(l));
  EXPECT_EQ(5, i);

  EXPECT_NO_FATAL_FAILURE(i = checked_cast<unsigned int>(u));
  EXPECT_EQ(10, i);
}

TEST(ArithUtils, Bad) {
  long long l = 400'0000'0000LL, l2 = -400'0000'0000LL, l3 = -5LL;
  int i = 0;

  EXPECT_ANY_THROW(i = checked_cast<int>(l));
  EXPECT_ANY_THROW(i = checked_cast<int>(l2));
  EXPECT_NO_FATAL_FAILURE(i = checked_cast<int>(l3));
  EXPECT_EQ(i, -5);

  EXPECT_ANY_THROW(i = checked_cast<unsigned int>(l));
  EXPECT_ANY_THROW(i = checked_cast<unsigned int>(l2));
  EXPECT_ANY_THROW(i = checked_cast<unsigned int>(l3));

  unsigned long long u = 400'0000'0000ULL;
  EXPECT_ANY_THROW(i = checked_cast<int>(u));
  EXPECT_ANY_THROW(i = checked_cast<unsigned int>(u));
}
