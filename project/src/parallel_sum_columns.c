#include "../include/matrix_operations.h"

double sum_column(double** matrix, int rows_quanity, int number_column) {
    al8double_t sum = 0;
    for (al4int_t i = 0; i <rows_quanity; ++i) {
        sum += matrix[i][number_column];
    }
    return sum;
}

int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity) {
    if(unlikely(rows_sum == NULL)) return error_row_sum;
    if(unlikely(matrix == NULL)) return error_with_matrix;

    char *shared_memory = mmap(NULL, sizeof(double) * columns_quanity, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (unlikely(!shared_memory)) {
        printf("Failed to map\n");
        return 1;
    }
    int p_num = -1;
    pid_t pid =fork();

    if (unlikely(pid == -1)) {
        printf("Fork failed\n");
        if (unlikely(munmap(shared_memory, sizeof(double) * columns_quanity))) {
            return error_unmap;
        }
        return error_fork;
    }

    if(pid == 0) p_num = 0;
    if(p_num != 0) {
        for(int i = 1; i < 10; ++i) {
            if(pid != 0) {
                pid = fork();
                if(pid == 0) {
                    p_num = i;
                    break;
                }
            }
        }
    }
    if(likely(p_num != -1)) {
        for(al4int_t i = p_num; i< columns_quanity; i+=10) {
            ((double*)(shared_memory))[i] = sum_column(matrix, rows_quanity, i);
        }
    }

    if (unlikely(pid != 0)) {
        pid_t wait_result;
        for(int i=0; i<10; ++i) {
            wait_result = wait(NULL);
            if(unlikely(wait_result < 0)) {
                printf("Wait failed\n");
                if (unlikely(munmap(shared_memory, sizeof(double) * columns_quanity))) {
                    printf("Failed to unmap\n");
                    return error_unmap;
                }
                return error_wait;
            }
        }
        for(int i = 0; i < columns_quanity; ++i) {
            rows_sum[i] =((double*)(shared_memory))[i];
        }
    }
    else {
        exit(0);
    }
    if (unlikely(munmap(shared_memory, sizeof(double) * columns_quanity))) {
        return error_unmap;
    }
    return success;
}