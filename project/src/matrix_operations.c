#include "../include/matrix_operations.h"


int init_matrix(double*** pmatrix, int rows_quanity, int columns_quanity) {
    if(unlikely(*pmatrix != NULL)) return error_with_matrix;
    (*pmatrix) = (double**)malloc(sizeof(double*)*rows_quanity);
    for(al4int_t i = 0; i < rows_quanity; ++i) {
        (*pmatrix)[i] =(double*)malloc(sizeof(double)*columns_quanity);
    }
    return success;
}
int free_matrix(double*** pmatrix, int rows_quanity) {
    if(unlikely(*pmatrix ==NULL)) return error_with_matrix;
    for(al4int_t i = 0; i < rows_quanity; ++i) {
        free((*pmatrix)[i]);
    }
    free(*pmatrix);
    return success;
}

int fill_file_with_matrix (FILE * file, double ** matrix, int rows_quanity, int columns_quanity) {
    if (unlikely(matrix == NULL)) return error_with_matrix;
    if (unlikely(!file)) return error_with_file;
    for(al4int_t i = 0; i< rows_quanity; ++i) {
        for(al4int_t k = 0; k < columns_quanity; ++k) {
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
            fprintf(file,"%lf ",matrix[i][k]);
        }
        fprintf(file,"\n");
    }
    return success;
}

int fill_matrix_from_file(FILE * file, double ** matrix, int rows_quanity, int columns_quanity) {
    if (unlikely(matrix == NULL)) return error_with_matrix;
    if (unlikely(file == NULL)) return error_with_file;
    for(al4int_t i = 0; i < rows_quanity; ++i) {
        for(al4int_t k = 0; k < columns_quanity; ++k) {
            if(unlikely(fscanf(file,"%lf", &(matrix[i][k]))) == 0) return error_with_scan;
        }
    }
    return success;
}

void print_matrix(double ** matrix, int rows_quanity, int columns_quanity) {
    for(al4int_t i = 0; i< rows_quanity; ++i) {
        for(al4int_t k = 0; k < columns_quanity; ++k) {
            printf("%lf ", matrix[i][k]);
        }
        printf("\n");
    }
}

int fill_matrix(double** matrix, int rows_quanity, int columns_quanity) {
    if(unlikely(matrix == NULL)) return error_with_matrix;
    for (al4int_t i = 0; i < rows_quanity; ++i) {
        for(register al4int_t k = 0; k < columns_quanity; ++k) {
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
        }
    }
    return 0;
}
