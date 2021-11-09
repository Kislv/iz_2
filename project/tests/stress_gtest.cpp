#include <dlfcn.h>
#include <gtest/gtest.h>

extern "C" {
#include "../include/matrix_operations.h"
}

TEST(STRESS_TESTS, parallel_with_consistent) {
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
    EXPECT_EQ(errflag_p, success);
    if(errflag_p) {
        assert("Error: errflag_p !=0\n");
        free(row_sum_i_p);
        free_matrix(&matrix, rows_quan);
        exit(1);
    }

    double *row_sum_i_c =NULL;
    int errflag_c;
    if (l1dcls == -1) l1dcls = sizeof(void*);
    errflag_c = posix_memalign((void**)&row_sum_i_c, l1dcls, sizeof(double)* columns_quan);
    EXPECT_EQ(errflag_c, success);
    if(errflag_c) {
        assert("Error: errflag_c !=0\n");
        free(row_sum_i_p);
        free(row_sum_i_c);
        free_matrix(&matrix, rows_quan);
        exit(1);
    }

    void* d_library;
    int (*my_func)( double* row_sum_i_p, double** matrix, int rows_q, int columns_q);
    d_library = dlopen("libsum_parallel.so", RTLD_LAZY);
    *(int**)(&my_func) = (int*)dlsym(d_library, "sum_columns");


    time_t start = clock();
    int parall_res = (*my_func)(row_sum_i_p, (double**)matrix, rows_quan, columns_quan);
    time_t finish = clock();

    printf("parallel sum time: clock() = %ld \n", finish - start);

    EXPECT_EQ(parall_res, success);
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


    time_t start_c = clock();
    int result_consistent = sum_columns(row_sum_i_c, matrix, rows_quan, columns_quan);
    time_t finish_c = clock();
    printf("consistent sum time: clock() = %ld \n", finish_c -start_c);


    EXPECT_EQ(result_consistent, success);
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
        ASSERT_FLOAT_EQ(row_sum_i_c[k], row_sum_i_p[k]);
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
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}