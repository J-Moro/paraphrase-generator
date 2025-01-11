#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TNodoA{
   int info;
   struct TNodoA *esq;
   struct TNodoA *dir;
} pNodoA;


pNodoA* Inserearvore(pNodoA *a, int ch);
void PreFixado(pNodoA *a);
void imprimeArvore(pNodoA *a);
void imprimeABP(pNodoA *a, int altura);
int Altura (pNodoA *a);
int fatorDeBalanceamento (pNodoA *a);
int fatorDeBalanceamentoArvore (pNodoA *a, int maiorFator);
