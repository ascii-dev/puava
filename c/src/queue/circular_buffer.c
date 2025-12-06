#include "includes/circular_buffer.h"

#include <stdlib.h>

struct CircularBuffer {
  void** data;
  size_t capacity;
  size_t size;
  size_t head;
  size_t tail;
};

CircularBuffer* cb_new(size_t capacity) {
  CircularBuffer* buffer = malloc(sizeof(CircularBuffer));
  if (buffer == NULL) return NULL;

  buffer->data = calloc(capacity, sizeof(void*));
  if (buffer->data == NULL) {
    free(buffer);
    return NULL;
  }

  buffer->capacity = capacity;
  buffer->size = 0;
  buffer->head = 0;
  buffer->tail = 0;

  return buffer;
}

short cb_empty(CircularBuffer* buffer) { return buffer->size == 0; }

short cb_full(CircularBuffer* buffer) { return buffer->size == buffer->capacity; }

short cb_enqueue(CircularBuffer* buffer, const void* item) {
  if (cb_full(buffer)) return -1;

  buffer->data[buffer->tail] = (void*)item;
  buffer->tail = (buffer->tail + 1) % buffer->capacity;
  buffer->size++;
  return 0;
}

void* cb_dequeue(CircularBuffer* buffer) {
  if (cb_empty(buffer)) return NULL;

  void** item = buffer->data[buffer->head];
  buffer->head = (buffer->head + 1) % buffer->capacity;
  buffer->size--;
  return item;
}

void cb_free(CircularBuffer* buffer) {
  free(buffer->data);
  free(buffer);
}
