#include <stdio.h>
#include <stdlib.h>
#include "plik_naglowkowy.h"

#define MAX_SIZE 100
#define RESULT_SIZE 2 * MAX_SIZE

int main() {
    test_sprawdzanie_podzbiorow();
    test_rownosc_multizbiorow();
    test_roznica_symetryczna_multizbiorow();
    test_roznica_multizbiorow();
    test_przeciecie_multizbiorow();
    test_suma_multizbiorow();
    system("chcp 65001");

    int operation_number;
    int multizbior_1[MAX_SIZE], multizbior_2[MAX_SIZE], wynik[RESULT_SIZE];
    int size1 = 0, size2 = 0, wynik_size = 0;
    char rownosc;

    while (1) {
        printf("Wprowadź numer transakcji i dane: ");
        if (scanf("%d", &operation_number) == EOF) {
            fprintf(stderr, "Błąd: nie można wczytać numeru transakcji\n");
            exit(EXIT_FAILURE);
        }

        char c;
        while ((c = getchar()) != ':')
            continue;

        while (scanf("%d", &multizbior_1[size1]) == 1) {
            size1++;
            if ((c = getchar()) == ':')
                break;
        }

        while (scanf("%d", &multizbior_2[size2]) == 1) {
            size2++;
            if ((c = getchar()) == EOF || c == '\n')
                break;
        }

        switch (operation_number) {
            case 1:
                suma_multizbiorow(multizbior_1, size1, multizbior_2, size2, wynik);
                wynik_size = size1 + size2;
                break;

            case 2:
                wynik_size = przeciecie_multizbiorow(multizbior_1, size1, multizbior_2, size2, wynik);
                break;

            case 3:
                wynik_size = roznica_multizbiorow(multizbior_1, size1, multizbior_2, size2, wynik);
                break;

            case 4:
                wynik_size = roznica_symertryczna_multizbiorow(multizbior_1, size1, multizbior_2, size2, wynik);
                break;

            case 5:
                rownosc = sprawdzanie_rownosci_multizbiorow(multizbior_1, size1, multizbior_2, size2);
                break;

            case 6:
                rownosc = sprawdzanie_podzbiorow(multizbior_1, size1, multizbior_2, size2);
                break;

            default:
                fprintf(stderr, "Błąd: niepoprawny numer transakcji: %d\n", operation_number);
                exit(EXIT_FAILURE);
                break;
        }

        if (operation_number != 5 && operation_number != 6) {
            printf("Wynik: ");
            for (int i = 0; i < wynik_size; i++) {
                printf("%d ", wynik[i]);
            }
            printf("\n");
        } else {
            printf("Wynik: %c\n", rownosc);
        }

        size1 = 0;
        size2 = 0;
        wynik_size = 0;
    }

    printf("Program zakończony\n");
    return 0;
}




// gcc -o program zestaw_2/zestaw_2.c  zestaw_2/suma_multizbiorow.c zestaw_2/przeciecie_multizbiorow.c zestaw_2/roznica_multizbiorow.c zestaw_2/roznica_symetryczna_multizbiorow.c zestaw_2/rownosc_multizbiorow.c zestaw_2/sprawdzanie_podzbiorow.c zestaw_2/testy.c
// ./program