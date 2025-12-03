#include "includes/llstack.h"

#include <stdlib.h>

#include "includes/slinkedlist.h"

struct LLStack {
  SLinkedList* list;
};

LLStack* llstack_new() {
  LLStack* stack = malloc(sizeof(LLStack));
  if (stack == NULL) return NULL;

  stack->list = slinkedlist_new();
  return stack;
}

void llstack_push(LLStack* stack, const void* item) { slinkedlist_push_front(stack->list, item); }

void* llstack_pop(LLStack* stack) { return slinkedlist_pop_front(stack->list); }

short llstack_empty(LLStack* stack) { return slinkedlist_empty(stack->list); }

void llstack_free(LLStack* stack) {
  slinkedlist_free(stack->list);
  free(stack);
}
