#include "../include/matrix_operations.h"
double sum_row(double* row, int columns_quanity) {
    double sum = 0;
    for (int i = 0; i < columns_quanity; ++i) {
        sum += row[i];
    }
    return sum;
}

int sum_rows(double * columns_sum, double ** matrix, int rows_quanity, int columns_quanity) {
    if(columns_sum == NULL) return error_row_sum;
    if(matrix == NULL) return error_with_matrix;
    for(int i = 0; i < rows_quanity; ++i){
        columns_sum[i] = sum_row(matrix[i], columns_quanity);
    }
    // for(int i =0; i< columns_quanity; ++i) {
    //     rows_sum[i] = sum_column(matrix, rows_quanity, i);
    // }
    return succes;
}

double sum_column(double** matrix, int rows_quanity, int number_column) {
    double sum = 0;
    for (int i = 0; i < rows_quanity; ++i) {
        sum += matrix[i][number_column];
    }
    return sum;
}

// int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity) {
//     if(rows_sum == NULL) return error_row_sum;
//     if(matrix == NULL) return error_with_matrix;
//     for(int i =0; i< columns_quanity; ++i) {
//         rows_sum[i] = sum_column(matrix, rows_quanity, i);
//     }
//     return succes;
// }

int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity) {
    if(rows_sum == NULL) return error_row_sum;
    if(matrix == NULL) return error_with_matrix;
    double ** transposed_matrix = NULL;
    init_matrix(&transposed_matrix, columns_quanity, rows_quanity);
    transpose(matrix, transposed_matrix, rows_quanity, columns_quanity);
    sum_rows(rows_sum, transposed_matrix, columns_quanity, rows_quanity);
    free_matrix(&transposed_matrix, columns_quanity);
    return succes;
}