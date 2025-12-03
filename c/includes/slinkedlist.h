#ifndef C_SLINKEDLIST_H
#define C_SLINKEDLIST_H
#include <stddef.h>

typedef struct SLinkedList SLinkedList;

SLinkedList* slinkedlist_new();
size_t slinkedlist_size(SLinkedList* list);
short slinkedlist_empty(SLinkedList* list);
void* slinkedlist_at(SLinkedList* list, int index);
void slinkedlist_push_front(SLinkedList* list, const void* item);
void* slinkedlist_pop_front(SLinkedList* list);
void slinkedlist_push_back(SLinkedList* list, const void* item);
void* slinkedlist_pop_back(SLinkedList* list);
void* slinkedlist_front(SLinkedList* list);
void* slinkedlist_back(SLinkedList* list);
void slinkedlist_insert(SLinkedList* list, int index, const void* item);
void slinkedlist_erase(SLinkedList* list, int index);
void* slinkedlist_value_n_from_end(SLinkedList* list, int n);
void slinkedlist_reverse(SLinkedList* list);
void slinkedlist_remove_value(SLinkedList* list, const void* value);
void slinkedlist_free(SLinkedList* list);

#endif  // C_SLINKEDLIST_H
