#include "plik_naglowkowy.h"
#include <stdbool.h>

int przeciecie_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]) {
    int k = 0;
    bool multizbior_2_used[size2];
    for (int i = 0; i < size2; ++i) {
        multizbior_2_used[i] = false;
    }

    for (int i = 0; i < size1; ++i) {
        for (int j = 0; j < size2; ++j) {
            if (multizbior_1[i] == multizbior_2[j] && !multizbior_2_used[j]) {
                wynik[k++] = multizbior_1[i];
                multizbior_2_used[j] = true;
                break;
            }
        }
    }
    return k;
}