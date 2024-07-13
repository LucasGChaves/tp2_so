#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList *createLinkedList()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL)
    {
        printf("Error allocating memory for the list!\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int isListEmpty(LinkedList *list)
{
    return list->head == NULL;
}

void insertAtBeginning(LinkedList *list, long int data)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        printf("Error allocating memory for the new node!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void insertAtEnd(LinkedList *list, long int data)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (newNode == NULL)
    {
        printf("Error allocating memory for the new node!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (isListEmpty(list))
    {
        list->head = newNode;
    }
    else
    {
        ListNode *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void printList(LinkedList *list)
{
    ListNode *current = list->head;
    printf("List: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

long int removeFromBeginning(LinkedList *list)
{
    if (isListEmpty(list))
    {
        printf("Error: List is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    ListNode *temp = list->head;
    long int data = temp->data;
    list->head = temp->next;
    free(temp);
    list->size--;
    return data;
}

long int removeFromEnd(LinkedList *list)
{
    if (isListEmpty(list))
    {
        printf("Error: List is empty!\n");
        return -1; // Sentinel value to indicate error
    }

    if (list->head->next == NULL)
    {
        // Only one node in the list
        long int data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->size--;
        return data;
    }

    ListNode *current = list->head;
    ListNode *previous = NULL;
    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    long int data = current->data;
    free(current);
    previous->next = NULL;
    list->size--;
    return data;
}

long int findValue(LinkedList *list, long int value)
{
    ListNode *current = list->head;
    long int index = 0;
    while (current != NULL)
    {
        if (current->data == value)
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Value not found
}

void freeLinkedList(LinkedList *list)
{
    ListNode *current = list->head;
    while (current != NULL)
    {
        ListNode *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}