#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

typedef LinkedList Stack;

void stack_init();
void stack_add(char* value);
void stack_remove();
void stack_log();

#endif