#include "gtest/gtest.h"

extern "C" {
#include "includes/llstack.h"
}

TEST(LLStackTest, NewLLStack) {
  LLStack* stack = llstack_new();
  ASSERT_NE(stack, nullptr);
  ASSERT_EQ(llstack_empty(stack), 1);
  llstack_free(stack);
}

TEST(LLStackTest, PushAndPop) {
  LLStack* stack = llstack_new();
  ASSERT_NE(stack, nullptr);
  ASSERT_EQ(llstack_empty(stack), 1);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  llstack_push(stack, &item1);
  llstack_push(stack, &item2);
  llstack_push(stack, &item3);

  ASSERT_EQ(llstack_empty(stack), 0);
  ASSERT_EQ(llstack_pop(stack), &item3);
  ASSERT_EQ(llstack_empty(stack), 0);
  ASSERT_EQ(llstack_pop(stack), &item2);
  ASSERT_EQ(llstack_empty(stack), 0);
  ASSERT_EQ(llstack_pop(stack), &item1);
  ASSERT_EQ(llstack_empty(stack), 1);

  llstack_free(stack);
}
