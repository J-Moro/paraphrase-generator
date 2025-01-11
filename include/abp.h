#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct TNodoA{
   char info[50];
   char sinonimo[50];

   struct TNodoA *esq;
   struct TNodoA *dir;

   int altura;
   int nodos;
} pNodoA;

int comp = 0;

pNodoA* Inserearvore(pNodoA *a, char *palavra, char *sinonimo);
pNodoA *consulta(pNodoA *a, char *chave);
char* BuscaArvore(pNodoA *a, char *palavra);
int Altura(pNodoA *a);
