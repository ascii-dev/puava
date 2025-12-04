#include "gtest/gtest.h"

extern "C" {
#include "includes/arrstack.h"
}

TEST(ArrStackTest, NewArrStack) {
  ArrStack* stack = arrstack_new();
  ASSERT_NE(stack, nullptr);
  ASSERT_EQ(arrstack_empty(stack), 1);
  arrstack_free(stack);
}

TEST(ArrStackTest, PushAndPop) {
  ArrStack* stack = arrstack_new();
  ASSERT_NE(stack, nullptr);
  ASSERT_EQ(arrstack_empty(stack), 1);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  arrstack_push(stack, &item1);
  arrstack_push(stack, &item2);
  arrstack_push(stack, &item3);

  ASSERT_EQ(arrstack_empty(stack), 0);
  ASSERT_EQ(arrstack_pop(stack), &item3);
  ASSERT_EQ(arrstack_empty(stack), 0);
  ASSERT_EQ(arrstack_pop(stack), &item2);
  ASSERT_EQ(arrstack_empty(stack), 0);
  ASSERT_EQ(arrstack_pop(stack), &item1);
  ASSERT_EQ(arrstack_empty(stack), 1);

  arrstack_free(stack);
}
