#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MIN_SIZE 5
#define EMPTY_VALUE -INT_MAX

struct HeapNode {
    int value;
};

struct HeapRecord {
    int length;
    int heap_size;
    struct HeapNode *heap_array;
};

typedef struct HeapRecord *Heap;

//Tao 1 Heap
Heap create_heap(int length){
    //Test length
    if(length < MIN_SIZE)
    {
        printf("MIN_SIZE >= 5");
        return NULL;
    }
    Heap H = malloc(sizeof(struct HeapRecord));
    if(H==NULL)
    {
        printf("Out of space");
        return NULL;
    }
    H->heap_array = malloc(sizeof(struct HeapNode)*(length+1));
    if(H->heap_array==NULL)
    {
        printf("Out of space");
        free(H);
        return NULL;
    }
    H->length = length;
    H->heap_size = length;
    return H;
}

//chat thanh dong
void max_heapify(Heap H, int i)
{
    int l = 2*i;
    int r = 2*i+1;
    int largest = i;
    if(l <= H->heap_size && H->heap_array[l].value > H->heap_array[largest].value)
    {
        largest = l;
    }
    if(r <= H->heap_size && H->heap_array[r].value > H->heap_array[largest].value)
    {
        largest = r;
    }
    if(largest != i)
    {
        struct HeapNode tmp;
        tmp = H->heap_array[largest];
        H->heap_array[largest] = H->heap_array[i];
        H->heap_array[i] = tmp;
        max_heapify(H, largest);
    }
}

// chat thanh dong min
void min_heapify(Heap H, int i)
{
    int l = 2*i;
    int r = 2*i + 1;
    int smallest = i;
    if(l <= H->heap_size && H->heap_array[l].value < H->heap_array[smallest].value)
        smallest = l;
    if(r <= H->heap_size && H->heap_array[r].value < H->heap_array[smallest].value)
        smallest = r;
    if(i!=smallest)
    {
        struct HeapNode tmp;
        tmp = H->heap_array[smallest];
        H->heap_array[smallest] = H->heap_array[i];
        H->heap_array[i] = tmp;
        min_heapify(H, smallest);
    }
}

//Dung dong lon nhat
void build_max_heap(Heap H)
{
    H->heap_size = H->length;
    for(int i = H->length/2; i>0; i--)
    {
        max_heapify(H,i);
    }
}

//Dung dong nho nhat
void build_min_heap(Heap H)
{
    H->heap_size = H->length;
    for(int i = H->length/2; i>0; i--)
    {
        min_heapify(H,i);
    }
}

//Sap xep dong
void heap_sort_max(Heap H)
{
    build_max_heap(H);
    for(int i = H->length; i>1; i--)
    {
        struct HeapNode tmp;
        tmp = H->heap_array[1];
        H->heap_array[1] = H->heap_array[i];
        H->heap_array[i] = tmp;
        H->heap_size--;
        max_heapify(H,1);
    }
}

//Sap xep dong tu nho den lon
void heap_sort_min(Heap H)
{
    build_min_heap(H);
    for(int i = H->length; i>1; i--)
    {
        struct HeapNode tmp;
        tmp = H->heap_array[1];
        H->heap_array[1] = H->heap_array[i];
        H->heap_array[i] = tmp;
        H->heap_size--;
        min_heapify(H,1);
    }
}

struct HeapNode heap_maximum(Heap H)
{
    return H->heap_array[1];
}

struct HeapNode heap_extract_max(Heap H)
{
    if(H->heap_size < 1)
    {
        printf("Heap inderflow");
        struct HeapNode node;
        node.value = EMPTY_VALUE;
        return node;
    }
    struct HeapNode max;
    max = H->heap_array[1];
    H->heap_array[1] = H->heap_array[H->heap_size];
    H->heap_size--;
    max_heapify(H,1);
    return max;
}

void heap_increase_key(Heap H, int i, int key)
{
    if(key < H->heap_array[i].value)
    {
        printf("New key is smaller than current key");
        struct HeapNode node;
        node.value = EMPTY_VALUE;
        return node;
    }
    H->heap_array[i].value = key;
    while(i > 1 && H->heap_array[i/2].value < H->heap_array[i].value)
    {
        struct HeapNode tmp;
        tmp = H->heap_array[i];
        H->heap_array[i] = H->heap_array[i/2];
        H->heap_array[i/2] = tmp;
        i = i/2;
    }
}

//chen vao lon nhat
void max_heap_insert(Heap H, int key)
{
    if(H->heap_size < H->length)
    {
        H->heap_size++;
        H->heap_array[H->heap_size].value = EMPTY_VALUE;
        heap_increase_key(H, H->heap_size, key);
    } 
    else
    {
        H->length++;
        H->heap_size++;
        struct HeapNode node;
        node.value = EMPTY_VALUE;
        H->heap_array[H->length] = node;
        heap_increase_key(H, H->heap_size, key);
    }
}

void show_heap(Heap H)
{
    printf("The Heap is: ");
    for(int i = 1; i<=H->heap_size; i++)
    {
        printf("%d ", H->heap_array[i].value);
    }
    printf("\n");
}

void show_heap_array(Heap H)
{
    printf("The heap array is: ");
    for(int i = 1; i <= H->length; i++)
    {
        printf("%d ", H->heap_array[i].value);
    }
    printf("\n");
}

int main(){
    Heap H = create_heap(10);
    int data[] = {23,18,12,14,9,7,10,6,5,8};
    for(int i = 0; i< 10; i++){
        H->heap_array[i+1].value = data[i];
    }
    show_heap(H);
    max_heap_insert(H,19);
    max_heap_insert(H,20);
    show_heap(H);
    heap_sort_max(H);
    show_heap_array(H);
    heap_sort_min(H);
    show_heap_array(H);
    return 0;
}