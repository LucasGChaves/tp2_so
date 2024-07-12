#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode
{
    long int data;
    struct ListNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
    int size;
} LinkedList;

LinkedList *createLinkedList();
int isListEmpty(LinkedList *list);
void insertAtBeginning(LinkedList *list, long int data);
void insertAtEnd(LinkedList *list, long int data);
void printList(LinkedList *list);
int removeFromBeginning(LinkedList *list);
int removeFromEnd(LinkedList *list);
int findValue(LinkedList *list, long int value);
void freeLinkedList(LinkedList *list);

#endif