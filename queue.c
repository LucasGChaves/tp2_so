#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
    {
        printf("Error allocating memory for the queue!\n");
        exit(1);
    }
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue *q)
{
    return q->front == NULL;
}

void enqueue(Queue *q, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error allocating memory for the new node!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q))
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Error: Queue is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    Node *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL; // Queue is now empty
    }

    free(temp);
    return data;
}

int peek(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Error: Queue is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    return q->front->data;
}

void freeQueue(Queue *q)
{
    while (!isEmpty(q))
    {
        dequeue(q);
    }
    free(q);
}