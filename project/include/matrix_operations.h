#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <malloc.h>
#include <sys/mman.h>

#define rows 100
#define columns 50
#define args_quanity 4

#define succes 0
#define error_with_file 1
#define error_with_matrix 2
#define error_with_scan 3
#define error_row_sum 4
#define error_arg_quanity 5
#define error_fork 6
#define error_unmap 7
#define error_wait 8

int init_matrix(double*** pmatrix, int rows_quanity, int columns_quanity);
int free_matrix(double*** pmatrix, int rows_quanity);
int fill_file_with_matrix (FILE * file, double ** matrix, int rows_quanity, int columns_quanity);
int fill_matrix_from_file(FILE * file, double ** matrix, int rows_quanity, int columns_quanity);
void print_matrix(double ** matrix, int rows_quanity, int columns_quanity);
double sum_column(double** matrix, int rows_quanity, int number_column);
int sum_columns(double * row_sum, double ** matrix, int rows_quanity, int columns_quanity);
int fill_matrix(double** matrix, int rows_quanity, int columns_quanity);
int transpose(double **matrix, double **transposed_matrix, int rows_quanity, int columns_quanity);


