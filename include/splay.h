#include "abp.h"

int rotacoes = 0;

pNodoA* rotacaoZig(pNodoA* raiz);
pNodoA* rotacaoZag(pNodoA* raiz);
pNodoA* rotacaoZagZig(pNodoA* raiz);
pNodoA* rotacaoZigZag(pNodoA* raiz);
pNodoA* rotacaoZigZig(pNodoA* raiz);
pNodoA* rotacaoZagZag(pNodoA* raiz);
pNodoA* splay(pNodoA* nodo, char* chave);
pNodoA* consultaSplay(pNodoA* a, char* chave, pNodoA** lastVisited);
pNodoA* access(pNodoA* raiz, char* chave);
pNodoA* join(pNodoA* raiz1, pNodoA* raiz2);
void split(pNodoA* root, char* chave, pNodoA** root1, pNodoA** root2);
pNodoA* insereSplay(pNodoA* a, char* palavra, char* sinonimo);
pNodoA* deleteSplay(pNodoA* raiz, char* chave);