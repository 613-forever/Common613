// SPDX-License-Identifier: MIT
// Copyright (c) 2021 613_forever

#include <cstdint>
#include <gtest/gtest.h>
#include <common613/vector_definitions.h>

using namespace std;
using common613::ArrNi;

TEST(ArrayDefinitionTest, type) {
  {
    typedef ArrNi<false, std::int16_t, 2> Vector;
    EXPECT_TRUE(Vector::isPoint);
    EXPECT_FALSE(Vector::isVector);
    EXPECT_TRUE((std::is_same_v<typename Vector::valueType, std::int16_t>));
    EXPECT_EQ(Vector::dimension, 2);
  }

  {
    typedef ArrNi<true, std::uint8_t, 5> Vector;
    EXPECT_TRUE(Vector::isVector);
    EXPECT_FALSE(Vector::isPoint);
    EXPECT_TRUE((std::is_same_v<typename Vector::valueType, std::uint8_t>));
    EXPECT_EQ(Vector::dimension, 5);
  }

  {
    typedef ArrNi<true, int, 1> Vector;
    EXPECT_TRUE(Vector::isVector);
    EXPECT_FALSE(Vector::isPoint);
    EXPECT_TRUE((std::is_same_v<typename Vector::valueType, int>));
    EXPECT_EQ(Vector::dimension, 1);
  }
}

TEST(ArrayDefinitionTest, value1d) {
  typedef ArrNi<false, int, 1> Vector;

  Vector v1{-6};
  EXPECT_EQ(v1.arr[0], -6);
  EXPECT_EQ(v1.x(), -6);

  v1.x() = -3;
  EXPECT_EQ(v1.arr[0], -3);

  EXPECT_EQ(Vector::of(1).x(), 1);
}

TEST(ArrayDefinitionTest, value2d) {
  typedef ArrNi<true, int, 2> Vector;

  Vector v1{1, -2};
  EXPECT_EQ(v1.arr[0], 1);
  EXPECT_EQ(v1.arr[1], -2);
  EXPECT_EQ(v1.x(), 1);
  EXPECT_EQ(v1.y(), -2);

  v1.x() = -3;
  v1.y() = 4;
  EXPECT_EQ(v1.arr[0], -3);
  EXPECT_EQ(v1.arr[1], 4);

  EXPECT_EQ(Vector::of(2, 1).x(), 2);
  EXPECT_EQ(Vector::of(2, 1).y(), 1);
}

TEST(ArrayDefinitionTest, value3d) {
  typedef ArrNi<false, int, 3> Vector;

  Vector v1{1, 0, -2};
  EXPECT_EQ(v1.arr[0], 1);
  EXPECT_EQ(v1.arr[1], 0);
  EXPECT_EQ(v1.arr[2], -2);
  EXPECT_EQ(v1.x(), 1);
  EXPECT_EQ(v1.y(), 0);
  EXPECT_EQ(v1.z(), -2);

  v1.x() = -3;
  v1.y() = 4;
  v1.z() = -5;
  EXPECT_EQ(v1.arr[0], -3);
  EXPECT_EQ(v1.arr[1], 4);
  EXPECT_EQ(v1.arr[2], -5);

  EXPECT_EQ(Vector::of(2, 1, 5).x(), 2);
  EXPECT_EQ(Vector::of(2, 1, 5).y(), 1);
  EXPECT_EQ(Vector::of(2, 1, 5).z(), 5);
}
