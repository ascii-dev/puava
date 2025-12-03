#ifndef C_LLSTACK_H
#define C_LLSTACK_H
#include <stddef.h>

typedef struct LLStack LLStack;

LLStack* llstack_new();
void llstack_push(LLStack* stack, const void* item);
void* llstack_pop(LLStack* stack);
short llstack_empty(LLStack* stack);
void llstack_free(LLStack* stack);

#endif  // C_LLSTACK_H
