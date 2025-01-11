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