#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da Pessoa (Nó da lista)
typedef struct pessoa {
    char *nomePessoa;
    int idadePessoa;
    struct pessoa *proximaPessoa;
} Pessoa;

// 

// Definição do descritor da Lista
typedef struct listaPessoas {
    Pessoa *primeiraPessoa;
    int quantidadePessoas;
} ListaPessoas;

// Protótipos
ListaPessoas *inicializarListaPessoas();
void adicionarPessoaBusca(Pessoa **pessoa, char *nomePessoa, int idadePessoa, int posicaoBuscada);
void adicionarPessoaCrescente(Pessoa **pessoa, char *nomePessoa, int idadePessoa);
void removerPessoa(Pessoa **pessoa, int posicaoBuscada);
void removerTodasPessoas(Pessoa **pessoa);
void dividirPessoas(Pessoa **pessoa, Pessoa **novaPessoa, int posicaoBuscada);
void mostrarPessoas(Pessoa *pessoa);
void armazenarPessoaConteudo(ListaPessoas **listaPessoas);

int main() {
    // Inicializa as listas
    ListaPessoas *NovaPessoa = inicializarListaPessoas(); // Lista usada para divisão
    ListaPessoas *pessoa = inicializarListaPessoas();     // Lista principal

    int op = 1;
    int posicao;
    int idade;
    char nome[100];

    while (op != 0) {
        printf("\n--- MENU ---\n");
        printf("1 - Adicionar pessoa (posicao especifica)\n");
        printf("2 - Adicionar pessoa (ordem crescente de idade)\n");
        printf("3 - Remover pessoa por posicao\n");
        printf("4 - Remover todas as pessoas\n");
        printf("5 - Dividir lista de pessoas\n");
        printf("6 - Mostrar pessoas\n");
        printf("7 - Armazenar pessoa (via funcao auxiliar)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op == 1) {
            printf("Informe nome: ");
            scanf("%s", nome); // CORREÇÃO: Removido '&' pois 'nome' já é um endereço
            printf("Escolha a idade da pessoa: ");
            scanf("%d", &idade);
            printf("Informe a posicao buscada: ");
            scanf("%d", &posicao);
            
            // CORREÇÃO: Passar o endereço do ponteiro do PRIMEIRO NÓ, não da estrutura da lista
            adicionarPessoaBusca(&(pessoa->primeiraPessoa), nome, idade, posicao);
            pessoa->quantidadePessoas++;
        } 
        else if (op == 2) {
            printf("Informe nome: ");
            scanf("%s", nome);
            printf("Escolha a idade da pessoa: ");
            scanf("%d", &idade);
            
            // CORREÇÃO: Passar o endereço do ponteiro do nó
            adicionarPessoaCrescente(&(pessoa->primeiraPessoa), nome, idade);
            pessoa->quantidadePessoas++;
        } 
        else if (op == 3) {
            printf("Informe a posicao da pessoa para remover: ");
            scanf("%d", &posicao); // CORREÇÃO: Adicionado '&' que faltava
            removerPessoa(&(pessoa->primeiraPessoa), posicao);
            if(pessoa->quantidadePessoas > 0) pessoa->quantidadePessoas--;
        } 
        else if (op == 4) {
            removerTodasPessoas(&(pessoa->primeiraPessoa));
            pessoa->quantidadePessoas = 0;
        } 
        else if (op == 5) {
            printf("Escolha a posicao de corte: ");
            scanf("%d", &posicao);
            // CORREÇÃO: Passar os ponteiros internos das duas listas
            dividirPessoas(&(pessoa->primeiraPessoa), &(NovaPessoa->primeiraPessoa), posicao);
            printf("Lista dividida! Verifique a segunda lista (implementar visualizacao se desejar).\n");
        } 
        else if (op == 6) {
            mostrarPessoas(pessoa->primeiraPessoa);
        } 
        else if (op == 7) {
            // CORREÇÃO: Passar o endereço do ponteiro da lista corretamente
            armazenarPessoaConteudo(&pessoa);
        }
    }
    
    // Boa prática: Limpar memória antes de sair (opcional mas recomendado)
    removerTodasPessoas(&(pessoa->primeiraPessoa));
    removerTodasPessoas(&(NovaPessoa->primeiraPessoa));
    free(pessoa);
    free(NovaPessoa);
    
    return 0;
}

ListaPessoas *inicializarListaPessoas() {
    ListaPessoas *listaPessoas = (ListaPessoas *)malloc(sizeof(ListaPessoas));

    if (listaPessoas == NULL) return NULL;

    listaPessoas->primeiraPessoa = NULL;
    listaPessoas->quantidadePessoas = 0;

    return listaPessoas;
}

