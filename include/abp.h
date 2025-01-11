#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct TNodoA{
   char palavra[50];
   char sinonimo[50];

   struct TNodoA *esq;
   struct TNodoA *dir;
} pNodoA;


pNodoA* Inserearvore(pNodoA *a, char *palavra, char *sinonimo);
char* BuscaArvore(pNodoA *a, char *palavra);
void PreFixado(pNodoA *a);
void imprimeArvore(pNodoA *a);
void imprimeABP(pNodoA *a, int altura);
int Altura (pNodoA *a);
int fatorDeBalanceamento (pNodoA *a);
int fatorDeBalanceamentoArvore (pNodoA *a, int maiorFator);
