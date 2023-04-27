#ifndef _PQUEUE_H
#define _PQUEUE_H

/* macro */
#define PRIORITY_QUEUE_MAX_SIZE 16
#define NEGATIVE_INT_INF 0x80000000
#define Parent(i) (i % 2?(i >> 1):(i >> 1) -1)

/* structure definition */
typedef struct{
    char val[20];
    int key;
}Data;
typedef struct PriorityQueueDef{
    Data data[PRIORITY_QUEUE_MAX_SIZE];
    int size;
}pQueue;

/* enum definition */
typedef enum PriorityQueueStatus{
    QUEUE_ERROR = 0,
    QUEUE_OK,
    QUEUE_EMPTY,
    QUEUE_FULL,
    QUEUE_OVERFLOW
}pQueueStatus;

/* function reference */
pQueueStatus pQueueInit(pQueue *q);
pQueueStatus pQueueInsert(pQueue *q, char* val, int key);
char* pQueueGet(pQueue *q);
pQueueStatus pQueueExtract(pQueue *q);
pQueueStatus pQueueFix(pQueue *q, int pos, int key);
void MaxHeapify(pQueue *h, int i);
pQueueStatus pQueueStatusGet(pQueue *q);
void PrintQueue(pQueue *q);

#endif