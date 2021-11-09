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
    EXPECT_EQ(examination_sum, success);
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
    EXPECT_EQ(examination_sum, success);
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

TEST(MATRIX_TEST, test_init_matrix) {
    srand(time(NULL));
    double **matrix = NULL;
    al4int_t rows_quanity = (rand() % 16000 + 4000)/1000,
             columns_quanity = (rand() % 16000 + 4000)/1000;
    int check_init = init_matrix(&matrix, rows_quanity, columns_quanity);
    EXPECT_EQ(check_init, success);
    EXPECT_TRUE(matrix != NULL); //nullptr
    for(int i = 0; i < rows_quanity; ++i){
        EXPECT_TRUE(matrix[i] != NULL);
    }
    int check_free = free_matrix(&matrix, rows_quanity);
    EXPECT_EQ(check_free, success);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
