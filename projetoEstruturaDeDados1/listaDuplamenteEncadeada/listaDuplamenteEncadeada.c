#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Pessoa
{
    int idade;
    struct Pessoa *proximaPessoa;
    struct Pessoa *anteriorPessoa;
} Pessoa;

void inserePessoaInicio(Pessoa **pessoa, int idade);
void inserePessoaMeio(Pessoa **pessoa, int idade, int apos);
void inserePessoaFim(Pessoa **pessoa, int idade);
void removePessoaInicio(Pessoa **pessoa);
void removePessoaMeio(Pessoa **pessoa, int idade);
void removePessoaFim(Pessoa **pessoa);
void imprimePessoa(Pessoa *pessoa);

int main()
{
    int op = 1;
    int idade;
    int apos;
    Pessoa *pessoa = NULL; 
    while(op != 0)
    {
        printf("\n--- MENU ---\n");
        printf("1 - Inserir no inicio\n");
        printf("2 - Inserir no meio (apos X idade)\n");
        printf("3 - Inserir no fim\n");
        printf("4 - Remover no inicio\n");
        printf("5 - Remover valor especifico\n");
        printf("6 - Remover no fim\n");
        printf("7 - Imprimir lista\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if(op == 1)
        {
            printf("Digite a idade: ");
            scanf("%d", &idade);
            inserePessoaInicio(&pessoa, idade);
        }
        else if(op == 2)
        {
            printf("Digite a idade a inserir: ");
            scanf("%d", &idade);
            printf("Inserir apos qual idade? ");
            scanf("%d", &apos);
            inserePessoaMeio(&pessoa, idade, apos); 
        }
        else if(op == 3)
        {
            printf("Digite a idade: ");
            scanf("%d", &idade);
            inserePessoaFim(&pessoa, idade);
        }
        else if(op == 4)
        {
            removePessoaInicio(&pessoa);
        }
        else if(op == 5)
        {
            printf("Digite a idade a remover: ");
            scanf("%d", &idade);
            removePessoaMeio(&pessoa, idade);   
        }
        else if(op == 6)
        {
            removePessoaFim(&pessoa);
        }
        else if(op == 7)
        {
            imprimePessoa(pessoa);
        }
    }
    return 0;
}   

void inserePessoaInicio(Pessoa **pessoa, int idade)
{
    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    if (novo == NULL) return; 

    novo->idade = idade;
    novo->proximaPessoa = *pessoa; 
    novo->anteriorPessoa = NULL;   

    if (*pessoa != NULL)
    {
        (*pessoa)->anteriorPessoa = novo; 
    }
    
    *pessoa = novo; 
}

void inserePessoaMeio(Pessoa **pessoa, int idade, int apos)
{
    if (*pessoa == NULL)
    {
        printf("Lista vazia ou elemento nao encontrado.\n");
        return;
    }

    Pessoa *aux = *pessoa;
    
    while(aux != NULL && aux->idade != apos) {
        aux = aux->proximaPessoa;
    }

    if(aux == NULL) {
        printf("Idade %d nao encontrada na lista.\n", apos);
        return;
    }

    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    novo->idade = idade;
    
    novo->proximaPessoa = aux->proximaPessoa;
    novo->anteriorPessoa = aux;

    if (aux->proximaPessoa != NULL) {
        aux->proximaPessoa->anteriorPessoa = novo;
    }

    aux->proximaPessoa = novo;
}

void inserePessoaFim(Pessoa **pessoa, int idade)
{   
    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    novo->idade = idade;
    novo->proximaPessoa = NULL; L

    if (*pessoa == NULL)
    {
        novo->anteriorPessoa = NULL;
        *pessoa = novo;
        return;
    }

    Pessoa *aux = *pessoa;
    while(aux->proximaPessoa != NULL)
    {
        aux = aux->proximaPessoa;
    }

    aux->proximaPessoa = novo;
    novo->anteriorPessoa = aux;
}

void removePessoaInicio(Pessoa **pessoa)
{
    if (*pessoa == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    Pessoa *temp = *pessoa; 
    *pessoa = temp->proximaPessoa; 

    if (*pessoa != NULL)
    {
        (*pessoa)->anteriorPessoa = NULL; 
    }
    free(temp); 
}

void removePessoaMeio(Pessoa **pessoa, int idade)
{
    if (*pessoa == NULL) return;

    Pessoa *aux = *pessoa;

    while (aux != NULL && aux->idade != idade)
    {
        aux = aux->proximaPessoa;
    }

    if (aux == NULL) {
        printf("Elemento nao encontrado.\n");
        return;
    }

    if (aux == *pessoa)
    {
        removePessoaInicio(pessoa);
    }
    else
    {
        aux->anteriorPessoa->proximaPessoa = aux->proximaPessoa;
        if (aux->proximaPessoa != NULL)
        {
            aux->proximaPessoa->anteriorPessoa = aux->anteriorPessoa;
        }
        free(aux);
    }
}

void removePessoaFim(Pessoa **pessoa)
{
    if (*pessoa == NULL) return;

    if ((*pessoa)->proximaPessoa == NULL)
    {
        free(*pessoa);
        *pessoa = NULL;
        return;
    }

    Pessoa *aux = *pessoa;
    while (aux->proximaPessoa != NULL)
    {
        aux = aux->proximaPessoa;
    }

    if (aux->anteriorPessoa != NULL) {
        aux->anteriorPessoa->proximaPessoa = NULL;
    }

    free(aux);
}

void imprimePessoa(Pessoa *pessoa)
{
    if (pessoa == NULL)
    {
        printf("Lista vazia\n");
        return;
    }
    
    printf("\n--- Lista (Do Inicio ao Fim) ---\n");
    Pessoa *aux = pessoa;
    while (aux != NULL)
    {
        printf("Idade: %d", aux->idade);

        if (aux->anteriorPessoa != NULL)
            printf(" | Ant: %d", aux->anteriorPessoa->idade);
        else
            printf(" | Ant: NULL");

        if (aux->proximaPessoa != NULL)
            printf(" | Prox: %d", aux->proximaPessoa->idade);
        else
            printf(" | Prox: NULL");

        printf("\n");
        aux = aux->proximaPessoa;
    }
    printf("\n");

}
