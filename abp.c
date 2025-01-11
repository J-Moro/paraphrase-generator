#include "abp.h"

pNodoA* Inserearvore(pNodoA *a, int ch)
{
    if (a == NULL)
    {
        a = (pNodoA*) malloc(sizeof(pNodoA));
        a->info = ch;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (ch < a->info)
        a->esq = Inserearvore(a->esq,ch);
    else
        a->dir = Inserearvore(a->dir,ch);
    return a;
}

void PreFixado(pNodoA *a)
{
    if (a!= NULL)
    {
        printf("%d\n",a->info);
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

    if (a!= NULL)
    {

        for (int i = 0; i < altura; i++)
            printf("=");

        printf("%d\n",a->info);
        imprimeABP(a->esq, altura + 1);
        imprimeABP(a->dir, altura + 1);
    }
    else return;
}

int Altura (pNodoA *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = Altura (a->esq);
        Alt_Dir = Altura (a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

int fatorDeBalanceamento (pNodoA *a)
{
    return fatorDeBalanceamentoArvore (a, 0);
}

int fatorDeBalanceamentoArvore (pNodoA *a, int maiorFator)
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

    if (fatorA >maiorFator)
        maiorFator = fatorA;

    return maiorFator;
}
