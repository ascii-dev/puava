#include "gtest/gtest.h"

extern "C" {
#include "includes/puava_vector.h"
}

TEST(PuavaVectorTest, NewVector) {
  PuavaVector* vector = puava_vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(puava_vector_size(vector), 0);
  ASSERT_EQ(puava_vector_capacity(vector), 16);
  puava_vector_free(vector);
}

TEST(PuavaVectorTest, PushTriggersResize) {
  // 1. Create vector (Clamped to 16 internally)
  PuavaVector* vector = puava_vector_new(1);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  int item = 42;

  // 2. Fill it exactly to the limit
  for (int i = 0; i < 16; i++) {
    puava_vector_push(vector, &item);
  }
  ASSERT_EQ(puava_vector_size(vector), 16);
  ASSERT_EQ(puava_vector_capacity(vector), 16);  // Still 16

  // 3. The Trigger (The 17th Element)
  puava_vector_push(vector, &item);

  // 4. Verify the Resize (Doubling)
  ASSERT_EQ(puava_vector_size(vector), 17);
  ASSERT_EQ(puava_vector_capacity(vector), 32);  // 16 * 2 = 32

  puava_vector_free(vector);
}

TEST(PuavaVectorTest, PushAndPop) {
  PuavaVector* vector = puava_vector_new(2);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;

  puava_vector_push(vector, &item1);
  puava_vector_push(vector, &item2);
  puava_vector_push(vector, &item3);

  // Test At (Pointer Arithmetic Check)
  int* retrieved = (int*)puava_vector_at(vector, 1);
  ASSERT_EQ(*retrieved, 20);

  // Test Pop
  int* popped = (int*)puava_vector_pop(vector);
  ASSERT_EQ(*popped, 30);
  ASSERT_EQ(puava_vector_size(vector), 2);

  puava_vector_free(vector);
}

TEST(PuavaVectorTest, InsertAndDelete) {
  PuavaVector* vector = puava_vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(puava_vector_size(vector), 0);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  puava_vector_push(vector, &item1);
  puava_vector_push(vector, &item2);
  puava_vector_push(vector, &item3);
  puava_vector_push(vector, &item4);
  puava_vector_push(vector, &item5);
  ASSERT_EQ(puava_vector_size(vector), 5);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  // Test Insert
  int item6 = 60;
  puava_vector_insert(vector, 2, &item6);
  ASSERT_EQ(puava_vector_size(vector), 6);
  ASSERT_EQ(puava_vector_capacity(vector), 16);
  ASSERT_EQ(puava_vector_at(vector, 2), &item6);

  // Test Delete
  puava_vector_delete(vector, 2);
  ASSERT_EQ(puava_vector_size(vector), 5);
  ASSERT_EQ(puava_vector_capacity(vector), 16);
  ASSERT_EQ(puava_vector_at(vector, 2), &item3);

  puava_vector_free(vector);
}

TEST(PuavaVectorTest, PrependAndFind) {
  PuavaVector* vector = puava_vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(puava_vector_size(vector), 0);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  puava_vector_push(vector, &item1);
  puava_vector_push(vector, &item2);
  puava_vector_push(vector, &item3);
  puava_vector_push(vector, &item4);
  puava_vector_push(vector, &item5);
  ASSERT_EQ(puava_vector_size(vector), 5);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  // Test Prepend
  int item6 = 60;
  puava_vector_prepend(vector, &item6);
  ASSERT_EQ(puava_vector_size(vector), 6);
  ASSERT_EQ(puava_vector_capacity(vector), 16);  // Still 16

  // Test Find
  int index = puava_vector_find(vector, &item3);
  ASSERT_EQ(index, 3);
  index = puava_vector_find(vector, &item6);
  ASSERT_EQ(index, 0);

  puava_vector_free(vector);
}

TEST(PuavaVectorTest, RemoveAndEmpty) {
  PuavaVector* vector = puava_vector_new(10);
  ASSERT_NE(vector, nullptr);
  ASSERT_EQ(puava_vector_size(vector), 0);
  ASSERT_EQ(puava_vector_capacity(vector), 16);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;

  puava_vector_push(vector, &item1);
  puava_vector_push(vector, &item2);
  puava_vector_push(vector, &item3);
  puava_vector_push(vector, &item4);
  puava_vector_push(vector, &item5);
  ASSERT_EQ(puava_vector_size(vector), 5);
  ASSERT_EQ(puava_vector_capacity(vector), 16);

  // Test Remove
  puava_vector_remove(vector, &item3);
  ASSERT_EQ(puava_vector_size(vector), 4);
  ASSERT_EQ(puava_vector_capacity(vector), 8);
  ASSERT_EQ(puava_vector_at(vector, 2), &item4);

  // Test Empty
  ASSERT_EQ(puava_vector_empty(vector), 0);

  puava_vector_pop(vector);
  puava_vector_pop(vector);
  puava_vector_pop(vector);
  puava_vector_pop(vector);
  ASSERT_EQ(puava_vector_size(vector), 0);
  ASSERT_EQ(puava_vector_capacity(vector), 2);
  ASSERT_EQ(puava_vector_empty(vector), 1);

  puava_vector_free(vector);
}
