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
    FILE *arquivo1 = fopen("saida1.txt","w");
    FILE *arquivo2 = fopen("saida2.txt","w");
    FILE *atual = arquivo1;
    int nivel = 0;
    Elemts *menor;

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

    
    buildHeap(vetor,espaco_memoria);
    
    while(fscanf(arquivo, "%ld", &numero) != EOF) {
        menor = vetor[0];
        if (menor->marca > nivel) { //Trocar de bloco
                fprintf(atual,"-1\n");
                atual = (atual == arquivo1) ? arquivo2 : arquivo1;
                nivel += 1;
        }
        fprintf(atual,"%ld\n",menor->valor); //inserindo no arquivo

        menor->marca = numero < menor->valor ? menor->marca + 1 : menor->marca;
        menor->valor = numero;

        buildHeap(vetor,espaco_memoria);

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