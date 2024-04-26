#include <stdio.h>
#include "plik_naglowkowy.h"


void print_state(int step, int heap[], int sorted[], int heap_size, int sorted_size) {
    printf("Krok %d ", step);


    for (int i = 0; i < heap_size; i++) {
        printf("%2d ", heap[i]);
    }




    for (int i = 0; i < sorted_size; i++) {
        printf("   ");
    }

    for (int i = 0; i < sorted_size; i++) {
        printf("%2d ", sorted[i]);
    }

    printf("\n");
}