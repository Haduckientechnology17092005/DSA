#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

struct ElementType 
{
    unsigned long ID;
    char *name;
};

struct Node
{
    struct ElementType value;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node *List;
typedef struct Node *Position;

Position insert(List *pL, Position p, struct ElementType e)
{
    Position newItem = malloc(sizeof(struct Node));
    newItem -> value = e;
    newItem -> next = p -> next;
    newItem -> prev = p;
    p -> next = newItem;
    if(newItem -> next != NULL)
    {
        newItem -> next -> prev = newItem;
    }
    return newItem;
}

List createList()
{
    List headerNode = malloc(sizeof(struct Node));
    headerNode -> next = NULL;
    return headerNode;
}

void display(List pL)
{
    pL = pL->next;
    int count = 1;
    while(pL != NULL)
    {
        printf("%d. %lu %s\n",count,pL->value.ID,pL->value.name);
        pL = pL->next;
        count++;
    }
}

void delete(Position p)
{
    p->prev->next = p->next;
    if(p->next != NULL)
    {
        p->next->prev = p->prev;
    }
}

int main()
{
    List pL = createList();
    struct ElementType e1,e2,e3,e4;
    e1.ID = 1; e1.name = "e1";
    e2.ID = 2; e2.name = "e2";
    e3.ID = 3; e3.name = "e3";
    e4.ID = 4; e4.name = "e4";
    Position p1,p2,p3,p4;
    p1=insert(&pL,pL,e1);
    p2=insert(&pL,p1,e2);
    p3=insert(&pL,p2,e3);
    p4=insert(&pL,p3,e4);
    display(pL);
    delete(p1);
    display(pL);
}