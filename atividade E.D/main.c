#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

// UTIL 
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));

    if (!novo) {
        printf("\n[ERRO] Falha de alocacao de memoria!\n");
        return NULL;
    }

    novo->valor = valor;
    novo->prox = NULL;
    return novo;
}

int tamanhoLista(No *lista) {
    int cont = 0;
    while (lista) {
        cont++;
        lista = lista->prox;
    }
    return cont;
}

// LEITURA S...
int lerInteiro(const char *msg) {
    int valor;
    int ok;

    do {
        printf("%s", msg);
        ok = scanf("%d", &valor);

        if (ok != 1) {
            printf("[ERRO] Entrada invalida! Digite um numero.\n");
            while (getchar() != '\n'); // limpa buffer
        }

    } while (ok != 1);

    return valor;
}

// INSERÇÕES
void inserirInicio(No **lista, int valor) {
    No *novo = criarNo(valor);
    if (!novo) return;

    novo->prox = *lista;
    *lista = novo;
}

void inserirFinal(No **lista, int valor) {
    No *novo = criarNo(valor);
    if (!novo) return;

    if (*lista == NULL) {
        *lista = novo;
        return;
    }

    No *aux = *lista;
    while (aux->prox)
        aux = aux->prox;

    aux->prox = novo;
}

void inserirMeio(No **lista, int valor, int pos) {
    int tam = tamanhoLista(*lista);

    if (pos < 0 || pos > tam) {
        printf("\n[ERRO] Posicao invalida!\n");
        return;
    }

    if (pos == 0) {
        inserirInicio(lista, valor);
        return;
    }

    No *novo = criarNo(valor);
    if (!novo) return;

    No *aux = *lista;
    for (int i = 0; i < pos - 1; i++)
        aux = aux->prox;

    novo->prox = aux->prox;
    aux->prox = novo;
}

// IMPRESSÃO
void imprimirLista(No *lista) {
    if (!lista) {
        printf("\n[INFO] Lista vazia.\n");
        return;
    }

    printf("\nLista: ");

    int contador = 0;
    while (lista && contador < 50) {
        printf("[%d] -> ", lista->valor);
        lista = lista->prox;
        contador++;
    }

    if (contador == 50)
        printf("... POSSIVEL LOOP NA LISTA!\n");
    else
        printf("NULL\n");
}

// REMOÇÃO
void apagarElemento(No **lista, int valor) {
    if (*lista == NULL) {
        printf("\n[INFO] Lista vazia.\n");
        return;
    }

    No *atual = *lista;
    No *anterior = NULL;
    int removidos = 0;

    while (atual) {
        if (atual->valor == valor) {
            No *temp = atual;

            if (anterior == NULL) {
                *lista = atual->prox;
                atual = *lista;
            } else {
                anterior->prox = atual->prox;
                atual = atual->prox;
            }

            free(temp);
            removidos++;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    printf("\n[INFO] %d elemento(s) removido(s).\n", removidos);
}

void apagarLista(No **lista) {
    No *atual = *lista;

    while (atual) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    *lista = NULL;
    printf("\n[INFO] Lista totalmente removida.\n");
}

// MENU
void menu() {
    printf("\n MENU \n");
    printf("0 - Sair\n");
    printf("1 - Inserir no Inicio\n");
    printf("2 - Inserir no Final\n");
    printf("3 - Inserir no Meio\n");
    printf("4 - Imprimir\n");
    printf("5 - Apagar Elemento\n");
    printf("6 - Apagar Lista\n");
    printf(" \n");
}

// MAIN
int main() {
    No *lista = NULL;
    int opcao, valor, pos;

    do {
        menu();
        opcao = lerInteiro("Escolha: ");

        switch (opcao) {
            case 1:
                valor = lerInteiro("Valor: ");
                inserirInicio(&lista, valor);
                break;

            case 2:
                valor = lerInteiro("Valor: ");
                inserirFinal(&lista, valor);
                break;

            case 3:
                valor = lerInteiro("Valor: ");
                pos = lerInteiro("Posicao: ");
                inserirMeio(&lista, valor, pos);
                break;

            case 4:
                imprimirLista(lista);
                break;

            case 5:
                valor = lerInteiro("Valor a remover: ");
                apagarElemento(&lista, valor);
                break;

            case 6:
                apagarLista(&lista);
                break;

            case 0:
                apagarLista(&lista);
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}