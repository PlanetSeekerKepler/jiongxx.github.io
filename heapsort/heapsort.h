#ifndef _HEAPSORT_H
#define _HEAPSORT_H

/* Macro */
#define HEAP_MAX_SIZE 10

/* Structure definition*/
typedef struct HeapDef{
    int data[HEAP_MAX_SIZE];
    int size;
}Heap;

/* Function reference*/
void SwapInt(int *a,int *b);
void HeapInit(Heap *h);
void HeapInsert(Heap *h, int data);
void MaxHeapify(Heap *h, int i);
void PrintHeap(Heap *h);
int str2int(char *str);

#endif