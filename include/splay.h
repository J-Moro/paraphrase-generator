#ifndef SPLAY_H
#define SPLAY_H

#include "abp.h"

int rotacoes = 0;

pNodoA* rotacaoZig(pNodoA* raiz);
pNodoA* rotacaoZag(pNodoA* raiz);
pNodoA* rotacaoZagZig(pNodoA* raiz);
pNodoA* rotacaoZigZag(pNodoA* raiz);
pNodoA* rotacaoZigZig(pNodoA* raiz);
pNodoA* rotacaoZagZag(pNodoA* raiz);
pNodoA* splay(pNodoA* nodo);
pNodoA* consultaSplay(pNodoA* a, char* chave, pNodoA** lastVisited);
char* buscaSinonimo(pNodoA** raiz, char* chave);
pNodoA* access(pNodoA* raiz, char* chave);
void split(pNodoA* root, char* chave, pNodoA** root1, pNodoA** root2);
pNodoA* insereSplay(pNodoA* a, char* palavra, char* sinonimo);

#endif // SPLAY_H
