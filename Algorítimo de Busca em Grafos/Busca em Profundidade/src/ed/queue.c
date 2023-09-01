#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct NodeQueue NodeQueue;

struct NodeQueue{
    NodeQueue * next;
    void * celula; 
};

struct Queue{
    NodeQueue * head;
    NodeQueue * last;
    int size;
};

NodeQueue * _node_construct(NodeQueue * next, void * data){
    NodeQueue * n = (NodeQueue *)malloc(sizeof(NodeQueue));
    n->next = next;
    n->celula = data;
    return n;
}

Queue *queue_construct(){
    Queue * q = (Queue*)malloc(sizeof(Queue));
    q->head = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

void queue_push(Queue *q, void *data){
    NodeQueue * n = q->last;
    NodeQueue * new = _node_construct(NULL, data);

    if(n == NULL){
        q->last = q->head = new;
    }
    else{
        q->last->next = new;
        q->last = new;
    }
    q->size++;
}

bool queue_empty(Queue *queue){
    if(queue->size == 0)
        return 1;
    else
        return 0;
}

void _node_destruct(NodeQueue * n){
    free(n);
}


void *queue_pop(Queue *q){
    if(q == NULL || q->head == NULL)
        return NULL;
    else{
        NodeQueue * n = q->head;
        void * aux = n->celula;
        q->head = n->next;

        if(q->head == NULL)
            q->last = NULL;
        
        q->size--;
        free(n);
        return aux;
    }
}

void queue_destroy(Queue *q){
    NodeQueue * n = q->head;

    while(n != NULL){
        NodeQueue * salvar = n->next;
        _node_destruct(n);
        n = salvar;
    }

    free(q);
}