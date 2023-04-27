#include<stdio.h>
#include<string.h>
#include "pqueue.h"

/* Internal function */
void SwapData(Data *a, Data *b){
    Data t;
    strcpy(t.val, a->val);
    t.key = a->key;
    strcpy(a->val, b->val);
    a->key = b->key;
    strcpy(b->val, t.val);
    b->key = t.key;
}

/* Global function */
pQueueStatus pQueueInit(pQueue *q){
    q->size = 0;
    return QUEUE_OK;
}

char* pQueueGet(pQueue *q){
    if (pQueueStatusGet(q) != QUEUE_OK)
        return NULL;
    return q->data[0].val;
}
void MaxHeapify(pQueue *h, int i){
    int l = (i << 1) + 1;
    int r = (i + 1) << 1;
    int largest;
    if (l < h->size && h->data[l].key > h->data[i].key)
        largest = l;
    else
        largest = i;
    if (r < h->size && h->data[r].key > h->data[largest].key)
        largest = r;
    if (largest != i){
        SwapData(&h->data[i], &h->data[largest]);
        MaxHeapify(h, largest);
    }
}

pQueueStatus pQueueExtract(pQueue *q){
    if (q->size < 1)
        return QUEUE_EMPTY;
    SwapData(&(q->data[0]), &(q->data[q->size - 1]));
    q->size--;
    MaxHeapify(q, 0);
    return QUEUE_OK;
}

pQueueStatus pQueueFix(pQueue *q, int pos, int key){
    if (pos < 0 || pos > q->size)
        return QUEUE_OVERFLOW;
    if (key <= q->data[pos].key){
        q->data[pos].key = key;
        return QUEUE_OK;
    }
    q->data[pos].key = key;
    int Parentpos = Parent(pos);
    while (pos > 0 && q->data[Parentpos].key < q->data[pos].key ){
        SwapData(&(q->data[Parentpos]), &(q->data[pos]));
        pos = Parent(pos);
        Parentpos = Parent(pos);
    }
    return QUEUE_OK;
}

pQueueStatus pQueueInsert(pQueue *q, char* val, int key){
    if (q->size >= PRIORITY_QUEUE_MAX_SIZE)
        return QUEUE_FULL;
    q->size++;
    strcpy(q->data[q->size - 1].val, val);
    q->data[q->size - 1].key = NEGATIVE_INT_INF;
    pQueueFix(q, q->size - 1, key);
    return QUEUE_OK;
}

pQueueStatus pQueueStatusGet(pQueue *q){
    if (q->size == 0)
        return QUEUE_EMPTY;
    else if (q->size == PRIORITY_QUEUE_MAX_SIZE)
        return QUEUE_FULL;
    else if (q->size > PRIORITY_QUEUE_MAX_SIZE)
        return QUEUE_OVERFLOW;
    return QUEUE_OK;
}

void PrintQueue(pQueue *q){
    if (pQueueStatusGet(q) != QUEUE_OK)
        return ;
    int i;
    for (i = 0; i < q->size; i++){
        printf("%10s    ", q->data[i].val);
        printf("%4d\n", q->data[i].key);
    }
}
