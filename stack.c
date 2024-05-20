#include<stdio.h>
#include<stdlib.h>

struct ElementType {
    int value; 
};

struct Node {
    struct ElementType element;
    struct Node *next;
};

typedef struct Node *Stack;
typedef struct Node *StackNode;

Stack create_stack()
{
    Stack S = malloc(sizeof(struct Node));
    S->next = NULL;
    return S;
}

int is_empty(Stack S)
{
    return (S->next == NULL);
}

void make_null(Stack S)
{
    S->next=NULL;
}

void push(Stack S, struct ElementType e){
    if(S==NULL)
    {
        printf("Them phan tu vao danh sach lien ket\n");
    }
    else 
    {
    StackNode N = malloc(sizeof(struct Node));
    if(N == NULL){
        printf("Tran bo nho\n");
        exit(1);
    }
    N->element.value = e.value;
    N->next = S->next;
    S->next = N;
    }
}

void pop(Stack S) 
{
    if(is_empty(S)){
        printf("Ngan xep rong!\n");
        return;
    }
    StackNode N = S->next;
    S->next = N->next;
    free(N);
}

StackNode top(Stack S)
{
    if(is_empty(S)){
        printf("Ngan xep rong!\n");
        return NULL;
    }
    return S->next;
}

void display (Stack S)
{
    if(!is_empty(S))
    {
        printf("Danh sach ngan xep: \n");
    }
    else 
    {
        printf("Ngan xep rong\n");
    }
    StackNode N = S->next;
    while(N!=NULL)
    {
        printf("%d \n",N->element.value);
        N = N->next;
    }
}
int main ()
{
    Stack S = create_stack();
    struct ElementType e1,e2,e3,e4,e5,e6;
    e1.value = 1;
    push(S,e1);
    e2.value = 2;
    push(S,e2);
    e3.value = 3;
    push(S,e3);
    e4.value=5;
    push(S,e4);
    e5.value = 100;
    push(S,e5);
    e6.value = 200;
    push(S,e6);
    display(S);
    return 0;
}