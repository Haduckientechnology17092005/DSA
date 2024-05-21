#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

heap create_heap(int length) {
    heap H = malloc(sizeof(struct HeapRecord));
    if (H == NULL) {
        printf("Error allocating memory for heap record\n");
        return NULL;
    }
    H->heap_array = malloc(sizeof(struct ElementType) * (length + 1)); // +1 for 1-based indexing
    if (H->heap_array == NULL) {
        printf("Error allocating memory for heap array\n");
        free(H);
        return NULL;
    }
    H->length = length;
    H->heap_size = 0; // Initially, the heap size is 0
    return H;
}

void max_heapify(heap H, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int largest = i;
    if (l <= H->heap_size && H->heap_array[l].value > H->heap_array[i].value) {
        largest = l;
    }
    if (r <= H->heap_size && H->heap_array[r].value > H->heap_array[largest].value) {
        largest = r;
    }
    if (largest != i) {
        struct ElementType tmp = H->heap_array[largest];
        H->heap_array[largest] = H->heap_array[i];
        H->heap_array[i] = tmp;
        max_heapify(H, largest);
    }
}

void build_max_heap(heap H) {
    H->heap_size = H->length;
    for (int i = H->length / 2; i > 0; i--) {
        max_heapify(H, i);
    }
}

void heap_sort(heap H) {
    build_max_heap(H);
    for (int i = H->length; i > 1; i--) {
        struct ElementType tmp = H->heap_array[1];
        H->heap_array[1] = H->heap_array[i];
        H->heap_array[i] = tmp;
        H->heap_size--;
        max_heapify(H, 1);
    }
}

void display(heap H) {
    if (H->heap_size == 0) {
        printf("Heap is empty!\n");
        return;
    }
    printf("The heap is: ");
    for (int i = 1; i <= H->heap_size; i++) {
        printf("%d ", H->heap_array[i].value);
    }
    printf("\n");
}

void display_array(heap H) {
    if (H->length == 0) {
        printf("Heap is empty!\n");
        return;
    }
    printf("The array is: ");
    for (int i = H->length; i >= 1; i--) {
        printf("%d ", H->heap_array[i].value);
    }
    printf("\n");
}

int main() {
    heap H = create_heap(10);
    if (H == NULL) return 1;

    int data[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int data_size = sizeof(data) / sizeof(data[0]);

    for (int i = 0; i < data_size; i++) {
        H->heap_array[i + 1].value = data[i];
    }
    H->length = data_size;
    H->heap_size = data_size;
    for(int i = H->length / 2; i > 0; i--) {
        max_heapify(H, i);
    }
    display(H);
    heap_sort(H);
    display_array(H);

    free(H->heap_array);
    free(H);
    return 0;
}
