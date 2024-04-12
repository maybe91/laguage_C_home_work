#include "plik_naglowkowy.h"
#include "assert.h"


void test_suma_multizbiorow() {
    int multizbior1[] = {1, 2, 3};
    int multizbior2[] = {1, 2, 3};
    int wynik_spodziewany[] = {1, 2, 3, 1, 2, 3};
    int wynik[6];

    suma_multizbiorow(multizbior1, 3, multizbior2, 3, wynik);


    for (int i = 0; i < 6; i++) {
        assert(wynik[i] == wynik_spodziewany[i] && "nie dziala funkcja N1");
    }
}

void test_przeciecie_multizbiorow() {
    int multizbior1[] = {1, 2, 4, 3 };
    int multizbior2[] = {1, 2, 3};
    int wynik_spodziewany[] = {1, 2, 3};
    int wynik[3];

    przeciecie_multizbiorow(multizbior1, 4, multizbior2, 3, wynik);


    for (int i = 0; i < 3; i++) {
        assert(wynik[i] == wynik_spodziewany[i] && "nie dziala funkcja N2");
    }
}

void test_roznica_multizbiorow() {
    int multizbior1[] = {1, 2, 3, 4, 5};
    int multizbior2[] = {1, 3, 2};
    int wynik_spodziewany[] = {4, 5};
    int wynik[2];

    roznica_multizbiorow(multizbior1, 5, multizbior2, 3, wynik);


    for (int i = 0; i < 2; i++) {
        assert(wynik[i] == wynik_spodziewany[i] && "nie dziala funkcja N3");
    }
}

void test_roznica_symetryczna_multizbiorow() {
    int multizbior1[] = {1, 1, 2, 2, 4};
    int multizbior2[] = {1, 1, 5, 2, 2};
    int wynik_spodziewany[] = {4, 5};
    int wynik[2];

    roznica_symertryczna_multizbiorow(multizbior1, 5, multizbior2, 5, wynik);


    for (int i = 0; i < 2; i++) {
        assert(wynik[i] == wynik_spodziewany[i] && "nie dziala funkcja N4");
    }
}

void test_rownosc_multizbiorow() {
    int multizbior1[] = {1, 2, 3};
    int multizbior2[] = {1, 2, 3};
    char wynik_spodziewany = 'T';

    sprawdzanie_rownosci_multizbiorow(multizbior1, 3, multizbior2, 3);

    assert(wynik_spodziewany == 'T' && "nie dziala funkcja N5");
}

void test_sprawdzanie_podzbiorow() {
    int multizbior1[] = {1, 2, 3, 4};
    int multizbior2[] = {1, 2, 3, 5,  4};
    char wynik_spodziewany = 'T';

    sprawdzanie_podzbiorow(multizbior1, 4, multizbior2, 5);

    assert(wynik_spodziewany == 'T' && "nie dziala funkcja N6");

}

