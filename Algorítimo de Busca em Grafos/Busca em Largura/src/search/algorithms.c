
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

void _busca_largura_recursiva(Grafo *grafo, Queue *queue, ResultData *resposta, int fim)
{
    if (queue_empty(queue)) {
        return;
    }

    Vertices *atual = (Vertices *)queue_pop(queue);
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
            queue_push(queue, novo);
        }
        n = n->next;
    }

    _busca_largura_recursiva(grafo, queue, resposta, fim);
}

ResultData busca_largura_recursiva(Grafo *grafo, int inicio, int fim)
{
    ResultData resposta = _default_result();
    Vertices *atual = &(grafo->array[inicio - 1]);
    Queue *queue = queue_construct();
    queue_push(queue, atual);
    atual->flag = 1;

    _busca_largura_recursiva(grafo, queue, &resposta, fim);
    queue_destroy(queue);
    return resposta;

}

ResultData busca_largura_iterando(Grafo *grafo, int inicio, int fim)
{
    ResultData resposta = _default_result();
    Vertices * atual = &(grafo->array[inicio-1]);
    Queue * queue = queue_construct();
    queue_push(queue, atual);
    atual->flag = 1;

    while(!queue_empty(queue)){
        atual = (Vertices*)queue_pop(queue);
        resposta.nos_expandidos++;
        printf("[%d]\n", atual->nome);
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
                queue_push(queue, novo);
            }
            n = n->next;
        }
    }

    queue_destroy(queue);
    return resposta;
}
