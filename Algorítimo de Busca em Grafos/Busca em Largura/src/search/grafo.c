#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Função para criar um grafo com vértices e arestas
Grafo * grafo_construct(int vertices, int arestas){
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    g->qtd_vertices = vertices;
    g->qtd_arestas = arestas;
    g->array = (Vertices *) malloc(sizeof(Vertices) * vertices);
    for(int i = 0; i < vertices; i++){
        g->array[i].head = NULL;
        g->array[i].parent = NULL;
    }
    return g;
}

// Função para adicionar uma aresta ao grafo
void _add_conexao_grafo_orientado(Grafo *g, int src, int dest){
    Adjacencia *vert= (Adjacencia *) malloc(sizeof(Adjacencia));
    vert->dest = dest;
    vert->next = NULL; 

    Adjacencia * node = g->array[src - 1].head;
    Adjacencia * prev = NULL;

    while(node != NULL){
        prev = node;
        node = node->next;
    }

    if(prev == NULL)
        g->array[src - 1].head = vert;
    else
        prev->next = vert;
    
    g->array[src - 1].nome = src;
    g->array[src - 1].flag = 0;

    if(g->array[dest - 1].head == NULL){
        g->array[dest - 1].flag = 0;
        g->array[dest - 1].nome = dest;
    }
}

void _add_conexao_grafo_nao_orientado(Grafo *g, int src, int dest){
    _add_conexao_grafo_orientado(g, src, dest);
    _add_conexao_grafo_orientado(g, dest, src);
}

//Leitura e conversão do arquivo para struct Grafo
Grafo *grafo_carregar(char *arquivo){

    FILE *file = fopen(arquivo, "rb");

    if (file == NULL)
        exit(printf("Arquivo %s nao encontrado.\n", arquivo));

    int qtd_vertices, qtd_arestas;
    fscanf(file, "%d", &qtd_vertices);
    fscanf(file, "%d", &qtd_arestas);

    Grafo *g = grafo_construct(qtd_vertices, qtd_arestas);
    for (int i = 0; i < qtd_arestas; i++)
    {   
        int src, dest;
        fscanf(file, "%d", &src);
        fscanf(file, "%d", &dest);
        //_add_conexao_grafo_orientado(g, src, dest);
        _add_conexao_grafo_nao_orientado(g, src, dest);
    }

    fclose(file);
    return g;
}

void grafo_destruir(Grafo *g){
    for(int i = 0; i < g->qtd_vertices; i++){
        Adjacencia * node = g->array[i].head;
        while(node != NULL){
            Adjacencia * aux = node->next;
            free(node);
            node = aux;
        }
    }
    free(g->array);
    free(g);
}