#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

Queue* queue;

void queue_init() {
    queue = (Queue*) malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

// Enqueue -> Push to end
void queue_add(char* value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    if (!queue->head) {
        node->next = NULL;
        queue->head = node;
        queue->tail = node;
    } else {
        Node* prev_tail = (Node*) malloc(sizeof(Node));
        prev_tail = queue->tail;
        prev_tail->next = node;
        queue->tail = node;
    }
    queue->size++;
}

// Dequeue -> Shift from front
void queue_remove() {
    if (!queue->head) return;
    if (queue->size == 1) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        Node* prev_head = (Node*) malloc(sizeof(Node));
        prev_head = queue->head;
        queue->head = prev_head->next;
        free(prev_head);
    }
    queue->size--;
}

void queue_log() {
    Node* node = (Node*) malloc(sizeof(Node));
    node = queue->head;
    while (node) {
        printf("-> %s\n", node->value);
        node = node->next;
    }
}
