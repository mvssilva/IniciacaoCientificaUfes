
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"
#include "../ed/queue.h"
#include "../ed/stack.h"

ResultData caminho(Vertices * atual, ResultData resposta)
{
    resposta.sucesso = 1;
    Stack * caminho = stack_construct();
    while (atual != NULL){
        stack_push(caminho, atual);
        resposta.tamanho_caminho++;
        atual = atual->parent;
    }

    int qtd = stack_size(caminho);
    resposta.tamanho_caminho = qtd;
    resposta.caminho = (int*)malloc(qtd * sizeof(int));
    for(int i = 0; i < resposta.tamanho_caminho; i++){
        Vertices * aux = stack_pop(caminho);
        resposta.caminho[i] = aux->nome;
    }

    stack_destroy(caminho);
    return resposta;
}

ResultData _default_result()
{
    ResultData result;

    result.caminho = NULL;
    result.nos_expandidos = 0;
    result.tamanho_caminho = 0;
    result.sucesso = 0;

    return result;
}

void _busca_profundidade_recursiva(Grafo *grafo, Stack *stack, ResultData *resposta, int fim)
{
    if (stack_empty(stack)) {
        return;
    }

    Vertices *atual = (Vertices *)stack_pop(stack);
    resposta->nos_expandidos++;

    if (atual->nome == fim) {
        *resposta = caminho(atual, *resposta);
        return;
    }

    Adjacencia *n = atual->head;
    while (n != NULL) {
        Vertices *novo = &(grafo->array[n->dest - 1]);

        if (novo->flag == 0) {
            novo->flag = 1;
            novo->parent = atual;
            stack_push(stack, novo);
        }
        n = n->next;
    }

    _busca_profundidade_recursiva(grafo, stack, resposta, fim);
}

ResultData busca_profundidade_recursiva(Grafo *grafo, int inicio, int fim)
{
    ResultData resposta = _default_result();
    Vertices *atual = &(grafo->array[inicio - 1]);
    Stack *stack = stack_construct();
    stack_push(stack, atual);
    atual->flag = 1;

    _busca_profundidade_recursiva(grafo, stack, &resposta, fim);
    stack_destroy(stack);
    return resposta;

}

ResultData busca_profundidade_iterando(Grafo *grafo, int inicio, int fim)
{   
    ResultData resposta = _default_result();
    Vertices * atual = &(grafo->array[inicio-1]);

    Stack * stack = stack_construct();
    stack_push(stack, atual);
    atual->flag = 1;

    while(!stack_empty(stack))
    {
        atual = (Vertices*)stack_pop(stack);
        printf("[%d]\n", atual->nome);
        resposta.nos_expandidos++;
        if(atual->nome == fim)
        {
            resposta = caminho(atual, resposta);
            break;
        }
        Adjacencia * n = atual->head;
        while(n != NULL)
        {
            Vertices *novo = &(grafo->array[n->dest - 1]);

            if(novo->flag == 0)
            {
                novo->flag = 1;
                novo->parent = atual;
                stack_push(stack, novo);
            }
            n = n->next;
        }
    
    }

    stack_destroy(stack);
    return resposta;
}

