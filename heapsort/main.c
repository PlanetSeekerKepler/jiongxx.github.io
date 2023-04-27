#include<stdio.h>
#include"heapsort.h"
int main(int argc, char *argv[]){
    Heap h;
    HeapInit(&h);
    int i;
    /* input */
    if (argc <= 1){
        printf("Please input array which to be sorted.\n");
        printf("Example: ./heapsort 9 8 3 4 1 6 \n");
        return 0;
    }
    for (i = 1; i < argc; i++)
        HeapInsert(&h, str2int(argv[i]));
    /* reform max heap */
    for (i = (h.size >> 1) - 1; i >= 0; i--)
        MaxHeapify(&h, i);
    /* heap sort */
    int hsize = h.size;
    for (i = h.size - 1; i >= 1; i--){
        SwapInt(&h.data[0], &h.data[i]);
        h.size--;
        MaxHeapify(&h, 0);
    }
    h.size = hsize;
    PrintHeap(&h);
    return 0;
}
