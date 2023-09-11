#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct NodeList{
    NodeList * next;
    void * data;
};

struct ForwardList{
    NodeList * head;
    NodeList * last;
    int size;
};

ForwardList * forward_list_construct(){
    ForwardList * f = (ForwardList*)malloc(sizeof(ForwardList));
    f->head = NULL;
    f->last = NULL;
    f->size = 0;
    return f;
}

NodeList *_node_list_construct(void * data, NodeList * next){
    NodeList* n = (NodeList*)malloc(sizeof(NodeList));
    n->data = data;
    n->next = next;
    return n;
}

void forward_list_push_back(ForwardList* f, void* data){
    //adicionando novo nó no final da fila
    NodeList * new = _node_list_construct(data, NULL);
    NodeList * n = f->last;

    if(n == NULL){
        f->head = f->last = new;
        f->size++;
    }
    else{
        f->last->next = new;
        f->last = new;
        f->size++;
    }

}

void forward_list_destruct(ForwardList* f){
    NodeList * n = f->head;

    while(n != NULL){
        NodeList* aux = n->next;
        free(n);
        n = aux;
    }
    free(f);
}

void *forward_list_pop_front(ForwardList* f){
    NodeList * n = f->head;

    if(n == NULL)
        return NULL;

    void * salvar = n->data;
    f->head = n->next;
    free(n);
    f->size--;

    if(f->head == NULL)
        f->last = NULL;

    return salvar;
}

int forward_return_size(ForwardList *f){
    return f->size;
}

void forward_list_remove(ForwardList * f, void * data){
    NodeList * n = f->head;
    NodeList * prev = NULL;
    NodeList * new_n = NULL;
    
    while(n != NULL){
        if(n->data == data){
            if (prev == NULL)
                f->head = new_n = n->next;
            else
                prev->next = new_n = n->next;

            free(n);
            n = new_n;
            f->size--;
        }
        else{
            prev = n;
            n = n->next;
        }
    }
}

void * forward_list_find(ForwardList *f, void *key, int (*cmp_fn)(void * cel1, void * cel2))
{
    NodeList *n = f->head;
    while (n != NULL)
    {
        if (!cmp_fn(n->data, key))
            return n->data;

        n = n->next;
    }
    return NULL;
}

void * forward_list_get(ForwardList* f, int i){
    if (i < 0 ||  i >= f->size)
        exit(printf("Error: forward_list_get(): index out of bounds."));

    NodeList *n = f->head;
    for (int j = 0; j < i; j++)
        n = n->next;

    return n->data;
}