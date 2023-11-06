#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    char telefone[15];
} Contato;

typedef struct lista {
    Contato contato;
    struct lista* proximo;
    struct lista* anterior;
} LISTA;

Contato entrada_contato(void);
LISTA* inserir_contato(LISTA* lista, Contato contato);
void consultar_contato(LISTA* lista, char nome[]);
LISTA* excluir_contato(LISTA* lista, char nome[]);
void alterar_contato(LISTA* lista, char nome[], char novoTelefone[]);
void listar_contatos(LISTA* lista);

int main() {
    int opcao;
    LISTA* lista = NULL;
    char nome[50];
    char novoTelefone[15];

    do {
        system("cls");
        printf("Bem-vindo ao cadastro de contatos:\n");
        printf("1 - Inserir\n");
        printf("2 - Consultar\n");
        printf("3 - Excluir\n");
        printf("4 - Alterar\n");
        printf("5 - Listar\n");
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %i", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                lista = inserir_contato(lista, entrada_contato());
                printf("Contato inserido com sucesso!\n");
                break;
            case 2:
                printf("Digite o nome do contato a ser consultado: ");
                gets(nome);
                fflush(stdin);
                consultar_contato(lista, nome);
                break;
            case 3:
                printf("Digite o nome do contato a ser excluido: ");
                gets(nome);
                fflush(stdin);
                lista = excluir_contato(lista, nome);
                break;
            case 4:
                printf("Digite o nome do contato a ser alterado: ");
                gets(nome);
                fflush(stdin);
                printf("Digite o novo telefone: ");
                gets(novoTelefone);
                fflush(stdin);
                alterar_contato(lista, nome, novoTelefone);
                break;
            case 5:
                listar_contatos(lista);
                break;
            case 6:
                exit(0);
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        printf("Pressione algo para continuar\n");
        getchar();
    } while (opcao != 6);

    return 0;
}

Contato entrada_contato(void) {
    Contato contato;

    printf("Digite o nome: ");
    gets(contato.nome);
    fflush(stdin);
    printf("Digite o telefone: ");
    gets(contato.telefone);
    fflush(stdin);

    return contato;
}

LISTA* inserir_contato(LISTA* lista, Contato contato) {
    LISTA* novoContato = (LISTA*)malloc(sizeof(LISTA));
    novoContato->contato = contato;
    novoContato->proximo = NULL;

    if (lista == NULL) {
        novoContato->anterior = NULL;
        return novoContato;
    } else {
        LISTA* atual = lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoContato;
        novoContato->anterior = atual;
        return lista;
    }
}

void consultar_contato(LISTA* lista, char nome[]) {
    LISTA* atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0) {
            printf("Nome: %s\nTelefone: %s\n", atual->contato.nome, atual->contato.telefone);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Contato nao encontrado!\n");
    }
}

LISTA* excluir_contato(LISTA* lista, char nome[]) {
    LISTA* atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0) {
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                lista = atual->proximo;
            }
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            }
            free(atual);
            printf("Contato excluido com sucesso!\n");
            return lista;
        }
        atual = atual->proximo;
    }

    printf("Contato nao encontrado!\n");
    return lista;
}

void alterar_contato(LISTA* lista, char nome[], char novoTelefone[]) {
    LISTA* atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0) {
            strcpy(atual->contato.telefone, novoTelefone);
            printf("Contato alterado com sucesso!\n");
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void listar_contatos(LISTA* lista) {
    LISTA* atual = lista;

    if (atual == NULL) {
        printf("A lista de contatos esta vazia.\n");
    } else {
        printf("Lista de Contatos:\n");
        while (atual != NULL) {
            printf("Nome: %s\nTelefone: %s\n\n", atual->contato.nome, atual->contato.telefone);
            atual = atual->proximo;
        }
    }
}
