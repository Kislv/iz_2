#include "../include/matrix_operations.h"
double sum_column(double** matrix, int rows_quanity, int number_column) {
    al8double_t sum = 0;
    for (al4int_t i = 0; i < rows_quanity; ++i) {
        sum += matrix[i][number_column];
    }
    return sum;
}

int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity) {
    if(unlikely(rows_sum == NULL)) return error_row_sum;
    if(unlikely(matrix == NULL)) return error_with_matrix;
    for(al4int_t i =0; i< columns_quanity; ++i) {
        rows_sum[i] = sum_column(matrix, rows_quanity, i);
    }
    return success;
}