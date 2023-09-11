#include <stdio.h>
#include <stdlib.h>
#include "src/graphs/graph.h"

int main(){
    char diretorio[100];
    scanf("%s", diretorio);
    Graph *graph = graph_carregar(diretorio);
    graph_printf_graphviz(graph);
    graph_destruct(graph);
    return 0;
}