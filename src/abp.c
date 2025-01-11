#include "../include/abp.h"

pNodoA *Inserearvore(pNodoA *a, char *palavra, char *sinonimo)
{
    if (a == NULL)
    {
        a = (pNodoA *)malloc(sizeof(pNodoA));
        strcpy(a->info, palavra);
        strcpy(a->sinonimo, sinonimo);
        a->esq = NULL;
        a->dir = NULL;
        a->nodos++;

    }
    else if (strcmp(palavra, a->info) < 0)
        a->esq = Inserearvore(a->esq, palavra, sinonimo);
    else
        a->dir = Inserearvore(a->dir, palavra, sinonimo);
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
    if (consulta(a, palavra) != NULL)
        return consulta(a, palavra)->sinonimo;
    else
        return NULL;
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
