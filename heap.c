#include <stdio.h>
#include "heap.h"


void heapMin(Elemts **vetor,int pos) {
    int min,aux;
    int l = (pos*2)+1;
    int r = (pos*2)+2;

    if(l < espaco_memoria && vetor[l]->marca < vetor[pos]->marca) {
        min = l;
    }else{
        min = pos;
    }

    if(r < espaco_memoria && vetor[r]->marca < vetor[min]->marca) {
        min = r;
    }



    if(l < espaco_memoria && vetor[l]->valor < vetor[pos]->valor && vetor[l]->marca == vetor[pos]->marca) {
        min = l;
    }else{
        min = pos;
    }

    if(r < espaco_memoria && vetor[r]->valor < vetor[min]->valor && vetor[r]->marca == vetor[min]->marca) {
        min = r;
    }


    if(min != pos) {
        aux = vetor[min];
        vetor[min] = vetor[pos];
        vetor[pos] = aux;

        heapMin(vetor,min);
    }
}

void buildHeap(Elemts **vetor, int quant) {
    int i;

    for(i = quant/2;i>=0;i--) {
        heapMin(vetor,i);
    }
}


long int heap_Extract(Elemts **vetor,int quant) {
    long int menor = vetor[0];
    vetor[0] = vetor[quant];
    return menor;
}