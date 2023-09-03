#ifndef GRAPH_H_H
#define GRAPH_H_H

#include "../ed/list.h"

typedef struct Graph Graph;

Graph * graph_upload_file_CVRPLIB(char *);
Graph * graph_construct();
void graph_printfull(Graph *);
void graph_destruct(Graph *);


#endif