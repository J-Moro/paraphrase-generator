#include "../include/splay.h"

pNodoA* rotacaoZig(pNodoA* raiz)
{
    if (raiz == NULL || raiz->esq == NULL) return raiz; // Check if raiz or its left child is NULL

    pNodoA* aux = raiz->esq;        // aux recebe o filho esquerdo da raiz
    raiz->esq = aux->dir;          // o filho direito de aux passa a ser o filho esquerdo da raiz
    if (aux->dir != NULL) aux->dir->pai = raiz; // Update parent pointer of aux->dir

    aux->dir = raiz;               // a raiz passa a ser o filho direito de aux
    aux->pai = raiz->pai;          // Update parent pointer of aux
    raiz->pai = aux;               // Update parent pointer of raiz

    // Ensure the parent of aux points to aux
    if (aux->pai != NULL) {
        if (aux->pai->esq == raiz) aux->pai->esq = aux;
        else aux->pai->dir = aux;
    }

    return aux; // Return new root of the subtree
}

pNodoA* rotacaoZag(pNodoA* raiz)
{
    if (raiz == NULL || raiz->dir == NULL) return raiz; // Check if raiz or its right child is NULL

    pNodoA* aux = raiz->dir;        // aux recebe o filho direito da raiz
    raiz->dir = aux->esq;          // o filho esquerdo de aux passa a ser o filho direito da raiz
    if (aux->esq != NULL) aux->esq->pai = raiz; // Update parent pointer of aux->esq

    aux->esq = raiz;               // a raiz passa a ser o filho esquerdo de aux
    aux->pai = raiz->pai;          // Update parent pointer of aux
    raiz->pai = aux;               // Update parent pointer of raiz

    // Ensure the parent of aux points to aux
    if (aux->pai != NULL) {
        if (aux->pai->esq == raiz) aux->pai->esq = aux;
        else aux->pai->dir = aux;
    }

    return aux; // Return new root of the subtree
}


pNodoA* rotacaoZagZig(pNodoA* raiz)
{
    if (raiz == NULL || raiz->esq == NULL) return raiz;  // Check if raiz or its left child is NULL
    raiz->esq = rotacaoZag(raiz->esq);  // rotaciona o filho esquerdo da raiz para a esquerda
    return rotacaoZig(raiz);            // rotaciona a raiz para a direita
}

pNodoA* rotacaoZigZag(pNodoA* raiz)
{
    if (raiz == NULL || raiz->dir == NULL) return raiz;  // Check if raiz or its right child is NULL
    raiz->dir = rotacaoZig(raiz->dir);  // rotaciona o filho direito da raiz para a direita
    return rotacaoZag(raiz);            // rotaciona a raiz para a esquerda
}

pNodoA* rotacaoZigZig(pNodoA* raiz)
{
    if (raiz == NULL || raiz->esq == NULL) return raiz;  // Check if raiz or its left child is NULL
    raiz = rotacaoZig(raiz);    // rotaciona a raiz para a direita duas vezes
    return rotacaoZig(raiz);
}

pNodoA* rotacaoZagZag(pNodoA* raiz)
{
    if (raiz == NULL || raiz->dir == NULL) return raiz;  // Check if raiz or its right child is NULL
    raiz = rotacaoZag(raiz);    // rotaciona a raiz para a direita duas vezes
    return rotacaoZag(raiz);
}

pNodoA* splay(pNodoA* nodo)    //funcao temporariamente vazia
{
    if(nodo == NULL)    // se a arvore estiver vazia
        return nodo;    // retorna a arvore vazia

    else if(nodo->pai != NULL)      //se o nodo tiver pai
    {
        if(nodo->pai->pai != NULL)  //se o nodo tiver avô
        {
            if(nodo->pai->pai->esq == nodo->pai) //se o pai for o filho esquerdo do avô
            {
                if(nodo->pai->esq == nodo) //se o nodo for o filho esquerdo
                {
                    nodo = rotacaoZigZig(nodo->pai->pai);  //rotaciona para a direita
                    rotacoes++;
                }
                else
                {
                    nodo = rotacaoZagZig(nodo->pai->pai);  //rotaciona para a esquerda
                    rotacoes++;
                }
            }
            else
            {
                if(nodo->pai->dir == nodo) //se o nodo for o filho direito
                {
                    nodo = rotacaoZagZag(nodo->pai->pai);  //rotaciona para a esquerda
                    rotacoes++;
                }
                else
                {
                    nodo = rotacaoZigZag(nodo->pai->pai);  //rotaciona para a direita
                    rotacoes++;
                }
            }
        }
        else
        {
            if(nodo->pai->esq == nodo) //se o nodo for o filho esquerdo
            {
                nodo = rotacaoZig(nodo->pai);  //rotaciona o pai para a direita
                rotacoes++;
            }
            else
            {
                nodo = rotacaoZag(nodo->pai);  //rotaciona o pai para a esquerda
                rotacoes++;
            }
        }

    }

    if(nodo->pai != NULL)   //se o nodo tiver pai (nao for a raiz)
    {
        return splay(nodo);  //chama a funcao splay recursivamente
    }
    else
    {
        return nodo;    //retorna o nodo
    }
}

