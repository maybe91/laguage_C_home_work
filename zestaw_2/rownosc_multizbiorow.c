#include "plik_naglowkowy.h"

void bubbleSort(int arr[], int n);

char sprawdzanie_rownosci_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2) {
    if (size1 != size2) {
        return 0;
    }


    bubbleSort(multizbior_1, size1);
    bubbleSort(multizbior_2, size2);

    for (int i = 0; i < size1; i++) {
        if (multizbior_1[i] != multizbior_2[i]) {
            return 'N';
        }
    }

    return 'T';
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}