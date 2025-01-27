#ifndef SECOND_CHANCE_H
#define SECOND_CHANCE_H
#include "data_structs.h"

typedef struct SecondChanceQueueNode
{
    Page page;
    struct SecondChanceQueueNode *next;
    int referenceBit;
} SecondChanceQueueNode;

typedef struct
{
    SecondChanceQueueNode *front;
    SecondChanceQueueNode *rear;
    int size;
} SecondChanceQueue;

SecondChanceQueue *createSecondChanceQueue();
int isSecondChanceQueueEmpty(SecondChanceQueue *q);
void enqueueSecondChanceQueue(SecondChanceQueue *q, Page page);
Page dequeueSecondChanceQueue(SecondChanceQueue *q);
void freeSecondChanceQueue(SecondChanceQueue *q);

#endif