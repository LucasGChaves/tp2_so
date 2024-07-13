#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

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

void enqueue(Queue *q, Page page)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Error allocating memory for the new node!\n");
        exit(1);
    }
    newNode->page = page;
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

Page dequeue(Queue *q)
{
    Page emptyPage;
    emptyPage.id = -1;
    if (isEmpty(q))
    {
        printf("Error: Queue is empty!\n");
        return emptyPage; // Sentinel value to indicate error
    }
    Node *temp = q->front;
    Page page = temp->page;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL; // Queue is now empty
    }

    free(temp);
    return page;
}

void freeQueue(Queue *q)
{
    while (!isEmpty(q))
    {
        dequeue(q);
    }
    free(q);
}