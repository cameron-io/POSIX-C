#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* value;
    void* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} Stack;

Stack* stack;

void stack_init() {
    stack = (Stack*) malloc(sizeof(Stack));
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;
}

// unshift
void stack_add(char* value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    if (!stack->size) {
        node->next = NULL;
        stack->head = node;
        stack->tail = node;
    } else {
        Node* prev_head = (Node*) malloc(sizeof(Node));
        prev_head = stack->head;
        node->next = prev_head;
        stack->head = node;
    }
    stack->size++;
}

// shift
void stack_remove() {
    if (!stack->size) return;
    Node* prev_head = (Node*) malloc(sizeof(Node));
    prev_head = stack->head;
    stack->head = prev_head->next;
    if (!stack->head) stack->tail = NULL;
    stack->size--;
}

void stack_log() {
    if (!stack->head) return;
    Node* node = stack->head;
    while (node) {
        printf("-> %s\n", node->value);
        node = node->next;
    }
}

int main() {
    stack_init();
    stack_add("Ford");
    stack_add("Chevrolet");
    stack_add("Dodge");
    printf("Stack 1:\n");
    stack_log();
    printf("\n");
    stack_remove();
    printf("Stack 2:\n");
    stack_log();
}
