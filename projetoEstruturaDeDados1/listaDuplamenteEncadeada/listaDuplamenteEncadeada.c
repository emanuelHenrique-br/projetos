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

// Protótipos
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
    Pessoa *pessoa = NULL; // Inicializa a lista vazia

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
    if (novo == NULL) return; // Verificação de erro de memória

    novo->idade = idade;
    novo->proximaPessoa = *pessoa; // O próximo do novo é o antigo primeiro
    novo->anteriorPessoa = NULL;   // Como é início, anterior é NULL

    if (*pessoa != NULL)
    {
        (*pessoa)->anteriorPessoa = novo; // O antigo primeiro aponta para trás para o novo
    }
    
    *pessoa = novo; // Atualiza a cabeça da lista
}

void inserePessoaMeio(Pessoa **pessoa, int idade, int apos)
{
    if (*pessoa == NULL)
    {
        printf("Lista vazia ou elemento nao encontrado.\n");
        return;
    }

    Pessoa *aux = *pessoa;
    
    // Procura o elemento "apos"
    while(aux != NULL && aux->idade != apos) {
        aux = aux->proximaPessoa;
    }

    // Se aux for NULL, não achou o elemento
    if(aux == NULL) {
        printf("Idade %d nao encontrada na lista.\n", apos);
        return;
    }

    // Achou, vamos alocar agora
    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    novo->idade = idade;
    
    novo->proximaPessoa = aux->proximaPessoa;
    novo->anteriorPessoa = aux;

    // Se não for o último, arruma o ponteiro de trás do próximo
    if (aux->proximaPessoa != NULL) {
        aux->proximaPessoa->anteriorPessoa = novo;
    }

    aux->proximaPessoa = novo;
}

void inserePessoaFim(Pessoa **pessoa, int idade)
{   
    Pessoa *novo = (Pessoa *)malloc(sizeof(Pessoa));
    novo->idade = idade;
    novo->proximaPessoa = NULL; // Como é fim, o próximo é NULL

    // Se a lista estiver vazia, insere no início
    if (*pessoa == NULL)
    {
        novo->anteriorPessoa = NULL;
        *pessoa = novo;
        return;
    }

    // Percorre até o último elemento
    Pessoa *aux = *pessoa;
    while(aux->proximaPessoa != NULL)
    {
        aux = aux->proximaPessoa;
    }

    // Faz as ligações
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

    Pessoa *temp = *pessoa; // Salva o nó a ser removido
    *pessoa = temp->proximaPessoa; // Avança a cabeça da lista

    if (*pessoa != NULL)
    {
        (*pessoa)->anteriorPessoa = NULL; // O novo início não tem anterior
    }

    free(temp); // Libera a memória do antigo início
}

void removePessoaMeio(Pessoa **pessoa, int idade)
{
    if (*pessoa == NULL) return;

    Pessoa *aux = *pessoa;

    // Procura o elemento
    while (aux != NULL && aux->idade != idade)
    {
        aux = aux->proximaPessoa;
    }

    if (aux == NULL) {
        printf("Elemento nao encontrado.\n");
        return;
    }

    // Se for o primeiro elemento
    if (aux == *pessoa)
    {
        removePessoaInicio(pessoa);
    }
    else
    {
        // Liga o anterior ao próximo
        aux->anteriorPessoa->proximaPessoa = aux->proximaPessoa;

        // Se NÃO for o último elemento, liga o próximo ao anterior
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

    // Se tiver só um elemento
    if ((*pessoa)->proximaPessoa == NULL)
    {
        free(*pessoa);
        *pessoa = NULL;
        return;
    }

    // Percorre até o último
    Pessoa *aux = *pessoa;
    while (aux->proximaPessoa != NULL)
    {
        aux = aux->proximaPessoa;
    }

    // Aux agora é o último. O penúltimo deve apontar para NULL
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