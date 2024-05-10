#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <regex.h>


typedef struct {
    char *linia;  // Pełna linia
    double klucz_numeryczny; // Klucz do sortowania numerycznego
    char *klucz_tekstowy; // Klucz do sortowania według tekstu/kolumny
} sortowalna_linia;


int porownaj_numerycznie(const void *a, const void *b) {
    const sortowalna_linia *linia1 = (const sortowalna_linia *)a;
    const sortowalna_linia *linia2 = (const sortowalna_linia *)b;
    if (linia1->klucz_numeryczny < linia2->klucz_numeryczny) return -1;
    if (linia1->klucz_numeryczny > linia2->klucz_numeryczny) return 1;
    return 0;
}


int porownaj_tekstowo(const void *a, const void *b) {
    const sortowalna_linia *linia1 = (const sortowalna_linia *)a;
    const sortowalna_linia *linia2 = (const sortowalna_linia *)b;
    return strcmp(linia1->klucz_tekstowy, linia2->klucz_tekstowy);
}


char *wydobadz_kolumne(const char *tekst, int kolumna) {
    regex_t regex;
    regmatch_t dopasowania[10];
    int wynik;


    wynik = regcomp(&regex, "^([^\t ]+)(\t| )?", REG_EXTENDED);

    if (wynik) {
        fprintf(stderr, "Błąd kompilacji wyrażenia regularnego\n");
        return NULL;
    }

    const char *wsk = tekst;
    int biezaca_kolumna = 0;

    while (*wsk && biezaca_kolumna <= kolumna) {
        wynik = regexec(&regex, wsk, 10, dopasowania, 0);
        if (wynik == REG_NOMATCH) {
            break;
        }

        if (biezaca_kolumna == kolumna) {
            int dlugosc = dopasowania[0].rm_eo - dopasowania[0].rm_so;
            char *wynik = (char *)malloc(dlugosc + 1);
            if (!wynik) {
                fprintf(stderr, "Błąd alokacji pamięci\n");
                return NULL;
            }

            strncpy(wynik, wsk + dopasowania[0].rm_so, dlugosc);
            wynik[dlugosc] = '\0';
            regfree(&regex);
            return wynik;
        }

        wsk += dopasowania[0].rm_eo;
        biezaca_kolumna++;
    }

    regfree(&regex);
    return strdup("");
}


void sortuj_linie(char **linie, int liczba_linii, int kolumna, int sortowanie_numeryczne) {
    sortowalna_linia *sortowalne_linie = (sortowalna_linia *)malloc(sizeof(sortowalna_linia) * liczba_linii);
    if (!sortowalne_linie) {
        fprintf(stderr, "Błąd alokacji pamięci\n");
        return;
    }

    for (int i = 0; i < liczba_linii; i++) {
        sortowalne_linie[i].linia = linie[i];
        sortowalne_linie[i].klucz_tekstowy = wydobadz_kolumne(linie[i], kolumna);

        if (sortowanie_numeryczne) {
            sortowalne_linie[i].klucz_numeryczny = atof(sortowalne_linie[i].klucz_tekstowy);
        }
    }

    if (sortowanie_numeryczne) {
        qsort(sortowalne_linie, liczba_linii, sizeof(sortowalna_linia), porownaj_numerycznie);
    } else {
        qsort(sortowalne_linie, liczba_linii, sizeof(sortowalna_linia), porownaj_tekstowo);
    }

    for (int i = 0; i < liczba_linii; i++) {
        printf("%s", sortowalne_linie[i].linia);
        free(sortowalne_linie[i].klucz_tekstowy);
    }

    free(sortowalne_linie);
}

void test_sort_numeric() {
    char *linie[] = {
            "3\tApple\n",
            "1\tBanana\n",
            "2\tCherry\n",
            "4\tDate\n",
    };
    int liczba_linii = 4;
    int kolumna = 0;
    int sortowanie_numeryczne = 1;

    printf("Test sort -n: spodziewane: 1, 2, 3, 4\n");
    sortuj_linie(linie, liczba_linii, kolumna, sortowanie_numeryczne);

    // Sprawdzenie poprawnej kolejności
    assert(strcmp(linie[0], "1\tBanana\n") == 0);
    assert(strcmp(linie[1], "2\tCherry\n") == 0);
    assert(strcmp(linie[2], "3\tApple\n") == 0);
    assert(strcmp(linie[3], "4\tDate\n") == 0);

    printf("Test sort -n: PASSED\n");
}

void test_sort_textual() {
    char *linie[] = {
            "Banana\t1\n",
            "Cherry\t3\n",
            "Apple\t2\n",
            "Date\t4\n",
    };
    int liczba_linii = 4;
    int kolumna = 0;
    int sortowanie_numeryczne = 0;

    printf("Test sort tekstowy: spodziewane: Apple, Banana, Cherry, Date\n");
    sortuj_linie(linie, liczba_linii, kolumna, sortowanie_numeryczne);

    // Sprawdzenie poprawnej kolejności
    assert(strcmp(linie[0], "Apple\t2\n") == 0);
    assert(strcmp(linie[1], "Banana\t1\n") == 0);
    assert(strcmp(linie[2], "Cherry\t3\n") == 0);
    assert(strcmp(linie[3], "Date\t4\n") == 0);

    printf("Test sort tekstowy: PASSED\n");
}


int main() {

    test_sort_numeric();
    test_sort_textual();


    char komenda[20];

    printf("Podaj komendę (np. \"sort -n\", \"sort -k 2\", \"sort -n -k 2\"): ");
    fgets(komenda, sizeof(komenda), stdin);
    komenda[strcspn(komenda, "\n")] = '\0';

    printf("Podaj dane (Ctrl+D, aby zakończyć wprowadzanie):\n");

    char **linie = (char **)malloc(sizeof(char *) * 100);
    if (!linie) {
        fprintf(stderr, "Błąd alokacji pamięci\n");
        return 1;
    }

    int liczba_linii = 0;
    char bufor[200];
    while (fgets(bufor, sizeof(bufor), stdin)) {
        linie[liczba_linii] = strdup(bufor);
        if (!linie[liczba_linii]) {
            fprintf(stderr, "Błąd kopiowania linii\n");
            return 1;
        }
        liczba_linii++;
    }

    int sortowanie_numeryczne = 0;
    int kolumna = 0;

    if (strstr(komenda, "sort -n")) {
        sortowanie_numeryczne = 1;
    }

    if (sscanf(komenda, "sort -k %d", &kolumna) == 1) {
        kolumna--;
    }

    sortuj_linie(linie, liczba_linii, kolumna, sortowanie_numeryczne);

    for (int i = 0; i < liczba_linii; i++) {
        free(linie[i]);
    }
    free(linie);

    return 0;
}