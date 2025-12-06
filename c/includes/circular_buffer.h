#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include <stddef.h>

typedef struct CircularBuffer CircularBuffer;

CircularBuffer* cb_new(size_t capacity);
short cb_enqueue(CircularBuffer* buffer, const void* item);
void* cb_dequeue(CircularBuffer* buffer);
short cb_empty(CircularBuffer* buffer);
short cb_full(CircularBuffer* buffer);
void cb_free(CircularBuffer* buffer);

#endif  // CIRCULAR_BUFFER_H
