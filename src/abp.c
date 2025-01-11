#include "abp.h"

pNodoA* Inserearvore(pNodoA *a, char *palavra, char *sinonimo)
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->palavra, palavra);
        strcpy(a->sinonimo, sinonimo);
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (strcmp(palavra, a->palavra) < 0)
        a->esq = Inserearvore(a->esq, palavra, sinonimo);
    else
        a->dir = Inserearvore(a->dir, palavra, sinonimo);
    return a;
}

char* BuscaArvore(pNodoA *a, char *palavra)
{
    if (a == NULL)
        return NULL;
    else if (strcmp(palavra, a->palavra) == 0)
        return a->sinonimo;
    else if (strcmp(palavra, a->palavra) < 0)
        return BuscaArvore(a->esq, palavra);
    else
        return BuscaArvore(a->dir, palavra);
}

void PreFixado(pNodoA *a)
{
    if (a != NULL)
    {
        printf("%s\n", a->palavra);
        PreFixado(a->esq);
        PreFixado(a->dir);
    }
}

void imprimeArvore(pNodoA *a)
{
    return imprimeABP(a, 1);
}

void imprimeABP(pNodoA *a, int altura)
{
    if (a != NULL)
    {
        for (int i = 0; i < altura; i++)
            printf("=");

        printf("%s\n", a->palavra);
        imprimeABP(a->esq, altura + 1);
        imprimeABP(a->dir, altura + 1);
    }
    else return;
}

int Altura(pNodoA *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura(a->esq);
        Alt_Dir = Altura(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int fatorDeBalanceamento(pNodoA *a)
{
    return fatorDeBalanceamentoArvore(a, 0);
}

int fatorDeBalanceamentoArvore(pNodoA *a, int maiorFator)
{
    int fatorA, fatorEsq, fatorDir;

    if (a == NULL)
        return 0;

    fatorA = abs(Altura(a->esq) - Altura(a->dir));

    fatorEsq = fatorDeBalanceamentoArvore(a->esq, maiorFator);
    fatorDir = fatorDeBalanceamentoArvore(a->dir, maiorFator);

    if (fatorEsq > fatorDir)
        maiorFator = fatorEsq;
    else maiorFator = fatorDir;

    if (fatorA > maiorFator)
        maiorFator = fatorA;

    return maiorFator;
}

