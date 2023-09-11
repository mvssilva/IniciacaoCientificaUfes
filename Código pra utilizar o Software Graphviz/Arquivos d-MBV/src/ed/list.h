#ifndef FOWARD_LIST_H
#define FOWARD_LIST_H

typedef struct NodeList NodeList;
typedef struct ForwardList ForwardList;

ForwardList * forward_list_construct();
void forward_list_push_back(ForwardList*, void*);
void forward_list_destruct(ForwardList*);
void *forward_list_pop_front(ForwardList*);
int forward_return_size(ForwardList *);
void forward_list_remove(ForwardList *, void *);
void * forward_list_find(ForwardList *l, void *key, int (*cmp_fn)(void * cel1, void * cel2));
void * forward_list_get(ForwardList*, int);
int forward_size_over(ForwardList *);
#endif