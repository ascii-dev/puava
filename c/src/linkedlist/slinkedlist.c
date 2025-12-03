#include "includes/slinkedlist.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct SLinkedListNode {
  void* value;
  struct SLinkedListNode* next;
} SLinkedListNode;

struct SLinkedList {
  size_t size;
  SLinkedListNode* head;
  SLinkedListNode* tail;
};

SLinkedList* slinkedlist_new() {
  SLinkedList* list = malloc(sizeof(SLinkedList));
  if (list == NULL) return NULL;

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

size_t slinkedlist_size(SLinkedList* list) { return list->size; }

short slinkedlist_empty(SLinkedList* list) { return list->size == 0; }

void* slinkedlist_at(SLinkedList* list, int index) {
  if (index < 0 || index >= list->size) return NULL;

  SLinkedListNode* node = list->head;
  int i = 0;
  while (node != NULL && i < index) {
    node = node->next;
    i++;
  }

  if (node == NULL) return NULL;

  return node->value;
}

void slinkedlist_push_front(SLinkedList* list, const void* item) {
  SLinkedListNode* node = malloc(sizeof(SLinkedListNode));
  if (node == NULL) return;

  node->value = (void*)item;
  node->next = list->head;

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->head = node;
  }

  list->size++;
}

void* slinkedlist_pop_front(SLinkedList* list) {
  if (list->head == NULL) return NULL;

  void* value = list->head->value;
  SLinkedListNode* next = list->head->next;

  free(list->head);

  list->head = next;

  if (list->head == NULL) list->tail = NULL;

  list->size--;

  return value;
}

void slinkedlist_push_back(SLinkedList* list, const void* item) {
  SLinkedListNode* node = malloc(sizeof(SLinkedListNode));
  if (node == NULL) return;

  node->value = (void*)item;
  node->next = NULL;

  if (list->tail == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->size++;
}

void* slinkedlist_pop_back(SLinkedList* list) {
  if (list->tail == NULL) return NULL;

  void* value = list->tail->value;
  if (list->head == list->tail) {
    free(list->head);
    list->head = NULL;
    list->tail = NULL;
    list->size--;
    return value;
  }

  SLinkedListNode* prev = list->head;
  while (prev->next != list->tail) {
    prev = prev->next;
  }

  free(list->tail);
  list->tail = prev;
  list->tail->next = NULL;
  list->size--;

  return value;
}

void* slinkedlist_front(SLinkedList* list) {
  if (list->head == NULL) return NULL;

  return list->head->value;
}

void* slinkedlist_back(SLinkedList* list) {
  if (list->tail == NULL) return NULL;

  return list->tail->value;
}

void slinkedlist_insert(SLinkedList* list, int index, const void* item) {
  if (index < 0 || index > list->size) return;

  if (index == 0) {
    slinkedlist_push_front(list, item);
  } else if (index == list->size) {
    slinkedlist_push_back(list, item);
  } else {
    SLinkedListNode* prev = list->head;
    int i = 0;
    while (prev != NULL && i < index - 1) {
      prev = prev->next;
      i++;
    }

    if (prev == NULL) return;

    SLinkedListNode* node = malloc(sizeof(SLinkedListNode));
    if (node == NULL) return;

    node->value = (void*)item;
    node->next = prev->next;
    prev->next = node;

    if (node->next == NULL) list->tail = node;

    list->size++;
  }
}

void slinkedlist_erase(SLinkedList* list, int index) {
  if (index < 0 || index >= list->size) return;

  if (index == 0) {
    slinkedlist_pop_front(list);
  } else if (index == list->size - 1) {
    slinkedlist_pop_back(list);
  } else {
    SLinkedListNode* prev = list->head;
    int i = 0;
    while (prev != NULL && i < index - 1) {
      prev = prev->next;
      i++;
    }

    if (prev == NULL) return;

    SLinkedListNode* target = prev->next;
    if (target == NULL) return;

    prev->next = target->next;
    if (target->next == NULL) list->tail = prev;

    free(target);
    list->size--;
  }
}

void* slinkedlist_value_n_from_end(SLinkedList* list, int n) {
  if (n < 0 || n >= list->size) return NULL;

  SLinkedListNode* first = list->head;
  int i = 0;
  while (first != NULL && i < list->size - n - 1) {
    first = first->next;
    i++;
  }

  if (first == NULL) return NULL;

  return first->value;
}

void slinkedlist_reverse(SLinkedList* list) {
  if (list->head == NULL || list->head->next == NULL) {
    return;
  }

  SLinkedListNode* new_tail = list->head;
  SLinkedListNode* prev = NULL;
  SLinkedListNode* current = list->head;
  SLinkedListNode* next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }

  list->head = prev;
  list->tail = new_tail;
}

void slinkedlist_remove_value(SLinkedList* list, const void* value) {
  SLinkedListNode* prev = NULL;
  SLinkedListNode* current = list->head;
  while (current != NULL && current->value != value) {
    prev = current;
    current = current->next;
  }

  if (current == NULL) return;

  if (prev == NULL) {
    slinkedlist_pop_front(list);
  } else {
    prev->next = current->next;
    if (current->next == NULL) list->tail = prev;
    free(current);
    list->size--;
  }
}

void slinkedlist_free(SLinkedList* list) {
  SLinkedListNode* current = list->head;
  while (current != NULL) {
    SLinkedListNode* next = current->next;
    free(current);
    current = next;
  }
  free(list);
}
