#include <stdlib.h>
#include <stdio.h>

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

LinkedList* dll;

void dll_init() {
    dll = (LinkedList*) malloc(sizeof(LinkedList));
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
}

void dll_push(char* value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    if (!dll->head) {
        node->next = NULL;
        node->previous = NULL;
        dll->head = node;
        dll->tail = node;
    } else {
        Node* prev_tail = (Node*) malloc(sizeof(Node));
        prev_tail = dll->tail;
        prev_tail->next = node;
        node->previous = prev_tail;
        dll->tail = node;
    }
    dll->size++;
}

void dll_pop() {
    if (!dll->size) return;
    Node* prev_tail = (Node*) malloc(sizeof(Node));
    prev_tail = dll->tail;
    if (dll->size == 1) {
        dll->head = NULL;
        dll->tail = NULL;
    } else {
        dll->tail = prev_tail->previous;
        dll->tail->next = NULL;
    }
    free(prev_tail);
    dll->size--;
}

void dll_log() {
    Node* node = (Node*) malloc(sizeof(Node));
    node = dll->head;
    while (node) {
        printf("-> %s\n", node->value);
        node = node->next;
    }
}

int main() {
    dll_init();
    dll_push("Ford");
    dll_push("Chevrolet");
    dll_push("Dodge");
    dll_push("Ferrari");
    dll_push("Lamborghini");
    printf("DLL 1:\n");
    dll_log();
    printf("\n");
    dll_pop();
    dll_pop();
    printf("DLL 2:\n");
    dll_log();

    return 0;
}

