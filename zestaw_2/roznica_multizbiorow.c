#include "plik_naglowkowy.h"


int roznica_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]) {
    int i, j, k;
    k = 0;
    for (i = 0; i < size1; i++) {
        int znaleziono = 0;
        for (j = 0; j < size2; j++) {
            if (multizbior_1[i] == multizbior_2[j]) {
                znaleziono = 1;
                break;
            }
        }
        if (!znaleziono) {
            wynik[k++] = multizbior_1[i];
        }
    }
    return k;
}