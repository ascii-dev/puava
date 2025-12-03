#include "gtest/gtest.h"

extern "C" {
#include "includes/slinkedlist.h"
}

TEST(SLinkedListTest, NewSLinkedList) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  slinkedlist_free(list);
}

TEST(SLinkedListTest, PushFrontAndPopFront) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  int item2 = 20;
  slinkedlist_push_front(list, &item1);
  slinkedlist_push_front(list, &item2);
  ASSERT_EQ(slinkedlist_size(list), 2);
  ASSERT_EQ(slinkedlist_empty(list), 0);
  ASSERT_EQ(slinkedlist_front(list), &item2);
  ASSERT_EQ(slinkedlist_back(list), &item1);
  ASSERT_EQ(slinkedlist_at(list, 0), &item2);
  ASSERT_EQ(slinkedlist_at(list, 1), &item1);
  ASSERT_EQ(slinkedlist_pop_front(list), &item2);
  ASSERT_EQ(slinkedlist_size(list), 1);
  ASSERT_EQ(slinkedlist_empty(list), 0);

  slinkedlist_free(list);
}

TEST(SLinkedListTest, PushBackAndPopBack) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  slinkedlist_push_back(list, &item1);
  ASSERT_EQ(slinkedlist_size(list), 1);
  ASSERT_EQ(slinkedlist_empty(list), 0);
  ASSERT_EQ(slinkedlist_front(list), &item1);
  ASSERT_EQ(slinkedlist_back(list), &item1);
  ASSERT_EQ(slinkedlist_at(list, 0), &item1);
  ASSERT_EQ(slinkedlist_pop_back(list), &item1);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  ASSERT_EQ(slinkedlist_front(list), nullptr);
  ASSERT_EQ(slinkedlist_back(list), nullptr);
  ASSERT_EQ(slinkedlist_at(list, 0), nullptr);
  ASSERT_EQ(slinkedlist_pop_back(list), nullptr);

  slinkedlist_free(list);
}

TEST(SLinkedListTest, InsertAndErase) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  slinkedlist_insert(list, 0, &item1);
  ASSERT_EQ(slinkedlist_size(list), 1);
  ASSERT_EQ(slinkedlist_empty(list), 0);
  ASSERT_EQ(slinkedlist_front(list), &item1);
  ASSERT_EQ(slinkedlist_back(list), &item1);
  ASSERT_EQ(slinkedlist_at(list, 0), &item1);
  ASSERT_EQ(slinkedlist_pop_back(list), &item1);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  ASSERT_EQ(slinkedlist_front(list), nullptr);
  ASSERT_EQ(slinkedlist_back(list), nullptr);
  ASSERT_EQ(slinkedlist_at(list, 0), nullptr);
  ASSERT_EQ(slinkedlist_pop_back(list), nullptr);

  slinkedlist_free(list);
}

TEST(SLinkedListTest, ValueNFromEnd) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;
  slinkedlist_push_back(list, &item1);
  slinkedlist_push_back(list, &item2);
  slinkedlist_push_back(list, &item3);
  slinkedlist_push_back(list, &item4);
  slinkedlist_push_back(list, &item5);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 0), &item5);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 1), &item4);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 2), &item3);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 3), &item2);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 4), &item1);
  ASSERT_EQ(slinkedlist_value_n_from_end(list, 5), nullptr);

  slinkedlist_free(list);
}

TEST(SLinkedListTest, Reverse) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  int item2 = 20;
  int item3 = 30;
  int item4 = 40;
  int item5 = 50;
  slinkedlist_push_back(list, &item1);
  slinkedlist_push_back(list, &item2);
  slinkedlist_push_back(list, &item3);
  slinkedlist_push_back(list, &item4);
  slinkedlist_push_back(list, &item5);
  slinkedlist_reverse(list);
  ASSERT_EQ(slinkedlist_size(list), 5);
  ASSERT_EQ(slinkedlist_empty(list), 0);
  ASSERT_EQ(slinkedlist_front(list), &item5);
  ASSERT_EQ(slinkedlist_back(list), &item1);
  ASSERT_EQ(slinkedlist_at(list, 0), &item5);
  ASSERT_EQ(slinkedlist_at(list, 1), &item4);
  ASSERT_EQ(slinkedlist_at(list, 2), &item3);
  ASSERT_EQ(slinkedlist_at(list, 3), &item2);
  ASSERT_EQ(slinkedlist_at(list, 4), &item1);

  slinkedlist_free(list);
}

TEST(SLinkedListTest, RemoveValue) {
  SLinkedList* list = slinkedlist_new();
  ASSERT_NE(list, nullptr);
  ASSERT_EQ(slinkedlist_size(list), 0);
  ASSERT_EQ(slinkedlist_empty(list), 1);
  int item1 = 10;
  int item2 = 20;
  slinkedlist_push_front(list, &item1);
  slinkedlist_push_front(list, &item2);
  ASSERT_EQ(slinkedlist_size(list), 2);

  slinkedlist_remove_value(list, &item1);
  ASSERT_EQ(slinkedlist_size(list), 1);
  ASSERT_EQ(slinkedlist_empty(list), 0);
  ASSERT_EQ(slinkedlist_front(list), &item2);
  ASSERT_EQ(slinkedlist_back(list), &item2);

  slinkedlist_free(list);
}
