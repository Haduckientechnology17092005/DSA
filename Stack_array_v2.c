#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MIN_CAPACITY 5
#define empty_pos -1

struct ElementType {
    int value;
};

struct StackRecord {
    unsigned int capacity;
    int tos;
    struct ElementType *stack_array;
};

typedef struct StackRecord *Stack;

Stack create_stack (unsigned int capacity)
{
    if(capacity < MIN_CAPACITY)
    {
        printf("The Stack's capacity is at least %d\n", MIN_CAPACITY);
        return NULL;
    }
    Stack S;
    S = malloc(sizeof(struct StackRecord));
    if(S==NULL)
    {
        printf("Out of space\n");
        return NULL;
    }
    S->stack_array = malloc(sizeof(struct ElementType)*capacity);
    if(S->stack_array == NULL)
    {
        printf("Out of space\n");
        return NULL;
    }
    S->capacity = capacity;
    S->tos = empty_pos;
    return S;
}

int is_empty(Stack S)
{
    return (S->tos == empty_pos);
}

int is_full(Stack S)
{
    return (S->tos == S->capacity - 1);
}

void make_null(Stack S)
{
    S->tos = empty_pos;
}

void dispose_stack(Stack S)
{
    free(S->stack_array);
    free(S);
}

void push (Stack S, struct ElementType e)
{
    if(is_full(S))
    {
        printf("The Stack is full\n");
        return;
    }
    else 
    {
        S->stack_array[++S->tos] = e;
    }
}

struct ElementType *pop (Stack S)
{
    if(is_empty(S))
    {
        printf("The Stack is empty\n");
        return NULL;
    }
    else
    {
        return &(S->stack_array[S->tos--]);
    }
}

struct ElementType *top(Stack S)
{
    if(is_empty(S))
    {
        printf("The Stack is empty\n");
        return NULL;
    }
    else
    {
        return &(S->stack_array[S->tos]);
    }
}