#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} node;

typedef struct node *position;
typedef struct node *list;

int main()
{
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    int i;
    for(i=0;i<10;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}