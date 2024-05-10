#include <stdio.h>
#include <string.h>

// tail -n liczba
void tail_ostatnie_linie(const char *dane, int n) {
    if (n <= 0) return;

    int liczba_linii = 0;
    const char *pozycja = dane;
    while (*pozycja) {
        if (*pozycja == '\n') {
            liczba_linii++;
        }
        pozycja++;
    }

    int start_linia = liczba_linii - n;
    if (start_linia < 0) start_linia = 0;

    pozycja = dane;
    while (start_linia > 0) {
        if (*pozycja == '\n') {
            start_linia--;
        }
        pozycja++;
    }

    printf("%s", pozycja);
}

// tail +n
void tail_od_linii(const char *dane, int n) {
    if (n <= 0) return;

    int biezaca_linia = 1;
    const char *pozycja = dane;
    while (biezaca_linia < n && *pozycja) {
        if (*pozycja == '\n') {
            biezaca_linia++;
        }
        pozycja++;
    }

    if (*pozycja) {
        printf("%s", pozycja);
    }
}

// tail -c liczba
void tail_ostatnie_znaki(const char *dane, int n) {
    int dlugosc_danych = strlen(dane);
    if (n <= 0 || n >= dlugosc_danych) {
        printf("%s", dane);
        return;
    }

    printf("%s", dane + (dlugosc_danych - n));
}

int main() {
    char komenda[20];

    printf("Podaj komendę (np. \"tail -n 3\", \"tail +2\", \"tail -c 5\"): ");
    fgets(komenda, sizeof(komenda), stdin);
    komenda[strcspn(komenda, "\n")] = '\0';

    printf("Podaj dane:\n");

    char dane[1000];
    int c;
    int i = 0;
    while ((c = getchar()) != EOF && i < 999) {
        dane[i++] = (char) c;
    }
    dane[i] = '\0';

    int parametr;
    if (sscanf(komenda, "tail -n %d", &parametr) == 1) {
        tail_ostatnie_linie(dane, parametr);
    } else if (sscanf(komenda, "tail +%d", &parametr) == 1) {
        tail_od_linii(dane, parametr);
    } else if (sscanf(komenda, "tail -c %d", &parametr) == 1) {
        tail_ostatnie_znaki(dane, parametr);
    } else {
        printf("Nieznana komenda: %s\n", komenda);
        return 1;
    }

    return 0;
}
