#include "../include/splay.h"

pNodoA* rotacaoZig(pNodoA* raiz)
{
    pNodoA* aux = raiz->esq;    // aux recebe o filho esquerdo da raiz
    raiz->esq = aux->dir;       // o filho direito de aux passa a ser o filho esquerdo da raiz
    aux->dir = raiz;            // a raiz passa a ser o filho direito de aux
    return aux;
}

pNodoA* rotacaoZag(pNodoA* raiz)
{
    pNodoA* aux = raiz->dir;    // aux recebe o filho direito da raiz
    raiz->dir = aux->esq;       // o filho esquerdo de aux passa a ser o filho direito da raiz
    aux->esq = raiz;            // a raiz passa a ser o filho esquerdo de aux
    return aux;
}

pNodoA* rotacaoZagZig(pNodoA* raiz)
{
    raiz->esq = rotacaoZag(raiz->esq);  // rotaciona o filho esquerdo da raiz para a esquerda
    return rotacaoZig(raiz);            // rotaciona a raiz para a direita
}

pNodoA* rotacaoZigZag(pNodoA* raiz)
{
    raiz->dir = rotacaoZig(raiz->dir);  // rotaciona o filho direito da raiz para a direita
    return rotacaoZag(raiz);            // rotaciona a raiz para a esquerda
}

pNodoA* rotacaoZigZig(pNodoA* raiz)
{
    raiz = rotacaoZig(raiz);    // rotaciona a raiz para a direita duas vezes
    return rotacaoZig(raiz);    
}

pNodoA* rotacaoZagZag(pNodoA* raiz)
{
    raiz = rotacaoZag(raiz);    // rotaciona a raiz para a direita duas vezes
    return rotacaoZag(raiz);    
}

pNodoA* splay(pNodoA* nodo, char* chave)    //funcao temporariamente vazia
{
    if(nodo == NULL)    // se a arvore estiver vazia
        return nodo;    // retorna a arvore vazia

    else if(nodo->pai != NULL)      //se o nodo tiver pai
    {
        if(nodo->pai->pai =! NULL)  //se o nodo tiver avô
        {
            if(nodo->pai->pai->esq == nodo->pai) //se o pai for o filho esquerdo do avô
            {
                if(nodo->pai->esq == nodo) //se o nodo for o filho esquerdo
                {
                    rotacaoZigZig(nodo->pai->pai);  //rotaciona para a direita
                }
                else
                {
                    rotacaoZagZig(nodo->pai->pai);  //rotaciona para a esquerda
                }
            }
            else
            {
                if(nodo->pai->dir == nodo) //se o nodo for o filho direito
                {
                    rotacaoZagZag(nodo->pai->pai);  //rotaciona para a esquerda
                }
                else
                {
                    rotacaoZigZag(nodo->pai->pai);  //rotaciona para a direita
                }
            }
        }
        else
        {
            if(nodo->pai->esq == nodo) //se o nodo for o filho esquerdo
            {
                rotacaoZig(nodo->pai);  //rotaciona o pai para a direita
            }
            else
            {
                rotacaoZag(nodo->pai);  //rotaciona o pai para a esquerda
            }
        }

    }
    
    if(nodo->pai != NULL)   //se o nodo tiver pai (nao for a raiz)
    {
        return splay(nodo, chave);  //chama a funcao splay recursivamente
    }
    else
    {
        return nodo;    //retorna o nodo
    }
}

pNodoA* access(pNodoA* raiz, char* chave)    
{
    raiz = consulta(raiz, chave);   // busca a chave na arvore
        
    return raiz;
}