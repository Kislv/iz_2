#include "../include/matrix_operations.h"


void init_matrix(double*** pmatrix, int rows_quanity, int columns_quanity){
    if(*pmatrix != NULL) return error_with_matrix;
    (*pmatrix) = (double**)malloc(sizeof(double*)*rows_quanity);
    for(int i = 0;i < rows_quanity; ++i){
        (*pmatrix)[i] =(double*)malloc(sizeof(double)*columns_quanity);
    }
}
void free_matrix(double*** pmatrix, int rows_quanity, int columns_quanity){
    if(*pmatrix ==NULL) return error_with_matrix;
    for(int i = 0;i < rows_quanity; ++i){
        free((*pmatrix)[i]);
    }
    free(*pmatrix);
}

int fill_file_with_matrix (FILE * file, double ** matrix, int rows_quanity, int columns_quanity){
    if (matrix == NULL) return error_with_matrix;
    if (!file) return error_with_file;
    for(int i = 0; i< rows_quanity; ++i){
        for(int k = 0; k < columns_quanity; ++k){
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
            fprintf(file,"%lf ",matrix[i][k]);
        }
    fprintf(file,"\n");
    }
    return succes;
}

int fill_matrix_from_file(FILE * file, double ** matrix, int rows_quanity, int columns_quanity){
    if (matrix == NULL) return error_with_matrix;
    if (file == NULL) return error_with_file;
    for(int i = 0; i< rows_quanity; ++i){
        for(int k = 0; k < columns_quanity; ++k){
            if(fscanf(file,"%lf", &(matrix[i][k])) == NULL) return error_with_scan;
        }
    }
    return succes;
};

void print_matrix(double ** matrix, int rows_quanity, int columns_quanity){
        for(int i = 0; i< rows_quanity; ++i){
            for(int k = 0; k < columns_quanity; ++k){
                printf("%lf ", matrix[i][k]);
            }
        printf("\n");
    }
}

void fill_matrix(double** matrix, int rows_quanity, int columns_quanity){
    for (int i = 0;i < rows_quanity; ++i){
        for(int k =0; k<columns_quanity; ++k){
            matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
        }
    }
    return;
}
int sum_int(int a, int b){
    return a+b;
}
