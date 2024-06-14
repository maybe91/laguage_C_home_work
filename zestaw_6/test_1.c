#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "zadanie_1.c"

void test_get() {
    int matrix[] = {1, 2, 3, 4, 5, 6};
    Element e = {3, 1, 2};
    assert(get(e, matrix) == 6);
    printf("test_get passed\n");
}

void test_max_matrix_row_or_col_element() {
    int A[] = {1, 3, 3, 4, 5, 6};
    int B[] = {6, 5, 4, 3, 2, 1};
    int *result = max_matrix_row_or_col_element(true, 2, 3, 2, 3, A, B); //складываются столбики
    assert(result[0] == 7);
    assert(result[1] == 8);
    assert(result[2] == 7);
    free(result);

    printf("test_max_matrix_row_or_col_element passed\n");
}


void test_integration() {
    int A[] = {1, 2, 3, 4, 5, 6};
    int B[] = {6, 5, 4, 3, 2, 1};
    int *result = max_matrix_row_or_col_element(true, 2, 3, 2, 3, A, B);
    for (int i = 0; i < 3; i++) {
        Element e = {3, 0, i};
        assert(result[i] == get(e, A) + get(e, B));
    }
    free(result);

    result = max_matrix_row_or_col_element(false, 2, 3, 2, 3, A, B);
    for (int i = 0; i < 2; i++) {
        Element e = {3, i, 0};
        assert(result[i] == get(e, A) + get(e, B));
    }
    free(result);

    printf("test_integration passed\n");
}


int main() {
    test_get();
    test_max_matrix_row_or_col_element();
    test_integration();
}