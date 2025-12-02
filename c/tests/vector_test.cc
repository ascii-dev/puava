#include "gtest/gtest.h"

extern "C" {
#include "includes/vector.h"
}

TEST(VectorTest, NewVector) {
  Vector* vector = vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(vector_size(vector), 0);
  ASSERT_EQ(vector_capacity(vector), 16);
  vector_free(vector);
}

TEST(VectorTest, PushTriggersResize) {
  // 1. Create vector (Clamped to 16 internally)
  Vector* vector = vector_new(1);
  ASSERT_EQ(vector_capacity(vector), 16);

  int item = 42;

  // 2. Fill it exactly to the limit
  for (int i = 0; i < 16; i++) {
    vector_push(vector, &item);
  }
  ASSERT_EQ(vector_size(vector), 16);
  ASSERT_EQ(vector_capacity(vector), 16);  // Still 16

  // 3. The Trigger (The 17th Element)
  vector_push(vector, &item);

  // 4. Verify the Resize (Doubling)
  ASSERT_EQ(vector_size(vector), 17);
  ASSERT_EQ(vector_capacity(vector), 32);  // 16 * 2 = 32

  vector_free(vector);
}

TEST(VectorTest, PushAndPop) {
  Vector* vector = vector_new(2);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;

  vector_push(vector, &item1);
  vector_push(vector, &item2);
  vector_push(vector, &item3);

  // Test At (Pointer Arithmetic Check)
  int* retrieved = (int*)vector_at(vector, 1);
  ASSERT_EQ(*retrieved, 20);

  // Test Pop
  int* popped = (int*)vector_pop(vector);
  ASSERT_EQ(*popped, 30);
  ASSERT_EQ(vector_size(vector), 2);

  vector_free(vector);
}

TEST(VectorTest, InsertAndDelete) {
  Vector* vector = vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(vector_size(vector), 0);
  ASSERT_EQ(vector_capacity(vector), 16);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  vector_push(vector, &item1);
  vector_push(vector, &item2);
  vector_push(vector, &item3);
  vector_push(vector, &item4);
  vector_push(vector, &item5);
  ASSERT_EQ(vector_size(vector), 5);
  ASSERT_EQ(vector_capacity(vector), 16);

  // Test Insert
  int item6 = 60;
  vector_insert(vector, 2, &item6);
  ASSERT_EQ(vector_size(vector), 6);
  ASSERT_EQ(vector_capacity(vector), 16);
  ASSERT_EQ(vector_at(vector, 2), &item6);

  // Test Delete
  vector_delete(vector, 2);
  ASSERT_EQ(vector_size(vector), 5);
  ASSERT_EQ(vector_capacity(vector), 16);
  ASSERT_EQ(vector_at(vector, 2), &item3);

  vector_free(vector);
}

TEST(VectorTest, PrependAndFind) {
  Vector* vector = vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(vector_size(vector), 0);
  ASSERT_EQ(vector_capacity(vector), 16);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  vector_push(vector, &item1);
  vector_push(vector, &item2);
  vector_push(vector, &item3);
  vector_push(vector, &item4);
  vector_push(vector, &item5);
  ASSERT_EQ(vector_size(vector), 5);
  ASSERT_EQ(vector_capacity(vector), 16);

  // Test Prepend
  int item6 = 60;
  vector_prepend(vector, &item6);
  ASSERT_EQ(vector_size(vector), 6);
  ASSERT_EQ(vector_capacity(vector), 16);  // Still 16

  // Test Find
  int index = vector_find(vector, &item3);
  ASSERT_EQ(index, 3);
  index = vector_find(vector, &item6);
  ASSERT_EQ(index, 0);

  vector_free(vector);
}

TEST(VectorTest, RemoveAndEmpty) {
  Vector* vector = vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(vector_size(vector), 0);
  ASSERT_EQ(vector_capacity(vector), 16);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  vector_push(vector, &item1);
  vector_push(vector, &item2);
  vector_push(vector, &item3);
  vector_push(vector, &item4);
  vector_push(vector, &item5);
  ASSERT_EQ(vector_size(vector), 5);
  ASSERT_EQ(vector_capacity(vector), 16);

  // Test Remove
  vector_remove(vector, &item3);
  ASSERT_EQ(vector_size(vector), 4);
  ASSERT_EQ(vector_capacity(vector), 8);
  ASSERT_EQ(vector_at(vector, 2), &item4);

  // Test Empty
  ASSERT_EQ(vector_empty(vector), 0);

  vector_pop(vector);
  vector_pop(vector);
  vector_pop(vector);
  vector_pop(vector);
  ASSERT_EQ(vector_capacity(vector), 2);
  ASSERT_EQ(vector_empty(vector), 1);

  vector_free(vector);
}
