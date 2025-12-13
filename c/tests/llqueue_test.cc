#include "gtest/gtest.h"

extern "C" {
#include "includes/llqueue.h"
}

TEST(LLQueueTest, NewLLQueue) {
  LLQueue* queue = llq_new();
  ASSERT_NE(queue, nullptr);
  ASSERT_EQ(llq_empty(queue), 1);
  llq_free(queue);
}

TEST(LLQueueTest, EnqueueAndDequeue) {
  LLQueue* queue = llq_new();
  ASSERT_NE(queue, nullptr);
  ASSERT_EQ(llq_empty(queue), 1);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  llq_enqueue(queue, &item1);
  llq_enqueue(queue, &item2);
  llq_enqueue(queue, &item3);
  ASSERT_EQ(llq_empty(queue), 0);
  ASSERT_EQ(llq_dequeue(queue), &item1);
  ASSERT_EQ(llq_empty(queue), 0);
  ASSERT_EQ(llq_dequeue(queue), &item2);
  ASSERT_EQ(llq_empty(queue), 0);
  ASSERT_EQ(llq_dequeue(queue), &item3);
  ASSERT_EQ(llq_empty(queue), 1);
  llq_free(queue);
}
