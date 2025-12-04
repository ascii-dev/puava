#include "includes/arrstack.h"

#include <stdlib.h>

#include "includes/vector.h"

struct ArrStack {
  Vector* vector;
};

ArrStack* arrstack_new() {
  ArrStack* stack = malloc(sizeof(ArrStack));
  if (stack == NULL) return NULL;

  stack->vector = vector_new(10);
  if (stack->vector == NULL) {
    free(stack);
    return NULL;
  }
  return stack;
}

void arrstack_push(ArrStack* stack, const void* item) { vector_push(stack->vector, item); }

void* arrstack_pop(ArrStack* stack) { return vector_pop(stack->vector); }

short arrstack_empty(ArrStack* stack) { return vector_empty(stack->vector); }

void arrstack_free(ArrStack* stack) {
  vector_free(stack->vector);
  free(stack);
}
