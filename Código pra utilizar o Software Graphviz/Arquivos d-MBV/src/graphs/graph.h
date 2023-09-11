#ifndef GRAPH_H_H_
#define GRAPH_H_H_


typedef struct Adjacencia Adjacencia;
struct Adjacencia{
    int dest;    
    Adjacencia * next;
};

typedef struct Vertices Vertices;
struct Vertices{
    int nome;
    int demand;
    Adjacencia * head;
};

typedef struct Graph Graph;
struct Graph{
    Vertices * matriz;
    int qtd_vertices;
    int qtd_arestas;
};

Graph * graph_construct(int, int);
Graph *graph_carregar(char *);
void graph_destruct(Graph *);
void graph_printf_graphviz(Graph *);

#endif