#include "../include/matrix_operations.h"


int init_matrix(double*** pmatrix, int rows_quanity, int columns_quanity) {
    if(*pmatrix != NULL) return error_with_matrix;
    (*pmatrix) = (double**)malloc(sizeof(double*)*rows_quanity);
    for(int i = 0; i < rows_quanity; ++i) {
        (*pmatrix)[i] =(double*)malloc(sizeof(double)*columns_quanity);
    }
    return succes;
}
int free_matrix(double*** pmatrix, int rows_quanity) {
    if(*pmatrix ==NULL) return error_with_matrix;
    for(int i = 0; i < rows_quanity; ++i) {
        free((*pmatrix)[i]);
    }
    free(*pmatrix);
    return succes;
}

int fill_file_with_matrix (FILE * file, double ** matrix, int rows_quanity, int columns_quanity) {
    if (matrix == NULL) return error_with_matrix;
    if (!file) return error_with_file;
    for(int i = 0; i< rows_quanity; ++i) {
        for(int k = 0; k < columns_quanity; ++k) {
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
            fprintf(file,"%lf ",matrix[i][k]);
        }
        fprintf(file,"\n");
    }
    return succes;
}

int fill_matrix_from_file(FILE * file, double ** matrix, int rows_quanity, int columns_quanity) {
    if (matrix == NULL) return error_with_matrix;
    if (file == NULL) return error_with_file;
    for(int i = 0; i< rows_quanity; ++i) {
        for(int k = 0; k < columns_quanity; ++k) {
            if(fscanf(file,"%lf", &(matrix[i][k])) == 0) return error_with_scan;
        }
    }
    return succes;
}

void print_matrix(double ** matrix, int rows_quanity, int columns_quanity) {
    for(int i = 0; i< rows_quanity; ++i) {
        for(int k = 0; k < columns_quanity; ++k) {
            printf("%lf ", matrix[i][k]);
        }
        printf("\n");
    }
}

int fill_matrix(double** matrix, int rows_quanity, int columns_quanity) {
    if(matrix == NULL) return error_with_matrix;
    for (int i = 0; i < rows_quanity; ++i) {
        for(int k =0; k<columns_quanity; ++k) {
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
        }
    }
    return 0;
}





// double sum_row(double* row, int columns_quanity) {
//     double sum = 0;
//     for (int i = 0; i < columns_quanity; ++i) {
//         sum += row[i];
//     }
//     return sum;
// }

// int sum_rows(double * columns_sum, double ** matrix, int rows_quanity, int columns_quanity) {
//     if(columns_sum == NULL) return error_row_sum;
//     if(matrix == NULL) return error_with_matrix;
//     for(int i = 0; i < rows_quanity; ++i){
//         columns_sum[i] = sum_row(matrix[i], columns_quanity);
//     }
//     // for(int i =0; i< columns_quanity; ++i) {
//     //     rows_sum[i] = sum_column(matrix, rows_quanity, i);
//     // }
//     return succes;
// }

// void copy_matrix(double **matrix_source, double **matrix_receiver, int rows_quanity, int columns_quanity){
//     for(int i = 0; i < rows_quanity; ++i){
//         for(int k = 0; k < columns_quanity; ++k){
//             matrix_receiver[i][k] = matrix_source[i][k];
//         };
//     }
// }
// int transpose(double ****matrix, int rows_quanity, int columns_quanity){
//     if(**matrix == NULL) return error_with_matrix;
//     double **transposed_matrix = NULL;
//     init_matrix(&transposed_matrix, columns_quanity, rows_quanity);
//     for (int i = 0; i < rows_quanity; ++i){
//         for (int k = 0; k < columns_quanity; ++k){
//             transposed_matrix[k][i] = (**matrix)[i][k];
//         }
//     }
//     free_matrix(*matrix,rows_quanity);
//     init_matrix(*matrix,rows_quanity, columns_quanity);
//     copy_matrix(transposed_matrix, (**matrix), columns_quanity, rows_quanity);
//     free_matrix(&transposed_matrix, columns_quanity);
//     return succes;
// }
int transpose(double **matrix, double **transposed_matrix, int rows_quanity, int columns_quanity){
    if(matrix == NULL) return error_with_matrix;
    if(transposed_matrix == NULL) return error_with_matrix;
    for (int i = 0; i < rows_quanity; ++i){
        for (int k = 0; k < columns_quanity; ++k){
            transposed_matrix[k][i] = matrix[i][k];
        }
    }
    return succes;
}