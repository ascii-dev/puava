#include "gtest/gtest.h"

extern "C" {
#include "includes/circular_buffer.h"
}

TEST(CircularBufferTest, NewCircularBuffer) {
  CircularBuffer* buffer = cb_new(10);
  ASSERT_NE(buffer, nullptr);
  ASSERT_EQ(cb_empty(buffer), 1);
  ASSERT_EQ(cb_full(buffer), 0);
  cb_free(buffer);
}

TEST(CircularBufferTest, EnqueueAndDequeue) {
  CircularBuffer* buffer = cb_new(10);
  ASSERT_NE(buffer, nullptr);
  ASSERT_EQ(cb_empty(buffer), 1);
  ASSERT_EQ(cb_full(buffer), 0);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  ASSERT_EQ(cb_enqueue(buffer, &item1), 0);
  ASSERT_EQ(cb_enqueue(buffer, &item2), 0);
  ASSERT_EQ(cb_enqueue(buffer, &item3), 0);
  ASSERT_EQ(cb_empty(buffer), 0);
  ASSERT_EQ(cb_full(buffer), 0);
  ASSERT_EQ(cb_dequeue(buffer), &item1);
  ASSERT_EQ(cb_empty(buffer), 0);
  ASSERT_EQ(cb_full(buffer), 0);
  ASSERT_EQ(cb_dequeue(buffer), &item2);
  ASSERT_EQ(cb_empty(buffer), 0);
  ASSERT_EQ(cb_full(buffer), 0);
  ASSERT_EQ(cb_dequeue(buffer), &item3);
  ASSERT_EQ(cb_empty(buffer), 1);
  ASSERT_EQ(cb_full(buffer), 0);
  cb_free(buffer);
}

TEST(CircularBufferTest, EnqueueAndDequeueWithOverflow) {
  CircularBuffer* buffer = cb_new(3);
  ASSERT_NE(buffer, nullptr);
  ASSERT_EQ(cb_empty(buffer), 1);
  ASSERT_EQ(cb_full(buffer), 0);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  ASSERT_EQ(cb_enqueue(buffer, &item1), 0);
  ASSERT_EQ(cb_enqueue(buffer, &item2), 0);
  ASSERT_EQ(cb_enqueue(buffer, &item3), 0);
  ASSERT_EQ(cb_enqueue(buffer, &item4), -1);

  cb_free(buffer);
}
