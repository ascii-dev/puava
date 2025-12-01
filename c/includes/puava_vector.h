#ifndef C_PUAVA_VECTOR_H
#define C_PUAVA_VECTOR_H
#include <stddef.h>

typedef struct PuavaVector PuavaVector;

PuavaVector* puava_vector_new(int capacity);
size_t puava_vector_size(PuavaVector* vector);
size_t puava_vector_capacity(PuavaVector* vector);
short puava_vector_empty(PuavaVector* vector);
void puava_vector_push(PuavaVector* vector, const void* item);
void* puava_vector_at(PuavaVector* vector, int index);
void puava_vector_insert(PuavaVector* vector, int index, const void* item);
void puava_vector_prepend(PuavaVector* vector, const void* item);
void* puava_vector_pop(PuavaVector* vector);
void puava_vector_delete(PuavaVector* vector, int index);
void puava_vector_remove(PuavaVector* vector, const void* item);
size_t puava_vector_find(PuavaVector* vector, const void* item);
void puava_vector_free(PuavaVector* vector);

#endif  // C_PUAVA_VECTOR_H
