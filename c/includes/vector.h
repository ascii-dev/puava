#ifndef C_VECTOR_H
#define C_VECTOR_H
#include <stddef.h>

typedef struct Vector Vector;

Vector* vector_new(int capacity);
size_t vector_size(Vector* vector);
size_t vector_capacity(Vector* vector);
short vector_empty(Vector* vector);
void vector_push(Vector* vector, const void* item);
void* vector_at(Vector* vector, int index);
void vector_insert(Vector* vector, int index, const void* item);
void vector_prepend(Vector* vector, const void* item);
void* vector_pop(Vector* vector);
void vector_delete(Vector* vector, int index);
void vector_remove(Vector* vector, const void* item);
size_t vector_find(Vector* vector, const void* item);
void vector_free(Vector* vector);

#endif  // C_VECTOR_H
