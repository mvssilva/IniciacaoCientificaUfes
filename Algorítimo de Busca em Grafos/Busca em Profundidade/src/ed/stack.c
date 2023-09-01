#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct NodeStack NodeStack;

struct NodeStack{
    void * data;
    NodeStack * next;
};

struct Stack{   
    NodeStack * head;
    NodeStack * last;
    int size;
};

Stack *stack_construct(){
    Stack * s = (Stack*)malloc(sizeof(Stack));
    s->head= NULL;
    s->last = NULL;
    s->size = 0;
    return s;
}

NodeStack * _node_stack_construct(NodeStack * next, void * data){
    NodeStack * n = (NodeStack *)malloc(sizeof(NodeStack));
    n->next = next;
    n->data = data;
    return n;
}

void stack_push(Stack *s, void *data){
    NodeStack * n = s->head;
    NodeStack * new = _node_stack_construct(NULL, data);

    if(n == NULL){
        s->last = s->head = new;
    }
    else{
        new->next = n;
        s->head = new;
    }
    s->size++;
}

bool stack_empty(Stack *stack){
    if(stack->size == 0)
        return 1;
    else
        return 0;
}

void *stack_pop(Stack *stack){

    if(stack == NULL || stack->head == NULL)
        return NULL;
    else{
        NodeStack * n = stack->head;
        void * aux = n->data;
        stack->head = n->next;

        if(stack->head == NULL)
            stack->last = NULL;
        
        stack->size--;
        free(n);
        return aux;
    }
}

int stack_size(Stack * stack){
    return stack->size;
}

void stack_destroy(Stack *stack){
    NodeStack * n = stack->head;

    while(n != NULL){
        NodeStack * aux = n->next;
        free(n);
        n = aux;
    }

    free(stack);
}