#include<stdio.h>
#include<string.h>
#include"heapsort.h"

/* Inner function */

/* Global function */
void SwapInt(int *a,int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
void HeapInit(Heap *h){
    h->size = 0;
}
void HeapInsert(Heap *h, int data){
    h->data[h->size++] = data;
}
void MaxHeapify(Heap *h, int i){
    int l = (i << 1) + 1;
    int r = (i + 1) << 1;
    int largest;
    if (l < h->size && h->data[l] > h->data[i])
        largest = l;
    else
        largest = i;
    if (r < h->size && h->data[r] > h->data[largest])
        largest = r;
    if (largest != i){
        SwapInt(&h->data[i], &h->data[largest]);
        MaxHeapify(h, largest);
    }
}
void PrintHeap(Heap *h){
    int i;
    for (i = 0; i < h->size; i++)
        printf("%4d ", h->data[i]);
    printf("\n");
}
int str2int(char *str){
    int len = strlen(str);
    int i, ret = 0;
    for (i = 0; i < len; i++)
        if (str[i] >= '0' && str[i] <= '9'){
            ret *= 10;
            ret += str[i] - '0';
        }
        else
            return 0;
    return ret;
}