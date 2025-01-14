#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

typedef LinkedList Queue;

void queue_init();
void queue_add(char* value);
void queue_remove();
void queue_log();

#endif