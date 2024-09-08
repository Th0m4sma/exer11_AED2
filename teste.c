#include <stdio.h>
#include <stdlib.h>

typedef struct elementos {
    int marca;
    long int valor;
} Elemts;

long int espaco_memoria = 3; // Espaço disponível na memória interna

void heapMin(Elemts **vetor, int pos) {
    int min;
    Elemts *aux;
    int l = (pos * 2) + 1;
    int r = (pos * 2) + 2;

    min = pos;
    
    if (l < espaco_memoria && (vetor[l]->marca < vetor[min]->marca || 
        (vetor[l]->marca == vetor[min]->marca && vetor[l]->valor < vetor[min]->valor))) {
        min = l;
    }

    if (r < espaco_memoria && (vetor[r]->marca < vetor[min]->marca || 
        (vetor[r]->marca == vetor[min]->marca && vetor[r]->valor < vetor[min]->valor))) {
        min = r;
    }

    if (min != pos) {
        aux = vetor[min];
        vetor[min] = vetor[pos];
        vetor[pos] = aux;

        heapMin(vetor, min);
    }
}

void buildHeap(Elemts **vetor, int quant) {
    for (int i = quant / 2 - 1; i >= 0; i--) {
        heapMin(vetor, i);
    }
}

/*
long int heap_Extract(Elemts **vetor, int *quant) {
    long int menor = vetor[0]->valor;
    vetor[0]->valor = vetor[*quant]->valor;
    (*quant)--;
    return menor;
}
*/

int todosMarcados(Elemts **vetor, int quant) {
    for (int i = 0; i < quant; i++) {
        if (vetor[i]->marca == 0) {  // Se algum elemento não foi marcado, retorna falso
            return 0;
        }
    }
    return 1;  // Todos os elementos estão marcados
}


// Função para processar os últimos elementos no heap
void processaRestantes(Elemts **vetor, FILE *arquivo1, FILE *arquivo2, int nivel, FILE *atual) {
    int sair = 1;
    long int ultimo = vetor[0]->valor;

    vetor[0]->valor = 100000;
    buildHeap(vetor, espaco_memoria);

    while (sair) {
        Elemts *menor = vetor[0]; // Pega o menor elemento do heap

        printf("Marca: %d, Nível: %d\n", menor->marca, nivel);

        if (todosMarcados(vetor, espaco_memoria) == 1) {  // Troca de arquivo se todos estiverem marcados
            printf("Todos os elementos foram marcados, trocando de arquivo.\n");
            fprintf(atual, "-1\n");
            atual = (atual == arquivo1) ? arquivo2 : arquivo1;  // Alterna entre os arquivos
            nivel += 1;
            // Reinicializa as marcas
            for (int j = 0; j < espaco_memoria; j++) {
                vetor[j]->marca = 0;
            }
        }

        fprintf(atual, "%ld\n", menor->valor);  // Inserindo o menor valor no arquivo
        ultimo = menor->valor;  // Atualiza 'ultimo' com o valor que acabou de ser inserido

        // Atualiza o valor da raiz do heap para remover o elemento processado
        vetor[0]->valor = 100000;  // Usa um valor muito alto para representar que esse elemento foi removido
        vetor[0]->marca = 1;  // Marca o elemento como "removido"
        
        buildHeap(vetor, espaco_memoria);  // Reorganiza o heap após a remoção

        // Checa se todos os elementos do heap foram processados
        int processados = 1;
        for (int i = 0; i < espaco_memoria; i++) {
            if (vetor[i]->valor != 100000) {
                processados = 0;
                break;
            }
        }

        // Se todos os elementos tiverem sido processados, sair do loop
        if (processados) {
            sair = 0;
        }
    }
}


void mescla_blocos(FILE *arquivo_principal, FILE *arquivo_saida1, FILE *arquivo_saida2) {
    long int numero1, numero2;
    int res1, res2;

    // Inicializa a leitura de ambos os arquivos
    res1 = fscanf(arquivo_saida1, "%ld", &numero1);
    res2 = fscanf(arquivo_saida2, "%ld", &numero2);

    // Mescla enquanto ambos os números forem válidos (nenhum deles atingiu o delimitador ou o fim)
    while (res1 == 1 && res2 == 1 && numero1 != -1 && numero2 != -1) {
        if (numero1 < numero2) {
            fprintf(arquivo_principal, "%ld\n", numero1);
            res1 = fscanf(arquivo_saida1, "%ld", &numero1);  // Lê o próximo número de arq1
        } else {
            fprintf(arquivo_principal, "%ld\n", numero2);
            res2 = fscanf(arquivo_saida2, "%ld", &numero2);  // Lê o próximo número de arq2
        }
    }

    // Processa os números restantes de arquivo_saida1 se arquivo_saida2 terminou
    while (res1 == 1 && numero1 != -1) {
        fprintf(arquivo_principal, "%ld\n", numero1);
        res1 = fscanf(arquivo_saida1, "%ld", &numero1);  // Continua lendo o restante
    }

    // Processa os números restantes de arquivo_saida2 se arquivo_saida1 terminou
    while (res2 == 1 && numero2 != -1) {
        fprintf(arquivo_principal, "%ld\n", numero2);
        res2 = fscanf(arquivo_saida2, "%ld", &numero2);  // Continua lendo o restante
    }

    // Escreve o delimitador de bloco no final
    fprintf(arquivo_principal, "-1\n");

    printf("Mesclagem de blocos concluída.\n");
}

