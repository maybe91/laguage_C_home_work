
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zadanie_2.c"

#define MAX_LINE_LENGTH 1000

typedef struct {
    int start;
    int end;
} ranges;

void test_read_lines() {
    FILE *fp = freopen("test.txt", "r", stdin);
    if (fp == NULL) {
        printf("Error: could not open test file\n");
        return;
    }

    char **lines = read_lines(3);
    assert(lines != NULL);
    assert(strcmp(lines[0], "line 1\n") == 0);
    assert(strcmp(lines[1], "line 2\n") == 0);
    assert(strcmp(lines[2], "line 3\n") == 0);

    fclose(fp);
}

void test_extract_numbers() {
    char *lines[] = {"123 abc 456", "789 def"};
    Range *ranges = extract_numbers(lines, 2, 10);
    assert(ranges != NULL);
    assert(ranges[0].start == 0);
    assert(ranges[0].end == 2);
    assert(ranges[1].start == 8);
    assert(ranges[1].end == 10);
}
void test_integration() {
    FILE *fp = freopen("test.txt", "r", stdin);
    if (fp == NULL) {
        printf("Error: could not open test file\n");
        return;
    }

    char **lines = read_lines(3);
    assert(lines != NULL);

    Range *ranges = extract_numbers(lines, 3, 10);
    assert(ranges != NULL);

    assert(ranges[0].start == 0);
    assert(ranges[0].end == 2);
    assert(ranges[1].start == 8);
    assert(ranges[1].end == 10);

    fclose(fp);
}

int main() {
    test_read_lines();
    test_extract_numbers();
    test_integration();

    printf("All tests passed\n");

    return 0;
}
