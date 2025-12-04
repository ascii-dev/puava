#ifndef ARRSTACK_H
#define ARRSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ArrStack ArrStack;

ArrStack* arrstack_new();
void arrstack_push(ArrStack* stack, const void* item);
void* arrstack_pop(ArrStack* stack);
short arrstack_empty(ArrStack* stack);
void arrstack_free(ArrStack* stack);

#endif
