#include "gtest/gtest.h"
#include "TSet.h"

TEST(TBitField, SetBit) {
  TBitField bf(10);
  bf.SetBit(3);
  EXPECT_EQ(bf.GetBit(3), 1);
}

TEST(TBitField, ClearBit) {
  TBitField bf(10);
  bf.SetBit(3);
  EXPECT_EQ(bf.GetBit(3), 1);
  bf.ClearBit(3);
  EXPECT_EQ(bf.GetBit(3), 0);
}

TEST(TBitField, And) {
  TBitField bf1(10);
  bf1.SetBit(3);
  bf1.SetBit(5);

  TBitField bf2(10);
  bf2.SetBit(8);
  bf2.SetBit(5);

  TBitField res = bf1 & bf2;
  EXPECT_EQ(res.GetBit(3), 0);
  EXPECT_EQ(res.GetBit(5), 1);
  EXPECT_EQ(res.GetBit(8), 0);
}

TEST(TSet, InsElem) {
  TSet s(10);
  s.InsElem(4);
  EXPECT_EQ(s.IsMember(4), true);
}

TEST(TSet, DelElem) {
  TSet s(10);
  s.InsElem(4);
  EXPECT_EQ(s.IsMember(4), true);
  s.DelElem(4);
  EXPECT_EQ(s.IsMember(4), false);
}

TEST(TSet, OperatorOr) {
  TSet s1(10);
  s1.InsElem(4);
  s1.InsElem(6);
  TSet s2(10);
  s2.InsElem(1);
  s2.InsElem(5);
  TSet res = s1 | s2;
  EXPECT_EQ(res.IsMember(1), true);
  EXPECT_EQ(res.IsMember(4), true);
  EXPECT_EQ(res.IsMember(5), true);
  EXPECT_EQ(res.IsMember(6), true);
}
