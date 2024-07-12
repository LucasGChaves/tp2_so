#ifndef QUEUE_H
#define QUEUE_H

typedef struct CircularQueueNode
{
    int data;
    struct CircularQueueNode *next;
} CircularQueueNode;

typedef struct
{
    CircularQueueNode *front;
    CircularQueueNode *rear;
    int size;
} CircularQueue;

CircularQueue *createCircularQueue();
int isCircularQueueEmpty(CircularQueue *q);
void enqueueCircularQueue(CircularQueue *q, int data);
int dequeueCircularQueue(CircularQueue *q);
int circularQueuePeek(CircularQueue *q);
void freeCircularQueue(CircularQueue *q);

#endif