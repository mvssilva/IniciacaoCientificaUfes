#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "../ed/list.h"
#include "../ed/vector.h"


typedef struct Vertices Vertices;

struct Vertices{
    int src;
    int x;
    int y;
    int demand;
    ForwardList *adj;
};

struct Graph{
    char * name;
    char * type;
    char * edge_type;
    int size;           //esse é o valor total de coordernadas?
    int capacity;       //essa seria a capacidade do caminhão?
    Vector * coord;
};

Graph * graph_construct(){
    Graph * g = (Graph*)malloc(sizeof(Graph));
    g->name = NULL;
    g->coord = NULL;
    g->type = NULL;
    g->edge_type = NULL;
    g->capacity = 0;
    g->size = 0;
    return g;
}

Vertices * _vertices_construct(int src, int x, int y){
    Vertices * v = (Vertices*)malloc(sizeof(Vertices));
    v->src = src;
    v->x = x;
    v->y = y;
    v->demand = -1;
    v->adj = forward_list_construct();
    return v;
}

void _save_coordinates(FILE * file, Graph *g){
    int qtd = g->size;
    int src, x, y;

    g->coord = vector_construct();

    for(int i = 0; i < qtd; i++){
        fscanf(file, "%d %d %d\n", &src, &x, &y); 
        vector_push_back(g->coord, _vertices_construct(src, x, y));
    }
}

void _save_demand(FILE * file, Graph *g){
    int qtd = g->size;
    int src, demand;

    for(int i = 0; i < qtd; i++){
        fscanf(file, "%d %d\n", &src, &demand); 
        Vertices * v = (Vertices*)vector_get(g->coord, i);
        v->demand = demand;
    }
}

void _save_depot(FILE * file, Graph *g){
    char valor1[100], valor2[100];
    fscanf(file, "%[^\n]", valor1);
    fscanf(file, "%[^\n]", valor2); 
}

Graph * graph_upload_file_CVRPLIB(char * name_file){
    Graph * graph = graph_construct();
    
    FILE *file = fopen(name_file, "r");
    if (file == NULL)
        exit(printf("Arquivo %s nao encontrado.\n", name_file));
    
    char comentario[100];
    char lixo;
    fscanf(file, "%[^:]%c", comentario, &lixo); // consumindo trecho "NAME : "
    fscanf(file, "%c", &lixo);
    char name[100];
    fscanf(file, "%s\n", name); // salvando nome do arquivo
    int qtd = 1 + strlen(name);
    graph->name = (char*)malloc(qtd * sizeof(char));
    strcpy(graph->name, name);

    fscanf(file, "%[^\n]", comentario); // consumindo trecho "COMENT : ..."
    fscanf(file, "%[^:]%c", comentario, &lixo); // consumindo trecho "TYPE : "
    fscanf(file, "%c", &lixo);

    char type[100];
    fscanf(file, "%s\n", type); // salvando tipo do arquivo
    qtd = 1 + strlen(type);
    graph->type = (char*)malloc(qtd * sizeof(char));
    strcpy(graph->type, type);
    
    fscanf(file, "%[^:]%c", comentario, &lixo); // consumindo trecho "DIMENSION : "
    fscanf(file, "%c", &lixo);

    fscanf(file, "%d\n", &graph->size);

    fscanf(file, "%[^:]%c", comentario, &lixo); // consumindo trecho "EDGE_WEIGHT_TYPE : "
    fscanf(file, "%c", &lixo);
    
    char edge_type[100];
    fscanf(file, "%s\n", edge_type); // salvando tipo de 'borda?' do arquivo
    qtd = 1 + strlen(edge_type);
    graph->edge_type = (char*)malloc(qtd * sizeof(char));
    strcpy(graph->edge_type, edge_type);

    fscanf(file, "%[^:]%c", comentario, &lixo); // consumindo trecho "CAPACITY : "
    fscanf(file, "%c", &lixo);

    fscanf(file, "%d\n", &graph->capacity);
    fscanf(file, "%[^\n]", comentario); // consumindo trecho "NODE_COORD_SECTION"

    _save_coordinates(file, graph);
    fscanf(file, "%[^\n]", comentario); // consumindo trecho "DEMAND_SECTION"
    _save_demand(file, graph);
    fscanf(file, "%[^\n]", comentario); // consumindo trecho "DEPOT_SECTION"
    _save_depot(file, graph);
    fscanf(file, "%[^\n]", comentario); // consumindo trecho "EOF"

    fclose(file);
    return graph;
}

void graph_printfull(Graph * g){
    printf("NAME : %s\n", g->name);
    printf("TYPE : %s\n", g->type);
    printf("DIMENSION : %d\n", g->size);
    printf("EDGE_WEIGHT_TYPE : %s\n", g->edge_type); 
    printf("CAPACITY : %d\n", g->capacity);
    printf("NODE_COORD_SECTION\n");

    for(int i = 0; i < g->size; i++){
        Vertices * v = vector_get(g->coord, i);
        printf("SRC = %02d | X = %02d | Y = %02d | Demand = %02d\n", v->src, v->x, v->y, v->demand);
    } 
}

void graph_printf_graphviz(Graph * g){
    for(int i = 0; i < g->size; i++){
        Vertices * v = vector_get(g->coord, i);
        printf("%d %d %d %d\n", v->src, v->x, v->y, v->demand);
    } 
}

void _vertices_destruct(Vertices * v){
    forward_list_destruct(v->adj);
    free(v);
}

void graph_destruct(Graph *g){
    while(vector_size(g->coord) > 0){
        Vertices * v = vector_pop_front(g->coord);
        _vertices_destruct(v);
    }
    vector_destroy(g->coord);
    free(g->name);
    free(g->edge_type);
    free(g->type);
    free(g);
}