#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


int szyfrowanie() {
    printf("type the sentence you want to encrypt:\n");
    char str[1000];
    gets(str);

    printf("Enter your keyword:\n");
    char klucz[1000];
    gets(klucz);

    int k = 0;
    int size_str = strlen(str);
    int size_klucz = strlen(klucz);
    int zaszyfrowana_litera;
    char zaszyfrowane_zdanie[1000];
    char space = ' ';

    for (int i = 0; i < size_str; i++) {
        if (k == size_klucz) {
            k = 0;
        }

        char litera = tolower(str[i]);

        char klucz_litera = tolower(klucz[k]);

        if (litera == 32 || klucz_litera == 32) {
            zaszyfrowane_zdanie[i] = space;
            continue;
        }

        zaszyfrowana_litera = (litera - 'a' + klucz_litera - 'a') % 26;
        zaszyfrowana_litera = zaszyfrowana_litera + 'a';

        zaszyfrowane_zdanie[i] = zaszyfrowana_litera;

        k++;
    }

    puts(zaszyfrowane_zdanie);

    return 0;
}
struct odd_even {
    int odd_num, even_num;
};

typedef struct odd_even Struct;

Struct losowanie(int n) {
    Struct s;
    int upper_bound = 1000;
    int lower_bound = 1;
    s.odd_num = 0;
    s.even_num = 0;
    int step = 0;

    while (1) {
        step = step + 1;
        int num1 = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        int num2 = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        if (num1 % 2 == 0) {
            s.even_num = s.even_num + 1;
        } else {
            s.odd_num = s.odd_num + 1;
        }
        if (num2 % 2 == 0) {
            s.even_num = s.even_num + 1;
        } else {
            s.odd_num = s.odd_num + 1;
        }
        printf("\n num1 = %d and num2 = %d", num1, num2);
        if (num1 - num2 <= 1 && num1 - num2 >= -1) {
            break;
        }
        if (step == n) {
            break;
        }
    }
    return s;
}

int zadanie2() {
    srand(time(NULL));

    int punktów_w_kwadracie;
    int punkty_w_figurze1 = 0;
    int punkty_w_figurze2 = 0;
    int punkty_w_figurze3 = 0;
    int punkty_w_figurze4 = 0;
    float kres_górny = 0.5;
    float kres_dolny = -0.5;
    printf("\nWrite number of points: ");
    scanf("%d", &punktów_w_kwadracie);

    for (int k = 0; k < punktów_w_kwadracie; k++) {
        double x = ((float) rand() / RAND_MAX) * kres_dolny;
        double y = ((float) rand() / RAND_MAX) * kres_górny;

        if (y <= sqrt(0.25 - x * x)) {
            punkty_w_figurze1 += 1;
        }
    }

    double pole_kwadratu = kres_górny * kres_górny;
    double stosunek1 = (double) punkty_w_figurze1 / punktów_w_kwadracie;
    double pole_figury1 = stosunek1 * pole_kwadratu;

    for (int k = 0; k < punktów_w_kwadracie; k++) {
        double x = ((float) rand() / RAND_MAX) * kres_górny;
        double y = ((float) rand() / RAND_MAX) * kres_górny;

        if (y <= -sqrt(-x * x + x) + 0.5) {
            punkty_w_figurze2 += 1;
        }
    }

    double stosunek2 = (double) punkty_w_figurze2 / punktów_w_kwadracie;
    double pole_figury2 = stosunek2 * pole_kwadratu;

    for (int k = 0; k < punktów_w_kwadracie; k++) {
        double x = ((float) rand() / RAND_MAX) * kres_dolny;
        double y = ((float) rand() / RAND_MAX) * kres_dolny;

        if (y >= -sqrt((1 - x * x / 0.25) * 0.09)) {
            punkty_w_figurze3 += 1;
        }
    }

    double stosunek3 = (double) punkty_w_figurze3 / punktów_w_kwadracie;
    double pole_figury3 = stosunek3 * pole_kwadratu;

    for (int k = 0; k < punktów_w_kwadracie; k++) {
        double x = ((float) rand() / RAND_MAX) * kres_górny;
        double y = ((float) rand() / RAND_MAX) * kres_dolny;

        if (y >= (1.2 * x * x) -0.3) {
            punkty_w_figurze4 += 1;
        }
    }

    double stosunek4 = (double) punkty_w_figurze4 / punktów_w_kwadracie;
    double pole_figury4 = stosunek4 * pole_kwadratu;

    double pole_figury =  pole_figury1 + pole_figury2 + pole_figury3 + pole_figury4;

    printf("Pole powierzchni figury: %lf\n", pole_figury);
}

int main() {
    szyfrowanie();
    srand(time(NULL));
    Struct result;
    int n;
    printf("\n Write number of steps:");
    scanf("%d", &n);
    result = losowanie(n);
    printf("\nParzystych liczb %d i nieparzystych liczb %d",
           result.even_num, result.odd_num);
    zadanie2();
    return 0;
}