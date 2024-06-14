#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int cols_num;
    int row;
    int col;
} Element;

int get(Element e, const int *matrix) {
    return matrix[e.row * e.cols_num + e.col];
}

int * max_matrix_row_or_col_element(bool horizontal, int rowsA, int colsA, int rowsB, int colsB, int *A, int *B) {
    if (horizontal) {
        if (colsA != colsB) return NULL;
        int *result = malloc(colsA * sizeof(int));
        for (int i = 0; i < colsA; i++) {
            result[i] = get((Element){colsA, 0, i}, A) + get((Element){colsB, 0, i}, B);
            for (int j = 1; j < rowsA && j < rowsB; j++) {
                int sum = get((Element){colsA, j, i}, A) + get((Element){colsB, j, i}, B);
                if (sum > result[i]) result[i] = sum;
            }
        }
        return result;
    } else {
        if (rowsA != rowsB) return NULL;
        int *result = malloc(rowsA * sizeof(int));
        for (int i = 0; i < rowsA; i++) {
            result[i] = get((Element){colsA, i, 0}, A) + get((Element){colsB, i, 0}, B);
            for (int j = 1; j < colsA && j < colsB; j++) {
                int sum = get((Element){colsA, i, j}, A) + get((Element){colsB, i, j}, B);
                if (sum > result[i]) result[i] = sum;
            }
        }
        return result;
    }
}
