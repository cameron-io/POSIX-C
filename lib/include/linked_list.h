#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct {
    char* value;
    void* next;
    void* previous;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

#endif