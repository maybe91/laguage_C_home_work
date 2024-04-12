#include "plik_naglowkowy.h"

void bubleSort(int arr[], int n);

char sprawdzanie_podzbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2) {
    int j = 0;

    bubleSort(multizbior_1, size1);
    bubleSort(multizbior_2, size2);

    if(size1 > size2){
        return 'N';
    }

    for (int i = 0; i < size1; i++) {
        if (j >= size2) {
            return 'N';
        }

        if (multizbior_1[i] < multizbior_2[j]){
            return 'N';
        }

        if (multizbior_1[i] == multizbior_2[j]) {
            j++;
            continue;
        }

        if (multizbior_1[i] > multizbior_2[j]) {
            j++;
            continue;
        }
    }

    return 'T';
}

void bubleSort(int arr[], int n) {
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