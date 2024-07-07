#ifndef STACK_H
#define STACK_H

typedef struct StackNode
{
    int data;
    struct StackNode *next;
} StackNode;

typedef struct
{
    StackNode *top;
    int size;
} Stack;

Stack *createStack();
int isEmpty(Stack *stack);
void push(Stack *stack, int data);
int pop(Stack *stack);
int stack_peek(Stack *stack);
void freeStack(Stack *stack);

#endif