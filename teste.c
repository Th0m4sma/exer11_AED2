#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct fita{
    FILE *arquivo;
    int *vetor_quant;
    int quant_blocos;
}Fita;


int main(void) {
    FILE *arquivo = fopen("teste.txt", "r");
    Elemts **vetor = (Elemts **) malloc(espaco_memoria * sizeof(Elemts *));
    long int numero;
    int i = 0;


    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 1;
    }


    //Alocando elementos do meu vetor:
    printf("Numeros lidos: \n");
    while ( i < espaco_memoria) {
        vetor[i] = (Elemts *) malloc(sizeof(Elemts));

        if (vetor[i] == NULL) {
            printf("Erro ao alocar memória para vetor[%d].\n", i);
            break;
        }

        fscanf(arquivo, "%ld", &numero);
        vetor[i]->valor = numero;
        vetor[i]->marca = 0; 

        
        printf("Numero: %ld\n", vetor[i]->valor);

        i++;
    }


























    // Libera a memória alocada para cada elemento
    for (int j = 0; j < i; j++) {
        free(vetor[j]);
    }
    
    // Libera o vetor de ponteiros
    free(vetor);
    
    // Fecha o arquivo
    fclose(arquivo);

    return 0;
}