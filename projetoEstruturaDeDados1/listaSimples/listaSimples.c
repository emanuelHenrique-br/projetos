#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char nomePessoa[100];
    int idadePessoa;
    struct pessoa *proximaPessoa;
} Pessoa;

// --- Protótipos das Funções ---
void adicionarPessoaBusca(Pessoa **pessoa, char nomePessoa[100], int idadePessoa, int posicaoBuscada);
void adicionarPessoaCrescente(Pessoa **pessoa, char nomePessoa[100], int idadePessoa);
void removerPessoa(Pessoa **pessoa, int posicaoBuscada);
void removerTodasPessoas(Pessoa **pessoa);
void dividirPessoas(Pessoa **pessoa, Pessoa **novaPessoa, int posicaoBuscada);
void mostrarPessoas(Pessoa *pessoa);

// --- Função Principal ---
int main() {
    int continuar = 1;
    int op;
    char nome[100];
    int idade;
    int posicaoBuscada;
    
    // Lista principal e lista secundária (para a função dividir)
    Pessoa *raiz = NULL;
    Pessoa *raiz2 = NULL;

    while (continuar != 0) {
        printf("\n\n=== MENU ===\n");
        printf("1 - Adicionar pessoa na posicao desejada\n");
        printf("2 - Adicionar pessoa (Crescente por idade)\n");
        printf("3 - Remover pessoa por posicao\n");
        printf("4 - Remover todas as pessoas\n");
        printf("5 - Dividir as pessoas em duas listas\n");
        printf("6 - Mostrar as pessoas\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        if (op == 1) {
            printf("Digite o nome: ");
            scanf("%s", nome);
            printf("Digite a idade: ");
            scanf("%d", &idade);
            printf("Digite a posicao para inserir (0 eh o inicio): ");
            scanf("%d", &posicaoBuscada);
            adicionarPessoaBusca(&raiz, nome, idade, posicaoBuscada);
        }
        else if (op == 2) {
            printf("Digite o nome: ");
            scanf("%s", nome);
            printf("Digite a idade: ");
            scanf("%d", &idade);
            adicionarPessoaCrescente(&raiz, nome, idade);
        }
        else if (op == 3) {
            printf("Informe a posicao para remover: ");
            scanf("%d", &posicaoBuscada);
            removerPessoa(&raiz, posicaoBuscada);
        }
        else if (op == 4) {
            removerTodasPessoas(&raiz);
            printf("Todas as pessoas foram removidas.\n");
        }
        else if (op == 5) {
            printf("Informe a posicao onde a lista sera cortada: ");
            scanf("%d", &posicaoBuscada);
            
            // Limpa a lista 2 antiga antes de dividir de novo, para evitar lixo
            removerTodasPessoas(&raiz2); 
            
            dividirPessoas(&raiz, &raiz2, posicaoBuscada);
            printf("Lista dividida com sucesso!\n");
            
            printf("--- Conteudo da Lista 2 (Nova) ---\n");
            mostrarPessoas(raiz2);
        }
        else if (op == 6) {
            printf("--- Conteudo da Lista 1 (Principal) ---\n");
            mostrarPessoas(raiz);
        }

        printf("\nPressione 0 para SAIR ou 1 para CONTINUAR: ");
        scanf("%d", &continuar);
    }
    
    // Limpeza de memória antes de fechar o programa
    removerTodasPessoas(&raiz);
    removerTodasPessoas(&raiz2);
    
    return 0;
}

// --- Implementação das Funções ---

void adicionarPessoaBusca(Pessoa **pessoa, char nomePessoa[100], int idadePessoa, int posicaoBuscada) {
    if ((*pessoa) != NULL && posicaoBuscada > 0) {
        // Ainda não chegamos na posição e a lista não acabou
        adicionarPessoaBusca(&(*pessoa)->proximaPessoa, nomePessoa, idadePessoa, posicaoBuscada - 1);
    } else {
        // Chegou na posição desejada ou no fim da lista
        Pessoa *pessoaTemporaria = (Pessoa*) malloc(sizeof(Pessoa));
        if (pessoaTemporaria == NULL) return; // Erro de alocação

        pessoaTemporaria->idadePessoa = idadePessoa;
        strcpy(pessoaTemporaria->nomePessoa, nomePessoa);
        
        pessoaTemporaria->proximaPessoa = (*pessoa);
        (*pessoa) = pessoaTemporaria;
    }
}

void adicionarPessoaCrescente(Pessoa **pessoa, char nomePessoa[100], int idadePessoa) {
    // Se a pessoa atual existe e é MAIS NOVA que a nova pessoa, avançamos
    if ((*pessoa) != NULL && (*pessoa)->idadePessoa <= idadePessoa) {
        adicionarPessoaCrescente(&(*pessoa)->proximaPessoa, nomePessoa, idadePessoa);
        return;
    }

    // Inserção (quando a lista é vazia ou achamos alguém mais velho)
    Pessoa *pessoaTemporaria = (Pessoa*) malloc(sizeof(Pessoa));
    if (pessoaTemporaria == NULL) return;

    pessoaTemporaria->idadePessoa = idadePessoa;
    strcpy(pessoaTemporaria->nomePessoa, nomePessoa);

    pessoaTemporaria->proximaPessoa = (*pessoa);
    (*pessoa) = pessoaTemporaria;
}

void removerPessoa(Pessoa **pessoa, int posicaoBuscada) {
    if (*pessoa != NULL && posicaoBuscada > 0) {
        removerPessoa(&(*pessoa)->proximaPessoa, posicaoBuscada - 1);
        return;
    }

    if (*pessoa == NULL) return; // Posição inválida

    Pessoa *pessoaTemporaria = (*pessoa)->proximaPessoa;
    free(*pessoa);
    *pessoa = pessoaTemporaria;
}

void removerTodasPessoas(Pessoa **pessoa) {
    while ((*pessoa) != NULL) {
        Pessoa *pessoaTemporaria = (*pessoa)->proximaPessoa;
        free(*pessoa);
        *pessoa = pessoaTemporaria;
    }
}

void dividirPessoas(Pessoa **pessoa, Pessoa **novaPessoa, int posicaoBuscada) {
    if ((*pessoa) != NULL && posicaoBuscada > 0) {
        dividirPessoas(&(*pessoa)->proximaPessoa, novaPessoa, posicaoBuscada - 1);
        return;
    }

    // O ponteiro atual vira o início da nova lista
    *novaPessoa = *pessoa;
    // O ponteiro anterior (da lista original) passa a apontar para NULL
    *pessoa = NULL;
}

void mostrarPessoas(Pessoa *pessoa) {
    if (pessoa == NULL) {
        printf("Lista Vazia!!\n");
        return;
    }

    int i = 0;
    while (pessoa != NULL) {
        printf("[%d] Nome: %s | Idade: %d\n", i, pessoa->nomePessoa, pessoa->idadePessoa);
        pessoa = pessoa->proximaPessoa;
        i++;
    }
}