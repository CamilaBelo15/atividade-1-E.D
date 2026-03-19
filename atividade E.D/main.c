#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct No {
    int valor;
    struct No *prox;
} No;

// Função pra criar nó
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: Falta de memoria!\n");
        return NULL;
    }

    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

// Inserir no início
No* inserirInicio(No *lista, int valor) {
    No *novo = criarNo(valor);
    if (novo == NULL) return lista;

    novo->prox = lista;
    return novo;
}

// Inserir no final
No* inserirFinal(No *lista, int valor) {
    No *novo = criarNo(valor);
    if (novo == NULL) return lista;

    if (lista == NULL) return novo;

    No *aux = lista;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }

    aux->prox = novo;
    return lista;
}

// Inserir no meio 
No* inserirMeio(No *lista, int valor, int pos) {
    if (pos == 0) return inserirInicio(lista, valor);

    No *novo = criarNo(valor);
    if (novo == NULL) return lista;

    No *aux = lista;
    int i = 0;

    while (aux != NULL && i < pos - 1) {
        aux = aux->prox;
        i++;
    }

    if (aux == NULL) {
        printf("Posicao invalida!\n");
        free(novo);
        return lista;
    }

    novo->prox = aux->prox;
    aux->prox = novo;

    return lista;
}

// Imprimi lista
void imprimir(No *lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *aux = lista;
    while (aux != NULL) {
        printf("%d -> ", aux->valor);
        aux = aux->prox;
    }
    printf("NULL\n");
}

// Apagar elementos com valor específico
No* apagarElemento(No *lista, int valor) {
    No *aux = lista;
    No *ant = NULL;

    while (aux != NULL) {
        if (aux->valor == valor) {
            if (ant == NULL) {
                lista = aux->prox;
                free(aux);
                aux = lista;
            } else {
                ant->prox = aux->prox;
                free(aux);
                aux = ant->prox;
            }
        } else {
            ant = aux;
            aux = aux->prox;
        }
    }

    return lista;
}

// Apagar lista
No* apagarLista(No *lista) {
    No *aux;

    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

    printf("Lista apagada!\n");
    return NULL;
}

// Menu
int main() {
    No *lista = NULL;
    int opcao, valor, pos;

    do {
        printf("\n--- MENU ---\n");
        printf("0 - Sair\n");
        printf("1 - Inserir no Inicio\n");
        printf("2 - Inserir no Final\n");
        printf("3 - Inserir no Meio\n");
        printf("4 - Imprimir\n");
        printf("5 - Apagar Elemento\n");
        printf("6 - Apagar Lista\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                lista = inserirInicio(lista, valor);
                break;

            case 2:
                printf("Valor: ");
                scanf("%d", &valor);
                lista = inserirFinal(lista, valor);
                break;

            case 3:
                printf("Valor: ");
                scanf("%d", &valor);
                printf("Posicao: ");
                scanf("%d", &pos);
                lista = inserirMeio(lista, valor, pos);
                break;

            case 4:
                imprimir(lista);
                break;

            case 5:
                printf("Valor a remover: ");
                scanf("%d", &valor);
                lista = apagarElemento(lista, valor);
                break;

            case 6:
                lista = apagarLista(lista);
                break;

            case 0:
                lista = apagarLista(lista);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}