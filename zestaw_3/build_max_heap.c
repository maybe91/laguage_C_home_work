#include "plik_naglowkowy.h"

void build_max_heap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        max_heapify(arr, i, size);
    }
}