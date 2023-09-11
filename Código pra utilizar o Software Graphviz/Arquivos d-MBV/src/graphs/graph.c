#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Função para criar um graph com vértices e arestas
Graph * graph_construct(int vertices, int arestas){
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->qtd_vertices = vertices;
    g->qtd_arestas = arestas;
    g->matriz = (Vertices *) malloc(sizeof(Vertices) * vertices);
    for(int i = 0; i < vertices; i++){
        g->matriz[i].head = NULL;
    }
    return g;
}

// Função para adicionar uma aresta ao graph
void _add_conexao_graph_orientado(Graph *g, int src, int dest, int demand){
    Adjacencia *vert= (Adjacencia *) malloc(sizeof(Adjacencia));
    vert->dest = dest;
    vert->next = NULL; 

    Adjacencia * node = g->matriz[src - 1].head;
    Adjacencia * prev = NULL;

    while(node != NULL){
        prev = node;
        node = node->next;
    }

    if(prev == NULL)
        g->matriz[src - 1].head = vert;
    else
        prev->next = vert;
    
    g->matriz[src - 1].nome = src;
    g->matriz[src - 1].demand = demand;

    if(g->matriz[dest - 1].head == NULL){
        g->matriz[dest - 1].demand = demand;
        g->matriz[dest - 1].nome = dest;
    }
}

void _add_conexao_graph_nao_orientado(Graph *g, int src, int dest, int demand){
    _add_conexao_graph_orientado(g, src, dest, demand);
    _add_conexao_graph_orientado(g, dest, src, demand);
}

//Leitura e conversão do arquivo para struct Graph
Graph *graph_carregar(char *arquivo){

    FILE *file = fopen(arquivo, "rb");

    if (file == NULL)
        exit(printf("Arquivo %s nao encontrado.\n", arquivo));

    int qtd_vertices, qtd_arestas, qtd_demand;
    fscanf(file, "%d", &qtd_vertices);
    fscanf(file, "%d", &qtd_arestas);
    fscanf(file, "%d", &qtd_demand);


    Graph *g = graph_construct(qtd_vertices, qtd_arestas);
    for (int i = 0; i < qtd_arestas; i++)
    {   
        int src, dest, demand;
        fscanf(file, "%d", &src);
        fscanf(file, "%d", &dest);
        fscanf(file, "%d", &demand);
        //_add_conexao_graph_orientado(g, src, dest, demand);
        _add_conexao_graph_nao_orientado(g, src, dest, demand);
    }

    fclose(file);
    return g;
}

void graph_destruct(Graph *g){
    for(int i = 0; i < g->qtd_vertices; i++){
        Adjacencia * node = g->matriz[i].head;
        while(node != NULL){
            Adjacencia * aux = node->next;
            free(node);
            node = aux;
        }
    }
    free(g->matriz);
    free(g);
}

void graph_printf_graphviz(Graph * g){
    FILE *arquivoDOT = fopen("grafos/grafofinal.dot", "w");
    
    if (arquivoDOT == NULL) {
        exit(printf("Erro ao abrir arquivos.\n"));
    }

    fprintf(arquivoDOT, "digraph G {\n");

    for(int i = 0; i < g->qtd_vertices; i++){
        Vertices v = g->matriz[i];
        
            Adjacencia * node = v.head;
            while(node != NULL){
                fprintf(arquivoDOT, "\t%d -> %d\n", v.nome, node->dest);
                node = node->next;
            }
    } 
    fprintf(arquivoDOT, "}\n");
    fclose(arquivoDOT);

    system("dot -Kneato -Tpng -o imagens/grafofinal.png grafos/grafofinal.dot");
}