#ifndef F_HEAP
#define F_HEAP


typedef struct elementos{
    int marca;
    long int valor;
}Elemts;

long int espaco_memoria =  3; //Espaço disponivel na memória interna

void heapMin(Elemts **vetor,int pos);
void buildHeap(Elemts **vetor, int quant);



#endif