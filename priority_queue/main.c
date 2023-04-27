#include "pqueue.h"

int main(int argc, char* argv[]){
    pQueue q;
    pQueueInit(&q);
    pQueueInsert(&q, "Alice", 5);
    pQueueInsert(&q, "Bob", 15);
    pQueueInsert(&q, "Cindy", 3);
    pQueueInsert(&q, "Dandy", 7);
    PrintQueue(&q);
    pQueueExtract(&q);
    PrintQueue(&q);
    pQueueExtract(&q);
    PrintQueue(&q);
    pQueueExtract(&q);
    PrintQueue(&q);
}




