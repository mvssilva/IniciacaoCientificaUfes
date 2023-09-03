#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct NodeList NodeList;

struct NodeList{
    NodeList * next;
    void * data;
};

struct List{
    List * head;
    List * last;
};