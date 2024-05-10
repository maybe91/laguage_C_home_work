#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <regex.h>



void test_grep_count() {
    char komenda[] = "grep -c word";
    char dane[] = "This is a word in the text. Another word here.";

    int ilosc = policzone_dane(dane, "word");
    assert(ilosc == 2);

    printf("Test grep -c: PASSED\n");
}

void test_grep_case_insensitive() {
    char komenda[] = "grep -i Word";
    char dane[] = "This is a word in the text. Another WORD here.";

    printf("Test grep -i: Expected output: word\nWORD\n");
    wypisane_dane(dane, "word");
    printf("Test grep -i: PASSED\n");
}

//grep -c
int count_match(const char *str, const char *wzorzec) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    int licznik = 0;

    reti = regcomp(&regex, wzorzec, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Nie można skompilować wyrażения regularnego\n");
        return -1;
    }

    regmatch_t dopasowanie;
    while (1) {
        reti = regexec(&regex, str, 1, &dopasowanie, 0);
        if (reti == REG_NOMATCH) {
            break;
        }
        if (reti) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Dopasowanie wyrażenia regularnego nie powiodło się: %s\n", msgbuf);
            return -1;
        }
        licznik++;
        str += dopasowanie.rm_eo;
    }

    regfree(&regex);
    return licznik;
}

//grep -w

void print_match(const char *str, const char *wzorzec) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, wzorzec, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Nie można skompilować wyrażenia regularnego\n");
        return;
    }

    regmatch_t dopasowanie;
    while (1) {
        reti = regexec(&regex, str, 1, &dopasowanie, 0);
        if (reti == REG_NOMATCH) {
            break;
        }
        if (reti) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Dopasowanie wyrażenia regularnego nie powiodło się: %s\n", msgbuf);
            return;
        }
        printf("%.*s\n", (int) (dopasowanie.rm_eo - dopasowanie.rm_so), str + dopasowanie.rm_so);
        str += dopasowanie.rm_eo;
    }

    regfree(&regex);
}

//grep -i

void print_matches(const char *str, const char *wzorzec) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    reti = regcomp(&regex, wzorzec, REG_ICASE);
    if (reti) {
        fprintf(stderr, "Nie można skompilować wyrażения regularnego\n");
        return;
    }

    regmatch_t dopasowanie;
    while (1) {
        reti = regexec(&regex, str, 1, &dopasowanie, 0);
        if (reti == REG_NOMATCH) {
            break;
        }
        if (reti) {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Dopasowanie wyrażenia regularnego nie powiodło się: %s\n", msgbuf);
            return;
        }
        printf("%.*s\n", (int) (dopasowanie.rm_eo - dopasowanie.rm_so), str + dopasowanie.rm_so);
        str += dopasowanie.rm_eo;
    }

    regfree(&regex);
}

//grep -n

void print_match_with_line_number(const char *str,const char *wzorzec){
   regex_t regex;
   int reti;
   char msgbuf[100];
   int licznik = 1;

   reti = regcomp(&regex,wzorzec ,REG_EXTENDED);
   if(reti){
       fprintf(stderr,"Nie można skompilować wyrażenia regularnego\n");
       return ;
   }

   regmatch_t dopasowanie ;
   while(1){
       reti = regexec(&regex,str ,1,&dopasowanie ,0);
       if(reti == REG_NOMATCH){
           break ;
       }
       if(reti){
           regerror(reti,&regex,msgbuf,sizeof(msgbuf));
           fprintf(stderr,"Dopasowanie wyrażenia regularnego nie powiodło się: %s\n",msgbuf);
           return ;
       }
       printf("%d:%.*s\n",licznik++,(int)(dopasowanie.rm_eo - dopasowanie.rm_so),str + dopasowanie.rm_so);
       str += dopasowanie.rm_eo;
   }

   regfree(&regex);
}

int main() {

    test_grep_count();
    test_grep_case_insensitive();


    char polecenie[20];

    printf("Podaj komendę (np. \"grep -c, -w, -n, -i szukane_slowo\"): ");
    fgets(polecenie, 20, stdin);
    polecenie[strcspn(polecenie, "\n")] = '\0';

    printf("Podaj dane:\n");

    char dane[1000];
    int c;
    int i = 0;
    while ((c = getchar()) != EOF && i < 999) {
        dane[i++] = (char) c;
    }
    dane[i] = '\0';


    char wzor[100];
    if (strstr(polecenie, "grep -c") == polecenie) {
        if (sscanf(polecenie + strlen("grep -c "), "%s", wzor) != 1) {
            printf("Nieprawidłowe argumenty dla polecenia grep\n");
            return 1;
        }
        int licznik = count_match(dane, wzor);
        if (licznik >= 0) {
            printf("%d\n", licznik);
        }
    } else if (strstr(polecenie, "grep -w") == polecenie) {
        if (sscanf(polecenie + strlen("grep -w "), "%s", wzor) != 1) {
            printf("Nieprawidłowe argumenty dla polecenia grep\n");
            return 1;
        }
        char wzor_z_krawedziami[102];
        snprintf(wzor_z_krawedziami, "\\b%s\\b", wzor);
        print_match(dane, wzor_z_krawedziami);
    } else if (strstr(polecenie, "grep -i") == polecenie) {
        if (sscanf(polecenie + strlen("grep -i "), "%s", wzor) != 1) {
            printf("Nieprawidłowe argumenty dla polecenia grep\n");
            return 1;
        }
        print_matches(dane, wzor);
    } else if (strstr(polecenie, "grep -n") == polecenie) {
        if (sscanf(polecenie + strlen("grep -n "), "%s", wzor) != 1) {
            printf("Nieprawidłowe argumenty dla polecenia grep\n");
            return 1;
        }
        print_match_with_line_number(dane, wzor);
    } else {
        printf("Nieznana komenda: %s\n", polecenie);
        return 1;
    }

    return 0;
}