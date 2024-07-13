#ifndef FIFO
#define FIFO
#include "data_structs.h"
typedef struct Node
{
    Page page;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
} Queue;

Queue *createQueue();
int isEmpty(Queue *q);
void enqueue(Queue *q, Page page);
Page dequeue(Queue *q);
void freeQueue(Queue *q);

#endif