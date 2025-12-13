#include "includes/llqueue.h"

#include <stdlib.h>

#include "includes/slinkedlist.h"

struct LLQueue {
  SLinkedList* list;
};

LLQueue* llq_new() {
  LLQueue* queue = malloc(sizeof(LLQueue));
  if (queue == NULL) return NULL;

  queue->list = slinkedlist_new();
  if (queue->list == NULL) {
    free(queue);
    return NULL;
  }

  return queue;
}

void llq_free(LLQueue* queue) {
  slinkedlist_free(queue->list);
  free(queue);
}

short llq_empty(LLQueue* queue) { return slinkedlist_empty(queue->list); }

void llq_enqueue(LLQueue* queue, const void* item) {
  return slinkedlist_push_back(queue->list, item);
}

void* llq_dequeue(LLQueue* queue) { return slinkedlist_pop_front(queue->list); }
