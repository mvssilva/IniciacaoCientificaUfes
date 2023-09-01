
#ifndef _STACK_H_
#define _STACK_H_

typedef unsigned char bool;
typedef struct Stack Stack;

Stack *stack_construct();
void stack_push(Stack *stack, void *data);
bool stack_empty(Stack *stack);
void *stack_pop(Stack *stack);
int stack_size(Stack * stack);
void stack_destroy(Stack *stack);

#endif