Miejsce zajęte w 86% … Jeśli zabraknie Ci miejsca, stracisz możliwość tworzenia i edytowania plików, a także ich przesyłania. Zyskaj 100 GB miejsca na dane przez 1 miesiąc za 8,99 zł 2,25 zł (cena przygotowana specjalnie dla Ciebie).
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

typedef struct {
    int start;
    int end;
} Range;

char **read_lines(int N) {
    char **lines = malloc(N * sizeof(char *));
    if (lines == NULL) {
        printf("Error: could not allocate memory for lines\n");
        return NULL;
    }

    int num_lines = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        if (num_lines == N) {
            N *= 2;
            char **new_lines = realloc(lines, N * sizeof(char *));
            if (new_lines == NULL) {
                printf("Error: could not reallocate memory for lines\n");
                return NULL;
            }
            lines = new_lines;
        }
        lines[num_lines] = strdup(line);
        num_lines++;
    }

    return lines;
}

Range *extract_numbers(char **lines, int num_lines, int base) {
    Range *ranges = malloc(num_lines * sizeof(Range));
    if (ranges == NULL) {
        printf("Error: could not allocate memory for ranges\n");
        return NULL;
    }

    for (int i = 0; i < num_lines; i++) {
        char *ptr = lines[i];
        int start = -1;
        int end = -1;
        while (*ptr != '\0') {
            if (strchr("0123456789ABCDEFabcdef", *ptr) != NULL) {
                if (start == -1) {
                    start = ptr - lines[i];
                }
                end = ptr - lines[i];
            } else {
                if (start != -1 && end != -1) {
                    ranges[i].start = start;
                    ranges[i].end = end;
                    start = -1;
                    end = -1;
                }
            }
            ptr++;
        }
        if (start != -1 && end != -1) {
            ranges[i].start = start;
            ranges[i].end = end;
        }
    }

    return ranges;
}
