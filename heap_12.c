#include <stdio.h>
#include <limits.h>

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

Heap create_heap(int length) {
	if (length<MIN_SIZE) {
		printf("The heap's length is at least %d\n",MIN_SIZE);
		return NULL;
	}
	Heap H = malloc(sizeof(struct HeapRecord));
	if (H == NULL) {
		printf("Not enough memory!\n");
		return NULL;
	}
	H->heap_array = malloc(sizeof(struct HeapNode)*(length+1));
	if (H->heap_array == NULL) {
		printf("Not enough memory!\n");
		return NULL;
	}
	H->length = length;
	H->heap_size = length;
	return H;
}

void max_heapify(Heap H, int i) {
	int l = 2*i;
	int r = 2*i+1;
	int largest = i;
	if (l <= H->heap_size && H->heap_array[largest].value < H->heap_array[l].value)
		largest = l;
	if (r <= H->heap_size && H->heap_array[largest].value < H->heap_array[r].value)
		largest = r;
	if (i!=largest) {
		struct HeapNode tmp;
		tmp = H->heap_array[largest];
		H->heap_array[largest] = H->heap_array[i];
		H->heap_array[i] = tmp;
		max_heapify(H,largest);
	}
}

void show_heap(Heap H) {
	if (H->heap_size == 0) {
		printf("The heap is empty!\n");
		return;
	}
	printf("The heap: ");
	for (int i=1;i<=H->heap_size;i++)
		printf("%d ",H->heap_array[i].value);
	printf("\n");
}

void show_heap_array(Heap H) {
	if (H->length == 0) {
		printf("The heap array is empty!\n");
		return;
	}
	printf("The heap array: ");
	for (int i=1;i<=H->length;i++)
		printf("%d ",H->heap_array[i].value);
	printf("\n");
}

void build_max_heap(Heap H) {
	H->heap_size = H->length;
	for (int i = H->length/2;i>0;i--)
		max_heapify(H,i);
}

void heap_sort(Heap H) {
	build_max_heap(H);
	for (int i = H->length;i>1;i--) {
		struct HeapNode tmp = H->heap_array[1];
		H->heap_array[1] = H->heap_array[i];
		H->heap_array[i] = tmp;
		H->heap_size--;
		max_heapify(H,1);
	}
}

struct HeapNode heap_maximum(Heap H) {
	return H->heap_array[1];
}

struct HeapNode extract_max(Heap H) {
	if (H->heap_array<1) {
		printf("The heap is empty!\n");
		struct HeapNode node;
		node.value = EMPTY_VALUE;
		return node;
	}
	struct HeapNode max = H->heap_array[1];
	H->heap_array[1] = H->heap_array[H->heap_size];
	H->heap_size--;
	max_heapify(H,1);
	return max;
}

void heap_increase_key(Heap H, int i, int key) {
	if (key < H->heap_array[i].value) {
		printf("The key must be equal or greater than the node's value!\n");
		return;
	} 
	H->heap_array[i].value = key;
	while (i>1 && H->heap_array[i/2].value < H->heap_array[i].value){
		struct HeapNode tmp = H->heap_array[i];
		H->heap_array[i] = H->heap_array[i/2];
		H->heap_array[i/2] = tmp;
		i = i/2;
	}
}

void max_heap_insert(Heap H, int key) {
	if (H->heap_size < H->length) {
		H->heap_size++;	
		H->heap_array[H->heap_size].value = EMPTY_VALUE;
		heap_increase_key(H,H->heap_size,key);
	} else {
		H->length++;
		H->heap_size++;
		struct HeapNode newNode;
		newNode.value = EMPTY_VALUE;
		H->heap_array[H->length] = newNode;
		heap_increase_key(H,H->heap_size,key);
	}
}

int main() {
	Heap H = create_heap(10);
	int data[] = {23,18,12,14,9,7,10,6,5,8};
	for (int i=0;i<10;i++)
		H->heap_array[i+1].value = data[i];
	show_heap(H);
	max_heap_insert(H,20);
	max_heap_insert(H,17);
	show_heap(H);
	heap_sort(H);
	show_heap_array(H);
	return 0;
}