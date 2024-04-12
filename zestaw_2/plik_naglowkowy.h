#ifndef _myfile_h
#define _myfile_h

void test_sprawdzanie_podzbiorow();
void test_rownosc_multizbiorow();
void test_roznica_symetryczna_multizbiorow();
void test_roznica_multizbiorow();
void test_przeciecie_multizbiorow();
void test_suma_multizbiorow();
void suma_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]);
int przeciecie_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]);
char sprawdzanie_rownosci_multizbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2);
int roznica_multizbiorow(int mmultizbior_1[], int size1, int multizbior_2[], int size2, int wynik[]);
int roznica_symertryczna_multizbiorow(int multizbior[], int size1, int multizbior_2[], int size2, int wynik[]);
char sprawdzanie_podzbiorow(int multizbior_1[], int size1, int multizbior_2[], int size2);

#endif