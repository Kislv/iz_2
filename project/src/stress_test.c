#include <dlfcn.h>
#include "../include/matrix_operations.h"

int main() {
    srand(time(NULL));
    al4int_t rows_quan = 10000,
        columns_quan = 5000;
    double ** matrix = NULL;
    init_matrix(&matrix, rows_quan, columns_quan);
    fill_matrix(matrix,rows_quan, columns_quan);

    //optimization by alignment
    double *row_sum_i_p =NULL;
    int errflag_p;
    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1dcls == -1) l1dcls = sizeof(void*);
    errflag_p = posix_memalign((void**)&row_sum_i_p, l1dcls, sizeof(double)* columns_quan);
    if(errflag_p){
        assert("Error: errflag_p !=0\n");
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        exit(1); 
    }

    double *row_sum_i_c =NULL;
    int errflag_c;
    if (l1dcls == -1) l1dcls = sizeof(void*);
    errflag_c = posix_memalign((void**)&row_sum_i_c, l1dcls, sizeof(double)* columns_quan);
    if(errflag_c){
        assert("Error: errflag_c !=0\n");
        free(row_sum_i_p);
        free(row_sum_i_c);
        free_matrix(&matrix, rows_quan);
        exit(1); 
    }
    //free(row_sum_i_p);
    //free(row_sum_i_c);


    void* d_library;
    int (*my_func)( double* row_sum_i_p, double** matrix, int rows_q, int columns_q);
    d_library = dlopen("libsum_parallel.so", RTLD_LAZY);    
    *(int**)(&my_func) = dlsym(d_library, "sum_columns");


    time_t start = clock();
    int parall_res = (*my_func)(row_sum_i_p, (double**)matrix, rows_quan, columns_quan);
    time_t finish = clock();

    printf("parall sum time: clock() = %ld \n", finish-start);


    switch (parall_res)
    {
    case error_row_sum:
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Invalid row_sum");
        exit(0);
        break;
    case error_with_matrix:
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Invalid matrix");
        exit(0);
        break;
    case unlikely(error_unmap):
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Can not unmap");
        exit(0);
        break;
    case error_fork:
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Error with fork");
        exit(0);
        break;
    case error_wait:
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Error with wait");
        exit(0);
        break;
    default:
        break;
    }

    dlclose(d_library);

    //clock_gettime(CLOCK_MONOTONIC, &begin);
    //printf("consistent start s = %ld, ns = %ld\n", begin.tv_sec, begin.tv_nsec);
    start = clock();
    int result_consistent = sum_columns(row_sum_i_c, matrix, rows_quan, columns_quan);
    finish = clock();
    //clock_gettime(CLOCK_MONOTONIC, &end);
    //printf("consistent start s = %ld, ns = %ld\n", end.tv_sec, end.tv_nsec);
    //alg_time = 1000000000*(end.tv_sec - begin.tv_sec)+(end.tv_nsec - begin.tv_nsec);
    printf("consistent sum time: clock() = %ld \n", finish-start);
    


    switch (result_consistent)
    {
    case error_row_sum:
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Invalid row_sum");
        exit(0);
        break;

    case unlikely(error_with_matrix):
        free(row_sum_i_c);
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        assert("Invalid matrix");
        exit(0);
        break;
    default:
        break;
    }

    free_matrix(&matrix, rows_quan);
    int sum_check = 0;


    for(al4int_t k = 0; k < columns_quan; ++k) {
        if(unlikely(row_sum_i_c[k] != row_sum_i_p[k])) sum_check = 1;
    }
    if(unlikely(sum_check)) {
        free(row_sum_i_c);
        free(row_sum_i_p);
        assert("Sum checking failed");
        exit(0);
    };
    printf("stress test done\n");
    free(row_sum_i_c);
    free(row_sum_i_p);
    return 0;
}