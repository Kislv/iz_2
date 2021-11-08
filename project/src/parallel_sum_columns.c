#include "../include/matrix_operations.h"

// void fill_matrix(double** matrix, int rows_quanity, int columns_quanity){
//     if(matrix == NULL) return error_with_matrix;
//     for (int i = 0;i < rows_quanity; ++i){
//         for(int k =0; k<columns_quanity; ++k){
//             matrix[i][k] = (double)(rand() % 20000 - 4000)/1000;
//         }
//     }
//     return;
// }

double sum_column(double** matrix, int rows_quanity, int number_column) {
    double sum = 0;
    for (int i = 0; i <rows_quanity; ++i) {
        sum += matrix[i][number_column];
    }
    return sum;
}

int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity) {
    //printf("IN PARALLEL SUM_COLUMNS\n");
    if(rows_sum == NULL) return error_row_sum;
    if(matrix == NULL) return error_with_matrix;
    //printf("AFTER CHEVKING FOR NULL POINTERS\n");
    char *shared_memory = mmap(NULL, sizeof(double) * columns_quanity, PROT_READ | PROT_WRITE,
                               MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!shared_memory) {
        printf("Failed to map\n");
        return 1;
    }
    //printf("AFTER SHARING MEMORY WITH MMAP\n");
    int p_num = -1;
    pid_t pid =fork();

    if (pid == -1) {
        printf("Fork failed\n");
        if (munmap(shared_memory, sizeof(double) * columns_quanity)) {
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
    if(p_num != -1) {
        for(int i = p_num; i< columns_quanity; i+=10) {
            ((double*)(shared_memory))[i] = sum_column(matrix, rows_quanity, i);
        }
    }
    //printf("AFTER CALCULATING SUM_COLUMN\n");


    if (pid != 0) {
        pid_t wait_result;
        for(int i=0; i<10; ++i) {
            wait_result = wait(NULL);
            if(wait_result < 0) {
                printf("Wait failed\n");
                if (munmap(shared_memory, sizeof(double) * columns_quanity)) {
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
    if (munmap(shared_memory, sizeof(double) * columns_quanity)) {
        return error_unmap;
    }
    return succes;
}
