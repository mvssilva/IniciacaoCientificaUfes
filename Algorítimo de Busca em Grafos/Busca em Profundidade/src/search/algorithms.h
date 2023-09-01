
#ifndef _ALGORITHMS_H_
#define _ALGORITHMS_H_

#include "grafo.h"

typedef struct
{
    int *caminho;
    int tamanho_caminho;
    int nos_expandidos;
    int sucesso;
} ResultData;

ResultData busca_largura_iterando(Grafo *g, int inicio, int fim);
ResultData busca_largura_recursiva(Grafo *g, int inicio, int fim);
ResultData busca_profundidade_iterando(Grafo *g, int inicio, int fim);
ResultData busca_profundidade_recursiva(Grafo *g, int inicio, int fim);
#endif