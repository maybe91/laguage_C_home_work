#include <stdbool.h>
#include "plik_naglowkowy.h"


void heapsort(int heap[], int sorted[], int size, bool track) {
    build_max_heap(heap, size);
    int sorted_size = 0;

    if (track) {
        print_state(1, heap, sorted, size, sorted_size);
    }

    for (int i = size - 1; i >= 0; i--) {
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;

        sorted[sorted_size++] = heap[i];
        heap[i] = -1;

        max_heapify(heap, 0, i);

        if (track) {
            print_state(size - i + 1, heap, sorted, i, sorted_size);
        }
    }
}