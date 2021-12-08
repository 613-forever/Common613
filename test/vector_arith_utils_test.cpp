// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <cstdint>
#include <gtest/gtest.h>
#include <common613/vector_arith_utils.h>

using namespace std;
using common613::ArrNi;

TEST(ArrayArithmeticTest, eq) {
  {
    typedef ArrNi<true, int, 1> Vector;

    Vector v1{-6}, v2{-6}, v3{0}, v4{2};

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v2 == v1);
    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
    EXPECT_FALSE(v2 == v3);
    EXPECT_FALSE(v4 == v3);
    EXPECT_FALSE(v2 == v4);

    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v1 != v1);
    EXPECT_FALSE(v2 != v1);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);
    EXPECT_TRUE(v2 != v3);
    EXPECT_TRUE(v4 != v3);
    EXPECT_TRUE(v2 != v4);
  }

  {
    typedef ArrNi<true, int, 2> Vector;

    Vector v1{-6, 2}, v2{-6, 2}, v3{0, 2}, v4{-6, 1};

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v2 == v1);
    EXPECT_TRUE(v1 == v1);
    EXPECT_FALSE(v1 == v3);
    EXPECT_FALSE(v1 == v4);
    EXPECT_FALSE(v2 == v3);
    EXPECT_FALSE(v4 == v3);
    EXPECT_FALSE(v2 == v4);

    EXPECT_FALSE(v1 != v2);
    EXPECT_FALSE(v1 != v1);
    EXPECT_FALSE(v2 != v1);
    EXPECT_TRUE(v1 != v3);
    EXPECT_TRUE(v1 != v4);
    EXPECT_TRUE(v2 != v3);
    EXPECT_TRUE(v4 != v3);
    EXPECT_TRUE(v2 != v4);
  }
}

TEST(ArrayArithmeticTest, cmp) {
  {
    typedef ArrNi<true, int, 1> Vector;

    Vector v1{-6}, v2{-6}, v3{0}, v4{2};

    EXPECT_TRUE(v1 == v2);
    EXPECT_TRUE(v2 == v1);
    EXPECT_TRUE(v2 <= v1);
    EXPECT_TRUE(v2 >= v1);
    EXPECT_TRUE(v3 > v1);
    EXPECT_TRUE(v1 < v3);
    EXPECT_TRUE(v4 > v1);
    EXPECT_TRUE(v1 < v4);
    EXPECT_TRUE(v2 < v3);
    EXPECT_TRUE(v3 >= v2);
    EXPECT_TRUE(v4 >= v2);
    EXPECT_TRUE(v2 < v4);
    EXPECT_TRUE(v3 < v4);
    EXPECT_TRUE(v4 > v3);
    EXPECT_TRUE(v4 <= v4);
  }
}

TEST(ArrayArithmeticTest, additive) {
  {
    typedef ArrNi<true, int, 1> Vector;

    Vector v1{-6}, v2{-6}, v3{0}, v4{-12};

    EXPECT_EQ(v1 + v2, v4);
    EXPECT_EQ(v2 + v1, v4);
    EXPECT_EQ(v1 + v1, v4);
    EXPECT_EQ(v1 + v3, v1);
    EXPECT_EQ(v1 + v3, v2);
    EXPECT_EQ(v2 + v2, v4);

    EXPECT_EQ(v1 - v2, v3);
    EXPECT_EQ(v2 - v1, v3);
    EXPECT_EQ(v1 - v1, v3);
    EXPECT_EQ(v1 - v3, v1);
    EXPECT_EQ(v1 - v3, v2);
    EXPECT_EQ(v4 - v2, v1);
  }

  {
    typedef ArrNi<true, int, 2> Vector;

    Vector v1{-6, 3}, v2{-6, 3}, v3{0, 0}, v4{-12, 6};

    EXPECT_EQ(v1 + v2, v4);
    EXPECT_EQ(v2 + v1, v4);
    EXPECT_EQ(v1 + v1, v4);
    EXPECT_EQ(v1 + v3, v1);
    EXPECT_EQ(v1 + v3, v2);
    EXPECT_EQ(v2 + v2, v4);

    EXPECT_EQ(v1 - v2, v3);
    EXPECT_EQ(v2 - v1, v3);
    EXPECT_EQ(v1 - v1, v3);
    EXPECT_EQ(v1 - v3, v1);
    EXPECT_EQ(v1 - v3, v2);
    EXPECT_EQ(v4 - v2, v1);
  }
}

TEST(ArrayArithmeticTest, mulplicative) {
  {
    typedef ArrNi<true, int, 1> Vector;

    Vector v1{-6}, v2{6}, v3{0}, v4{-12};

    EXPECT_EQ(v1 * 1, v1);
    EXPECT_EQ(v1 * 0, v3);
    EXPECT_EQ(v1 * 2, v4);
    EXPECT_EQ(v1 * -1, v2);

    EXPECT_EQ(v1 / 1, v1);
    EXPECT_EQ(v4 / 2, v1);
    EXPECT_EQ(v1 / -1, v2);
  }

  {
    typedef ArrNi<true, int, 2> Vector;

    Vector v1{-6, 3}, v2{6, -3}, v3{0, 0}, v4{-12, 6};

    EXPECT_EQ(v1 * 1, v1);
    EXPECT_EQ(v1 * 0, v3);
    EXPECT_EQ(v1 * 2, v4);
    EXPECT_EQ(v1 * -1, v2);

    EXPECT_EQ(v1 / 1, v1);
    EXPECT_EQ(v4 / 2, v1);
    EXPECT_EQ(v1 / -1, v2);

    EXPECT_EQ(v1 / 4, Vector::of(-1, 0));
  }
}

TEST(ArrayArithmeticTest, mixed) {
  {
    typedef ArrNi<true, int, 2> Vector;

    Vector v1{1, 5}, v2{5, -4}, v3{6, 3};

    EXPECT_EQ(v1 * 2 - v2 / 3 + v3 / 4, Vector::of(2, 11));
    EXPECT_EQ(v1 * 5 - v2 * 2 + v3 / 2, Vector::of(-2, 34));
    EXPECT_EQ(v1 * 2 - v2 * -1 - v3, Vector::of(1, 3));
  }
}
