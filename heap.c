#include <stdio.h>
#include "heap.h"


void heapMin(long int *vetor,int pos,int quant) {
    int min,aux;
    int l = (pos*2)+1;
    int r = (pos*2)+2;

    if(l < quant && vetor[l] < vetor[pos]) {
        min = l;
    }else{
        min = pos;
    }

    if(r < quant && vetor[r] < vetor[min]) {
        min = r;
    }

    if(min != pos) {
        aux = vetor[min];
        vetor[min] = vetor[pos];
        vetor[pos] = aux;

        heapMin(vetor,min,quant);
    }
}

void buildHeap(long int *vetor, int quant) {
    int i;

    for(i = quant/2;i>=0;i--) {
        heapMin(vetor,i,quant);
    }
}


long int heap_Extract(long int *vetor,int quant) {
    long int menor = vetor[0];
    vetor[0] = vetor[quant];
    return menor;
}