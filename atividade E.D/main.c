#include <stdio.h>
#include <stdlib.h>


// Parte a: Resolução por ponteiros
void calcular_por_ponteiros(int *num, int *dobro, int *triplo) {
    *dobro = *num * 2;
    *triplo = *num * 3;
}

// Parte b: Resolução por alocação dinâmica
void calcular_por_alocacao_dinamica(int num) {
    int *numero = (int *)malloc(sizeof(int));
    if (numero == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return;
    }
    *numero = num;
    int *dobro = (int *)malloc(sizeof(int));
    int *triplo = (int *)malloc(sizeof(int));
    if (dobro == NULL || triplo == NULL) {
        printf("Erro na alocacao de memoria.\n");
        free(numero);
        free(dobro);
        free(triplo);
        return;
    }
    *dobro = *numero * 2;
    *triplo = *numero * 3;
    printf("Por alocacao dinamica: Dobro = %d, Triplo = %d\n", *dobro, *triplo);
    free(numero);
    free(dobro);
    free(triplo);  
}

int main() {
    int numero;
    printf("Digite um numero: ");
    scanf("%d", &numero);

    // Parte a: Usando ponteiros
    int dobro, triplo;
    calcular_por_ponteiros(&numero, &dobro, &triplo);
    printf("Por ponteiros: Dobro = %d, Triplo = %d\n", dobro, triplo);

    // Parte b: Usando alocação dinâmica
    calcular_por_alocacao_dinamica(numero);

    return 0;
}
