#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define heap struct
typedef struct {
    int data[MAX_SIZE];
    int size;
} Heap;

Heap heap = { .size = 0 };

bool heapify(int *source_array, int *target_array, int size);
bool siftup(int index);
bool siftdown(int index);
bool insert(int new_elem);
int extract_max();
void heap_sort(int *array, int size);

bool heapify(int *source_array, int *target_array, int size) {
    if (size > MAX_SIZE) return false;
    for (int i = 0; i < size; i++) {
        insert(source_array[i]);
    }
    for (int i = 0; i < size; i++) {
        target_array[i] = extract_max();
    }
    return true;
}

bool siftup(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap.data[parent] >= heap.data[index]) break;
        int temp = heap.data[parent];
        heap.data[parent] = heap.data[index];
        heap.data[index] = temp;
        index = parent;
    }
    return true;
}

bool siftdown(int index) {
    while (2 * index + 1 < heap.size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        
        if (left < heap.size && heap.data[left] > heap.data[largest]) {
            largest = left;
        }
        if (right < heap.size && heap.data[right] > heap.data[largest]) {
            largest = right;
        }
        if (largest == index) break;
        
        int temp = heap.data[index];
        heap.data[index] = heap.data[largest];
        heap.data[largest] = temp;
        index = largest;
    }
    return true;
}

bool insert(int new_elem) {
    if (heap.size >= MAX_SIZE) return false;
    heap.data[heap.size] = new_elem;
    siftup(heap.size);
    heap.size++;
    return true;
}

int extract_max() {
    if (heap.size == 0) return -1;
    int max_value = heap.data[0];
    heap.data[0] = heap.data[--heap.size];
    siftdown(0);
    return max_value;
}

void heap_sort(int *array, int size) {
    int sorted[size];
    heapify(array, sorted, size);
    for (int i = 0; i < size; i++) {
        array[i] = sorted[i];
    }
}

int main() {
    int arr[] = {4, 10, 3, 5, 1};
    int size = sizeof(arr) / sizeof(arr[0]);

    heap_sort(arr, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
