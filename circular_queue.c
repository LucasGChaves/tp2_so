#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"

CircularQueue *createCircularQueue()
{
    CircularQueue *q = (CircularQueue *)malloc(sizeof(CircularQueue));
    if (q == NULL)
    {
        printf("Error allocating memory for the queue!\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

int isCircularQueueEmpty(CircularQueue *q)
{
    return q->front == NULL;
}

void enqueueCircularQueue(CircularQueue *q, int data)
{
    CircularQueueNode *newCircularQueueNode = (CircularQueueNode *)malloc(sizeof(CircularQueueNode));
    if (newCircularQueueNode == NULL)
    {
        printf("Error allocating memory for the new CircularQueuenode!\n");
        exit(1);
    }
    newCircularQueueNode->data = data;
    newCircularQueueNode->next = NULL;

    if (isQueueEmpty(q))
    {
        q->front = q->rear = newCircularQueueNode;
    }
    else
    {
        q->rear->next = newCircularQueueNode;
        q->rear = newCircularQueueNode;
    }
    q->rear->next = q->front; // Maintain circularity
    q->size++;
}

int dequeueCircularQueue(CircularQueue *q)
{
    if (isQueueEmpty(q))
    {
        printf("Error: Queue is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    int data;
    if (q->front == q->rear)
    { // Only one CircularQueuenode
        data = q->front->data;
        free(q->front);
        q->front = q->rear = NULL;
    }
    else
    {
        CircularQueueNode *temp = q->front;
        data = temp->data;
        q->front = q->front->next;
        q->rear->next = q->front; // Maintain circularity
        free(temp);
    }
    q->size--;
    return data;
}

int circularQueuePeek(CircularQueue *q)
{
    if (isQueueEmpty(q))
    {
        printf("Error: Queue is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    return q->front->data;
}

void freeCircularQueue(CircularQueue *q)
{
    CircularQueueNode *temp;
    while (q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
        if (q->front == q->rear->next)
        { // Last CircularQueuenode
            free(q->front);
            break;
        }
    }
    free(q);
}