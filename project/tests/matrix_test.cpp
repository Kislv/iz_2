#include <gtest/gtest.h>

extern "C" {
#include "../include/matrix_operations.h"
}

TEST(MATRIX_TEST, square_matrix_test) {
    al4int_t rows_quan = 4;
    al4int_t columns_quan = 4;
    double ** matrix = NULL;
    init_matrix(&matrix, rows_quan, columns_quan);
    fill_matrix(matrix,rows_quan,columns_quan);

    double * rows_sum = (double*)malloc(sizeof(double)* columns_quan);
    int examination_sum = sum_columns(rows_sum, matrix, rows_quan, columns_quan);
    EXPECT_EQ(examination_sum, succes);
    double * alternative_rows_sum = (double*)malloc(sizeof(double)* columns_quan);
    for(int i =0; i< columns_quan; ++i) {
        alternative_rows_sum[i] = sum_column(matrix, rows_quan, i);
    }
    for(int i = 0; i< columns_quan; ++i) {
        ASSERT_FLOAT_EQ(rows_sum[i],alternative_rows_sum[i]);
    }
    free(rows_sum);
    free(alternative_rows_sum);
    free_matrix(&matrix, rows_quan);
}
TEST(MATRIX_TEST, big_rows_quanity_test) {
    al4int_t rows_quan = 400;
    al4int_t columns_quan = 4;
    double ** matrix = NULL;
    init_matrix(&matrix, rows_quan, columns_quan);
    fill_matrix(matrix,rows_quan,columns_quan);

    double * rows_sum = (double*)malloc(sizeof(double)* columns_quan);
    int examination_sum = sum_columns(rows_sum, matrix, rows_quan, columns_quan);
    EXPECT_EQ(examination_sum, succes);
    double * alternative_rows_sum = (double*)malloc(sizeof(double)* columns_quan);
    for(int i =0; i< columns_quan; ++i) {
        alternative_rows_sum[i] = sum_column(matrix, rows_quan, i);
    }
    for(int i = 0; i< columns_quan; ++i) {
        ASSERT_FLOAT_EQ(rows_sum[i],alternative_rows_sum[i]);
    }
    free(rows_sum);
    free(alternative_rows_sum);
    free_matrix(&matrix, rows_quan);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
