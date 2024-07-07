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
} Queue;

Queue *createQueue();
int isQueueEmpty(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);
int queue_peek(Queue *q);
void freeQueue(Queue *q);

#endif