pNodoA *consultaSplay(pNodoA *a, char *chave, pNodoA **lastVisited) {
    while (a != NULL) {
        *lastVisited = a;  // Track the last visited node

        if (!strcmp(a->info, chave)) {
            return a;  // Key found
        } else {
            if (strcmp(a->info, chave) > 0)
                a = a->esq;  // Move left
            else
                a = a->dir;  // Move right
        }
    }
    return NULL;  // Key not found
}

pNodoA *consultaIncComp(pNodoA *a, char *chave, pNodoA **lastVisited) {
    while (a != NULL) {
        *lastVisited = a;  // Track the last visited node

        comp++;
        if (!strcmp(a->info, chave)) {
            comp++;
            return a;  // Key found
        } else {
            comp++;
            if (strcmp(a->info, chave) > 0)
                a = a->esq;  // Move left
            else
                a = a->dir;  // Move right
        }
    }
    return NULL;  // Key not found
}

char* buscaSinonimo(pNodoA** raiz, char* chave) {
    // Use the access function to search for the word
    pNodoA* resultado = accessIncComp(*raiz, chave);
    *raiz = resultado;

    // If the word was found, return its synonym
    if (resultado != NULL && strcmp(resultado->info, chave) == 0) {
        return resultado->sinonimo;
    }

    // If the word was not found, return NULL
    return NULL;
}

pNodoA* access(pNodoA* raiz, char* chave) {
    pNodoA* lastVisited = NULL;
    pNodoA* found = consultaSplay(raiz, chave, &lastVisited);  // Search the tree

    if (found != NULL) {
        // Key found, splay the found node
        return splay(found);
    } else if (lastVisited != NULL) {
        // Key not found, splay the last visited node
        return splay(lastVisited);
    }

    return raiz;  // Tree was empty
}

pNodoA* accessIncComp(pNodoA* raiz, char* chave) {
    pNodoA* lastVisited = NULL;
    pNodoA* found = consultaIncComp(raiz, chave, &lastVisited);  // Search the tree

    if (found != NULL) {
        // Key found, splay the found node
        return splay(found);
    } else if (lastVisited != NULL) {
        // Key not found, splay the last visited node
        return splay(lastVisited);
    }

    return raiz;  // Tree was empty
}

void split(pNodoA* root, char* chave, pNodoA** root1, pNodoA** root2) {
    if (root == NULL) {
        *root1 = NULL;
        *root2 = NULL;
        return;
    }

    // Splay the node with the given key (or the last visited node)
    root = access(root, chave);

    // Split the tree based on the root's key
    if (strcmp(root->info, chave) < 0) {
        // All nodes >= chave go to root2
        *root1 = root;
        *root2 = root->dir;
        if (*root2 != NULL) {
            (*root2)->pai = NULL;  // Disconnect root2 from root1
        }
        (*root1)->dir = NULL;  // Disconnect root1 from root2
    } else {
        // All nodes < chave go to root1
        *root2 = root;
        *root1 = root->esq;
        if (*root1 != NULL) {
            (*root1)->pai = NULL;  // Disconnect root1 from root2
        }
        (*root2)->esq = NULL;  // Disconnect root2 from root1
    }
}

pNodoA *insereSplay(pNodoA *a, char *palavra, char *sinonimo)
{
    pNodoA *subArvoreEsq = NULL;
    pNodoA *subArvoreDir = NULL;

    split(a, palavra, &subArvoreEsq, &subArvoreDir);

    pNodoA *novoNodo = (pNodoA *)malloc(sizeof(pNodoA));
    strcpy(novoNodo->info, palavra);
    strcpy(novoNodo->sinonimo, sinonimo);
    novoNodo->pai = NULL;
    novoNodo->esq = subArvoreEsq;
    novoNodo->dir = subArvoreDir;

    if (subArvoreEsq != NULL) subArvoreEsq->pai = novoNodo;
    if (subArvoreDir != NULL) subArvoreDir->pai = novoNodo;

    return novoNodo;

}
