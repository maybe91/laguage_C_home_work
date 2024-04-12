#include "plik_naglowkowy.h"

int roznica_symertryczna_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]) {
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


    for (i = 0; i < size2; i++) {
        int znaleziono = 0;

        for (j = 0; j < size1; j++) {
            if (multizbior_2[i] == multizbior_1[j]) {
                znaleziono = 1;
                break;
            }
        }

        if (!znaleziono) {
            wynik[k++] = multizbior_2[i];
        }
    }

    return k;
}