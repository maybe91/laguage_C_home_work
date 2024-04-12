#include "plik_naglowkowy.h"

void suma_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]) {
    int i;
    for (i = 0; i < size1; i++) {
        wynik[i] = multizbior_1[i];
    }
    for (i = 0; i < size2; i++) {
        wynik[size1 + i] = multizbior_2[i];
    }
}