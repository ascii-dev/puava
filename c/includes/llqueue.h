#ifndef LLQUEUE_H
#define LLQUEUE_H

#include <stddef.h>

typedef struct LLQueue LLQueue;

LLQueue* llq_new();
void llq_free(LLQueue* queue);
short llq_empty(LLQueue* queue);
void llq_enqueue(LLQueue* queue, const void* item);
void* llq_dequeue(LLQueue* queue);

#endif  // LLQUEUE_H
