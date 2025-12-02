#include "includes/vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
  size_t size;
  size_t capacity;
  void** data;
};

static void resize(Vector* vector, size_t new_capacity) {
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

Vector* vector_new(int capacity) {
  Vector* vector = malloc(sizeof(Vector));
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

size_t vector_size(Vector* vector) { return vector->size; }

size_t vector_capacity(Vector* vector) { return vector->capacity; }

short vector_empty(Vector* vector) { return vector->size == 0; }

void vector_push(Vector* vector, const void* item) {
  if (vector->size == vector->capacity) {
    resize(vector, vector->capacity * 2);
  }

  *(vector->data + vector->size) = (void*)item;
  vector->size++;
}

void* vector_at(Vector* vector, int index) {
  if (index < 0 || index >= vector->size) return NULL;

  return *(vector->data + index);
}

void vector_insert(Vector* vector, int index, const void* item) {
  if (index < 0 || index > vector->size) return;

  if (vector->size == vector->capacity) {
    resize(vector, vector->capacity * 2);
  }

  memmove(vector->data + index + 1, vector->data + index, (vector->size - index) * sizeof(void*));

  *(vector->data + index) = (void*)item;
  vector->size++;
}

void vector_prepend(Vector* vector, const void* item) { vector_insert(vector, 0, item); }

void* vector_pop(Vector* vector) {
  if (vector->size == 0) return NULL;

  void* item = *(vector->data + (vector->size - 1));
  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    resize(vector, vector->capacity / 2);

  return item;
}

void vector_delete(Vector* vector, int index) {
  if (index < 0 || index >= vector->size) return;

  memmove(vector->data + index, vector->data + index + 1,
          (vector->size - index - 1) * sizeof(void*));

  vector->size--;

  if (vector->size > 0 && vector->size == vector->capacity / 4)
    resize(vector, vector->capacity / 2);
}

void vector_remove(Vector* vector, const void* item) {
  for (size_t i = 0; i < vector->size; i++)
    if (*(vector->data + i) == item) {
      vector_delete(vector, i);
      return;
    }
}

size_t vector_find(Vector* vector, const void* item) {
  for (size_t i = 0; i < vector->size; i++)
    if (*(vector->data + i) == item) return i;  // Return index found
  return -1;                                    // Not found
}

void vector_free(Vector* vector) {
  free(vector->data);
  free(vector);
}
