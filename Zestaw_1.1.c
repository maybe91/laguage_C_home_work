#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct odd_even
{
    int odd_num, even_num;
};

typedef struct odd_even Struct;

Struct losowanie(int n)
{
    Struct s;
    int upper_bound = 1000;
    int lower_bound = 1;
    s.odd_num = 0;
    s.even_num = 0;
    int step = 0;

    while (1)
    {
        step = step + 1;
        int num1 = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        int num2 = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        if (num1 % 2 == 0)
        {
            s.even_num = s.even_num + 1;
        }
        else
        {
            s.odd_num = s.odd_num + 1;
        }
        if (num2 % 2 == 0)
        {
            s.even_num = s.even_num + 1;
        }
        else
        {
            s.odd_num = s.odd_num + 1;
        }
        printf("\n num1 = %d and num2 = %d", num1, num2);
        if (num1 - num2 <= 1 && num1 - num2 >= -1)
        {
            break;
        }
        if (step == n)
        {
            break;
        }
    }
    return s;
}

int main() {
    srand(time(NULL));
    Struct result;
    int n;
    printf("\n Write number of steps:");
    scanf("%d", &n);
    result = losowanie(n);
    printf("\nParzystych liczb %d i nieparzystych liczb %d",
           result.even_num, result.odd_num);
    return 0;
}