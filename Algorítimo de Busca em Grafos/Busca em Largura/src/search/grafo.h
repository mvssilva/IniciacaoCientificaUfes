#ifndef GRAFO_H_H_
#define GRAFO_H_H_


typedef struct Adjacencia Adjacencia;
struct Adjacencia{
    int dest;    
    Adjacencia * next;
};

typedef struct Vertices Vertices;
struct Vertices{
    int flag;
    int nome;
    Adjacencia * head;
    Vertices * parent;
};

typedef struct Grafo Grafo;
struct Grafo{
    Vertices * array;
    int qtd_vertices;
    int qtd_arestas;
};

Grafo * grafo_construct(int, int);
Grafo *grafo_carregar(char *arquivo);
void grafo_destruir(Grafo *g);

#endif