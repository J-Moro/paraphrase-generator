#include "../include/abp.h"

pNodoA *Inserearvore(pNodoA *a, char *palavra, char *sinonimo)
{
    if (a == NULL)
    {
        a = (pNodoA *)malloc(sizeof(pNodoA));
        strcpy(a->info, palavra);
        strcpy(a->sinonimo, sinonimo);
        a->pai = NULL;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (strcmp(palavra, a->info) < 0)
    {
        a->esq = Inserearvore(a->esq, palavra, sinonimo);
        a->esq->pai = a;
    }
    else
    {
        a->dir = Inserearvore(a->dir, palavra, sinonimo);
        a->dir->pai = a;
    }

    return a;
}

pNodoA *consulta(pNodoA *a, char *chave)
{
    while (a != NULL)
    {
        comp++;
        if (!strcmp(a->info, chave))
        {
            comp++;
            return a;
        }
        else
        {
            comp++;
            if (strcmp(a->info, chave) > 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }
    return NULL;
}

char *BuscaArvore(pNodoA *a, char *palavra)
{
    pNodoA *palavraAchada = consulta(a, palavra);
    if (palavraAchada != NULL)
        return palavraAchada->sinonimo;
    else
        return NULL;
}

int Nodos(pNodoA *a)
{
    if (a == NULL)
        return 0;
    else
        return (1 + Nodos(a->esq) + Nodos(a->dir));
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
