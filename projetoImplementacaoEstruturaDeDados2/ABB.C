#include <stdio.h>
#include <stdlib.h>

typedef struct No 
{
    int chave;
    struct No* pai;
    struct No* direita;
    struct No* esquerda;
} 
Nodo;

Nodo* criarNodo(int chave) 
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->chave = chave;
    nodo->pai = NULL;
    nodo->direita = NULL;
    nodo->esquerda = NULL;
    return nodo;
}

void emOrdem(Nodo* raiz) 
{
    if (raiz != NULL) 
	{
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

Nodo* inserir_arvore(Nodo* raiz, int chave) 
{
    if (raiz == NULL)
        return criarNodo(chave);
    if (chave < raiz->chave) 
	{
        raiz->esquerda = inserir_arvore(raiz->esquerda, chave);
        raiz->esquerda->pai = raiz;
    } 
	else if (chave > raiz->chave) 
	{
        raiz->direita = inserir_arvore(raiz->direita, chave);
        raiz->direita->pai = raiz;
    }
    return raiz;
}

Nodo* buscaNodo(Nodo* raiz, int chave)
{
    if (raiz == NULL)
        return NULL;
    if (chave == raiz->chave)
        return raiz;
    if (chave < raiz->chave)
        return buscaNodo(raiz->esquerda, chave);
    else
        return buscaNodo(raiz->direita, chave);
}

Nodo** menorNo(Nodo** no) 
{
    if (!*no)
        return NULL;
    if (!(*no)->esquerda)
        return no;
    return menorNo(&(*no)->esquerda);
}

void removeNo(Nodo** no, int chave) 
{
    if (!*no)
        return;
    if (chave < (*no)->chave) 
	{
        removeNo(&(*no)->esquerda, chave);
        if (*no && (*no)->esquerda)
            (*no)->esquerda->pai = *no;
    } 
	else if (chave > (*no)->chave) 
	{
        removeNo(&(*no)->direita, chave);
        if (*no && (*no)->direita)
            (*no)->direita->pai = *no;
    } 
	else 
	{
        if (!(*no)->esquerda && !(*no)->direita) 
		{
            if ((*no)->pai) 
			{
                if ((*no)->pai->esquerda != NULL) 
				{
                    if ((*no)->pai->esquerda->chave == chave)
                        (*no)->pai->esquerda = NULL;
                    else
                        (*no)->pai->direita = NULL;
                } 
				else 
				{
                    (*no)->pai->direita = NULL;
                }
            }
            free(*no);
            *no = NULL;
            return;
        }
        if (!(*no)->esquerda || !(*no)->direita) 
		{
            if (!(*no)->esquerda) 
			{
                Nodo* aux = (*no)->direita;
                aux->pai = (*no)->pai;
                free((*no));
                (*no) = aux;
            } 
			else 
			{
                Nodo* aux = (*no)->esquerda;
                aux->pai = (*no)->pai;
                free((*no));
                (*no) = aux;
            }
            return;
        }
        if ((*no)->esquerda && (*no)->direita) 
		{
            Nodo** aux = menorNo(&(*no)->direita);
            (*no)->chave = (*aux)->chave;
            removeNo(aux, (*aux)->chave);
            return;
        }
    }
}

void limparArvore(Nodo* raiz) 
{
    if (raiz == NULL)
        return;
    limparArvore(raiz->esquerda);
    limparArvore(raiz->direita);
    free(raiz);
}

int main() 
{
    int chave;
    int operacao;
    Nodo* raiz = NULL;

    while (5) 
	{
        printf("\n(1)inserir\n(2)buscar\n(3)remover\n(4)printar\n(5)sair:\n\n");
        scanf(" %d", &operacao);

        if (operacao == 5)
            break;

        switch (operacao) 
		{
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &chave);
                raiz = inserir_arvore(raiz, chave);
                break;
            case 2:
                printf("Digite a chave a ser buscada: ");
                scanf("%d", &chave);
                if (buscaNodo(raiz, chave) != NULL)
                    printf("Chave encontrada na arvore.\n");
                else
                    printf("Chave nao encontrada na arvore.\n");
                break;
            case 3:
                printf("Digite a chave a ser removida: ");
                scanf("%d", &chave);
                removeNo(&raiz, chave);
                break;
            case 4:
                printf("arvore em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            default:
                printf("Operacao invalida.\n");
        }
    }
    limparArvore(raiz);
    return 0;
}