void mescla_fitas(FILE *arq1, FILE *arq2, int quant_blocos,int tipo) {
    FILE *atual;
    FILE *arq_novo1;
    FILE *arq_novo2;
    atual = arq_novo1;
    int numero1, numero2;
    int res1, res2;

    if(tipo == 0) {
        arq_novo1 = fopen("teste1.txt", "w");
        arq_novo2 = fopen("teste2.txt", "w");
    }else{
        arq_novo1 = fopen("teste3.txt", "w");
        arq_novo2 = fopen("teste4.txt", "w");
    }

    for (int i = 0; i < quant_blocos; i++) {
        mescla_blocos(atual, arq1, arq2);

        // Alterna os arquivos de saída
        if (atual == arq_novo1) {
            atual = arq_novo2;
        } else {
            atual = arq_novo1;
        }
    }

    // Lendo os números restantes de arq1 e arq2
    res1 = fscanf(arq1, "%d", &numero1);
    res2 = fscanf(arq2, "%d", &numero2);

    // Escreve o restante de arq1 se arq2 estiver vazio, ignorando o -1
    while (res1 == 1 && numero1 != -1) {
        fprintf(atual, "%d\n", numero1);
        res1 = fscanf(arq1, "%d", &numero1);
    }

    // Escreve o restante de arq2 se arq1 estiver vazio, ignorando o -1
    while (res2 == 1 && numero2 != -1) {
        fprintf(atual, "%d\n", numero2);
        res2 = fscanf(arq2, "%d", &numero2);
    }

    // Escreve o delimitador de fim de bloco
    fprintf(atual, "-1\n");

    // Fechando os arquivos de saída
    fclose(arq_novo1);
    fclose(arq_novo2);
}


void intercalacao(FILE *arq1, FILE *arq2, int quantidade_blocos) {
    int tipo=0;

    // Enquanto houver mais de um bloco, continue a intercalação
    while (quantidade_blocos > 1) {
        if(tipo == 0) tipo =1;
        else tipo = 1;
        // Mescla blocos nos arquivos temporários
        mescla_fitas(arq1, arq2, quantidade_blocos,tipo);

        quantidade_blocos = quantidade_blocos-1;  
    }

    // Fecha os arquivos finais
    fclose(arq1);
    fclose(arq2);
}


int main(void) {
    FILE *arquivo = fopen("arquivo.txt", "r");
    FILE *arquivo1 = fopen("saida1.txt", "w");
    FILE *arquivo2 = fopen("saida2.txt", "w");
    FILE *atual = arquivo1;
    int nivel = 0;
    long int ultimo;
    Elemts *menor;

    Elemts **vetor = (Elemts **)malloc(espaco_memoria * sizeof(Elemts *));
    long int numero;
    int i = 0;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (arquivo1 == NULL || arquivo2 == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        fclose(arquivo);
        return 1;
    }

    if (vetor == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arquivo);
        return 1;
    }

    // Alocando elementos do vetor:
    printf("Números lidos: \n");

    while (i < espaco_memoria && fscanf(arquivo, "%ld", &numero) != EOF) {
        vetor[i] = (Elemts *)malloc(sizeof(Elemts));
        if (vetor[i] == NULL) {
            printf("Erro ao alocar memória para vetor[%d].\n", i);
            break;
        }
        vetor[i]->valor = numero;
        vetor[i]->marca = 0;
        printf("Numero: %ld\n", vetor[i]->valor);
        i++;
    }

    printf("Passou\n");
    buildHeap(vetor, espaco_memoria);
    menor = vetor[0];
    fprintf(atual, "%ld\n", menor->valor);
    ultimo = menor->valor;

    while (fscanf(arquivo, "%ld", &numero) != EOF) {
        vetor[0]->valor = numero;  // Atualiza o valor do menor elemento com o novo número lido

        if (numero < ultimo) {
            vetor[0]->marca = 1;  // Se o número for menor que o último, incrementa a marca
        }

        buildHeap(vetor, espaco_memoria);  // Reorganiza o heap após a inserção do novo número

        menor = vetor[0];  // Pega o novo menor valor
        printf("Marca: %d, Nível: %d\n", menor->marca, nivel);
        printf("Numero pego: %ld\n", numero);

        if (todosMarcados(vetor, espaco_memoria) == 1) {  // Troca de arquivo se todos estiverem marcados
            printf("Todos os elementos foram marcados, trocando de arquivo.\n");
            fprintf(atual, "-1\n");  // Escreve delimitador de bloco no arquivo
            atual = (atual == arquivo1) ? arquivo2 : arquivo1;  // Alterna entre os arquivos
            nivel += 1;
            // Reinicializa as marcas
            for (int j = 0; j < espaco_memoria; j++) {
                vetor[j]->marca = 0;
            }
        }

        fprintf(atual, "%ld\n", menor->valor);  // Inserindo o menor valor no arquivo
        ultimo = menor->valor;  // Atualiza 'ultimo' com o valor que acabou de ser inserido
    }

    
    processaRestantes(vetor, arquivo1, arquivo2, nivel, atual); //Processa os ultimos elementos do vetor 

    printf("FINAL\n");

    fclose(arquivo1);
    fclose(arquivo2);
    arquivo1 = fopen("saida1.txt", "r");
    arquivo2 = fopen("saida2.txt", "r");

    intercalacao(arquivo1,arquivo2,nivel); 


















    // Libera a memória alocada para cada elemento
    for (int j = 0; j < i; j++) {
        free(vetor[j]);
    }

    // Libera o vetor de ponteiros
    free(vetor);

    // Fecha os arquivos
    fclose(arquivo);
    fclose(arquivo1);
    fclose(arquivo2);

    return 0;
}