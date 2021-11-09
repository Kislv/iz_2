#include "stdio.h"
#include "stdlib.h"
#include "../include/matrix_operations.h"




int main(int argc, char *argv[]) {
    // argv[1] - path; argv[2] - quanity of rows; argv[3] - quanity of columns;
    clock_t begin = clock();
    printf("start = %ld \n", begin);

    if (unlikely(argc != args_quanity)) {
        assert("Error with quanity of arguments");
        exit(error_arg_quanity);
    }
    al4int_t rows_quan = atoi(argv[2]);
    al4int_t columns_quan = atoi (argv[3]);
    double ** matrix = NULL;
    init_matrix(&matrix, rows_quan, columns_quan);

    FILE * file_with_matrix = fopen(argv[1],"r");
    if (unlikely(file_with_matrix == NULL))
    {
        assert("Error with file opening");
        exit(1);
    }
    clock_t begin_fill = clock();
    fill_matrix(matrix, rows_quan, columns_quan);

    clock_t end_fill = clock();
    printf("Fill time =  %f\n", difftime(end_fill, begin_fill));

    fclose(file_with_matrix);

    double *row_sum = (double*)malloc(sizeof(double)* columns_quan);

    clock_t begin_sum = clock();
    int examination_sum = sum_columns(row_sum, matrix, rows_quan,columns_quan);
    clock_t end_sum = clock();
    printf("Sum time =  %f\n", difftime(end_sum, begin_sum));
    switch (examination_sum) {
    case unlikely(error_row_sum):
        assert("Error: array with sums is empty");
        free (row_sum);
        free_matrix(&matrix, rows_quan);
        exit(error_row_sum);
    case error_with_matrix:
        assert("Error: matrix is empty");
        free (row_sum);
        free_matrix(&matrix, rows_quan);
        exit(error_row_sum);
    default:
        break;
    }

    free (row_sum);
    free_matrix(&matrix,rows_quan);
    clock_t end = clock();
    printf("end = %ld \n", end);
    printf(" Time = %lf \n",difftime(end,begin));
    return 0;
}