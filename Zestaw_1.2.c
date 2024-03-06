#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//sqrt(0.25-x^2)






int main1() {
    srand(time(NULL));
    int upper_bound = 1000;
    int lower_bound = 1;
    int punktów_w_kwadracie;
    int punkty_w_figurze = 0;
    double x= rand() % (upper_bound - lower_bound + 1) + lower_bound;
    double y = rand() % (upper_bound - lower_bound + 1) + lower_bound;

    scanf("%d", &punktów_w_kwadracie);


    for(int k = 0; k <= punktów_w_kwadracie; k++){
        if(y <= sqrt(0.25 - x*x)){
            punkty_w_figurze += 1;
        }
    }
    printf("pole powierzchni figury: %d", punkty_w_figurze);
    return 0;
}
