
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/search/grafo.h"
#include "src/search/algorithms.h"
void print_result(ResultData *result)
{
    if (!result->sucesso)
    {
        printf("IMPOSSIVEL\n");
        return;
    }

    printf("Caminho percorrido = [");
    for (int i = 0; i < result->tamanho_caminho; i++){
        printf("%d", result->caminho[i]);

        if(i + 1 != result->tamanho_caminho)
            printf(", ");
    }
    printf("]\n");
    printf("Tamanho Caminho = %d\n", result->tamanho_caminho);
    printf("Vertices analizados = %d\n", result->nos_expandidos);
}

int main()
{
    char arquivo_grafo[100];
    int inicio, fim;
    ResultData result;
    Grafo *g;

    scanf("%s", arquivo_grafo);
    scanf("%d", &inicio);
    scanf("%d", &fim);

    g = grafo_carregar(arquivo_grafo);
    result = busca_profundidade_iterando(g, inicio, fim);
    //result = busca_profundidade_recursiva(g, inicio, fim);
    
    print_result(&result);

    grafo_destruir(g);
    if (result.caminho != NULL)
        free(result.caminho);

    return 0;
}