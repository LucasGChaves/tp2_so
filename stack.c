#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Error allocating memory for the stack!\n");
        exit(1);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int isEmpty(Stack *stack)
{
    return stack->top == NULL;
}

void push(Stack *stack, int data)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        printf("Error allocating memory for the new node!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    StackNode *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

int stack_peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty!\n");
        return -1; // Sentinel value to indicate error
    }
    return stack->top->data;
}

void freeStack(Stack *stack)
{
    StackNode *temp;
    while (stack->top != NULL)
    {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}