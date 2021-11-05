//
//
#include "stdio.h"
#include "stdlib.h"
#include "../include/matrix_operations.h"




int main(int argc, char *argv[]){
    // argv[1] - path; argv[2] - quanity of rows; argv[3] - quanity of columns;

    if (argc != args_quanity){
        assert("Error with quanity of arguments");
        exit(error_arg_quanity);
    }
    int rows_quan = atoi(argv[2]);
    int columns_quan = atoi (argv[3]);
    double ** matrix = NULL;
    init_matrix(&matrix, rows_quan, columns_quan);
    // argv[1] = "/home/viktor/Projects/c+c++/iz_2/project/src/file_with_matrix.txt"


    FILE * file_with_matrix = fopen(argv[1],"r"); 
    if (file_with_matrix == NULL)
    {
        assert("Error with file opening");
        exit(1);
    }
    int examination_fill_matrix = fill_matrix_from_file(file_with_matrix,matrix,rows_quan,columns_quan);
    switch (examination_fill_matrix){
        case error_with_matrix:
            assert("Error: matrix == NULL");
            free_matrix(&matrix, rows_quan, columns_quan);
            exit(error_with_matrix);
        case error_with_file:
            assert("Error: file == NULL");
            free_matrix(&matrix, rows_quan, columns_quan);
            exit(error_with_file);
        case error_with_scan:
            assert("Error: can't scan");
            free_matrix(&matrix, rows_quan, columns_quan);
            exit(error_with_scan);
        default:
            break;
    }
    fclose(file_with_matrix);
    
    double * rows_sum = (double*)malloc(sizeof(double)* columns_quan);
    int examination_sum = sum_columns(rows_sum, matrix, rows_quan,columns_quan);
    switch (examination_sum){
        case error_rows_sum:
            assert("Error: array with sums is empty");
            free (rows_sum);
            free_matrix(&matrix, rows_quan, columns_quan);
            exit(error_rows_sum);
        case error_with_matrix:
            assert("Error: matrix is empty");
            free (rows_sum);
            free_matrix(&matrix, rows_quan, columns_quan);
            exit(error_rows_sum);
        default:
            break;
    }
    for(int i = 0;i< columns_quan;++i){
        printf("%lf ",rows_sum[i]);
    }
    

    free (rows_sum);
    free_matrix(&matrix,rows_quan,columns_quan);

    return 0;
}
