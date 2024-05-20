#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MIN_SIZE 5
struct ElementType {
    int value;
};

struct HeapRecord {
    int length;
    int heap_size;
    struct ElementType* heap_array;
};

typedef struct HeapRecord* heap;

void create_heap(int length)
{
    heap H = malloc(sizeof(struct HeapRecord));
    if(H==NULL)
    {
        printf("Error");
        return;
    }
    H->heap_array = malloc(sizeof(struct ElementType)*(length+1));
    H->length = length;
    H->heap_size = length;
}

void Max_Heapify(heap H, int i)
{
    int l =2*i;
    int r = 2*i+1;
    int largest = i;
    if(l<=H->heap_size && H->heap_array[l].value>H->heap_array[i].value)
    {
        largest = l;
    }
    if(r<=H->heap_size && H->heap_array[r].value <H->heap_array[largest].value)
    {
        largest = r;
    }
    if(largest!=i)
    {
        struct ElementType tmp;
        tmp = H->heap_array[largest];
        H->heap_array[largest] = H->heap_array[i];
        H->heap_array[i]=tmp;
        Max_Heapify(H,largest);
    }
}