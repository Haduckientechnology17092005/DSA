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

Stack create_stack(unsigned int capacity)
{
    if(capacity < MIN_CAPACITY)
    {
        printf("The Stack's capacity is at least %d\n", MIN_CAPACITY);
        return NULL;
    }
    Stack S = malloc(sizeof(struct StackRecord));
    if(S == NULL)
    {
        printf("Out of space\n");
    }
    S->stack_array = malloc(capacity * sizeof(struct ElementType));
    if(S->stack_array == NULL)
    {
        printf("Out of space\n");
        free(S);
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

void dispose(Stack S)
{
    if(S != NULL)
    {
        free(S->stack_array);
        free(S);
    }
}

void push(Stack S, struct ElementType e)
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

struct ElementType *pop(Stack S)
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

void display(Stack S)
{
    if(is_empty(S))
    {
        printf("The Stack is empty\n");
        return;
    }
    else
    {
        int i;
        for(i = S->tos; i >= 0; i--)
        {
            printf("%d\n", S->stack_array[i].value);
        }
    }
}

int main()
{
    Stack S = create_stack(5);
    struct ElementType e1, e2, e3, e4, e5;
    e1.value = 1;
    push(S, e1);
    e2.value = 2;
    push(S, e2);
    e3.value = 3;
    push(S, e3);
    e4.value = 4;
    push(S, e4);
    e5.value = 5;
    push(S, e5);
    display(S);
    struct ElementType *p;
    p = pop(S);
    display(S);
    p = top(S);
    if (p != NULL)
        printf("Top element: %d\n", p->value);
    else
        printf("No top element\n");
    return 0;
}
