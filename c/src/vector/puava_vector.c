#include "includes/puava_vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct PuavaVector {
  size_t size;
  size_t capacity;
  void** data;
};

static void resize(PuavaVector* vector, size_t new_capacity) {
  void** new_data = realloc(vector->data, new_capacity * sizeof(void*));
  if (new_data == NULL) return;

  vector->data = new_data;
  vector->capacity = new_capacity;
}

uint32_t next_power_of_2(uint32_t n) {
  if (n == 0) return 1;

  n--;

  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;

  return n + 1;
}

PuavaVector* puava_vector_new(int capacity) {
  PuavaVector* vector = malloc(sizeof(PuavaVector));
  if (!vector) return NULL;

  if (capacity < 16) capacity = 16;
  capacity = next_power_of_2(capacity);

  vector->size = 0;
  vector->capacity = capacity;
  vector->data = calloc(capacity, sizeof(void*));

  if (!vector->data) {
    free(vector);
    return NULL;
  }

  return vector;
}

size_t puava_vector_size(PuavaVector* vector) { return vector->size; }

size_t puava_vector_capacity(PuavaVector* vector) { return vector->capacity; }

short puava_vector_empty(PuavaVector* vector) { return vector->size == 0; }

void puava_vector_push(PuavaVector* vector, const void* item) {
  if (vector->size == vector->capacity) {
    resize(vector, vector->capacity * 2);
  }

  *(vector->data + vector->size) = (void*)item;
  vector->size++;
}

void* puava_vector_at(PuavaVector* vector, int index) {
  if (index < 0 || index >= vector->size) return NULL;

  return *(vector->data + index);
}

void puava_vector_insert(PuavaVector* vector, int index, const void* item) {
  if (index < 0 || index > vector->size) return;

  if (vector->size == vector->capacity) {
    resize(vector, vector->capacity * 2);
  }

  memmove(vector->data + index + 1, vector->data + index, (vector->size - index) * sizeof(void*));

  *(vector->data + index) = (void*)item;
  vector->size++;
}

void puava_vector_prepend(PuavaVector* vector, const void* item) {
  puava_vector_insert(vector, 0, item);
}

void* puava_vector_pop(PuavaVector* vector) {
  if (vector->size == 0) return NULL;

  void* item = *(vector->data + (vector->size - 1));
  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    resize(vector, vector->capacity / 2);

  return item;
}

void puava_vector_delete(PuavaVector* vector, int index) {
  if (index < 0 || index >= vector->size) return;

  memmove(vector->data + index, vector->data + index + 1,
          (vector->size - index - 1) * sizeof(void*));

  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    resize(vector, vector->capacity / 2);
}

void puava_vector_remove(PuavaVector* vector, const void* item) {
  for (size_t i = 0; i < vector->size; i++)
    if (*(vector->data + i) == item) {
      puava_vector_delete(vector, i);
      return;
    }
}

size_t puava_vector_find(PuavaVector* vector, const void* item) {
  for (size_t i = 0; i < vector->size; i++)
    if (*(vector->data + i) == item) return i;  // Return index found
  return -1;                                    // Not found
}

void puava_vector_free(PuavaVector* vector) {
  free(vector->data);
  free(vector);
}
