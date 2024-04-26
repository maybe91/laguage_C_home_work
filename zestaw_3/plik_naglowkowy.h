#ifndef _myfile_h
#define _myfile_h
#include "stdbool.h"
void build_max_heap(int arr[], int size);
void heapsort(int heap[], int sorted[], int size, bool track);
void max_heapify(int arr[], int i, int size);
void print_state(int step, int heap[], int sorted[], int heap_size, int sorted_size);

#endif