void adicionarPessoaBusca(Pessoa **pessoa, char *nomePessoa, int idadePessoa, int posicaoBuscada) {
    if ((*pessoa) != NULL && posicaoBuscada > 0) { // Alterado para > 0 para lógica usual de posições 0, 1, 2...
        adicionarPessoaBusca(&(*pessoa)->proximaPessoa, nomePessoa, idadePessoa, posicaoBuscada - 1);
    } else {
        Pessoa *pessoaTemporaria = (Pessoa *)malloc(sizeof(Pessoa));

        if (pessoaTemporaria == NULL) return;

        pessoaTemporaria->idadePessoa = idadePessoa;
        // Aloca tamanho exato da string + 1 para o terminador nulo
        pessoaTemporaria->nomePessoa = (char *)malloc(strlen(nomePessoa) + 1);

        if (pessoaTemporaria->nomePessoa == NULL) {
            free(pessoaTemporaria);
            return;
        }

        strcpy(pessoaTemporaria->nomePessoa, nomePessoa);

        pessoaTemporaria->proximaPessoa = (*pessoa);
        (*pessoa) = pessoaTemporaria;
    }
}

void adicionarPessoaCrescente(Pessoa **pessoa, char *nomePessoa, int idadePessoa) {
    // Insere se a lista for nula OU se a idade atual for maior que a idade a inserir (para manter ordem crescente)
    if ((*pessoa) != NULL && (*pessoa)->idadePessoa <= idadePessoa) {
        adicionarPessoaCrescente(&(*pessoa)->proximaPessoa, nomePessoa, idadePessoa);
        return;
    }

    Pessoa *pessoaTemporaria = (Pessoa *)malloc(sizeof(Pessoa));

    if (pessoaTemporaria == NULL) return;

    pessoaTemporaria->idadePessoa = idadePessoa;
    pessoaTemporaria->nomePessoa = (char *)malloc(strlen(nomePessoa) + 1);

    if (pessoaTemporaria->nomePessoa == NULL) {
        free(pessoaTemporaria);
        return;
    }

    strcpy(pessoaTemporaria->nomePessoa, nomePessoa);

    pessoaTemporaria->proximaPessoa = (*pessoa);
    (*pessoa) = pessoaTemporaria;
}

void removerPessoa(Pessoa **pessoa, int posicaoBuscada) {
    if (*pessoa != NULL && posicaoBuscada > 0) {
        removerPessoa(&(*pessoa)->proximaPessoa, posicaoBuscada - 1);
        return;
    }

    if (*pessoa == NULL) return;

    Pessoa *pessoaTemporaria = (*pessoa)->proximaPessoa;
    
    // CORREÇÃO: Liberar a string nome antes de liberar o nó
    if((*pessoa)->nomePessoa != NULL) {
        free((*pessoa)->nomePessoa);
    }
    
    free(*pessoa);
    *pessoa = pessoaTemporaria;
}

void removerTodasPessoas(Pessoa **pessoa) {
    while ((*pessoa) != NULL) {
        Pessoa *pessoaTemporaria = (*pessoa)->proximaPessoa;
        
        // CORREÇÃO: Liberar memória do nome
        if((*pessoa)->nomePessoa != NULL) {
            free((*pessoa)->nomePessoa);
        }
        
        free(*pessoa);
        *pessoa = pessoaTemporaria;
    }
}

void dividirPessoas(Pessoa **pessoa, Pessoa **novaPessoa, int posicaoBuscada) {
    if ((*pessoa) != NULL && posicaoBuscada > 0) {
        dividirPessoas(&(*pessoa)->proximaPessoa, novaPessoa, posicaoBuscada - 1);
        return;
    }

    *novaPessoa = *pessoa;
    *pessoa = NULL;
}

void mostrarPessoas(Pessoa *pessoa) {
    int i = 0;
    while (pessoa != NULL) {
        printf("\n[%d] Nome: %s\n", i, pessoa->nomePessoa);
        printf("    Idade: %i\n", pessoa->idadePessoa);
        pessoa = pessoa->proximaPessoa;
        i++;
    }

    if (i == 0) {
        printf("\nLista Vazia!!\n");
    } else {
        printf("\nFim da lista.\n");
    }
}

void armazenarPessoaConteudo(ListaPessoas **listaPessoas) {
    // CORREÇÃO: Usar array estático aqui para evitar memory leak complexo
    char nome[100];
    int idade;
    int posicao;

    printf("Nome: ");
    scanf(" %s", nome);
    printf("Idade da pessoa: ");
    scanf("%i", &idade);
    printf("Posicao da pessoa: ");
    scanf("%i", &posicao);

    (*listaPessoas)->quantidadePessoas++;
    
    // Chama a função de inserção passando os dados
    adicionarPessoaBusca(&(*listaPessoas)->primeiraPessoa, nome, idade, posicao);
}