#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
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
#define error_rows_sum 4
#define error_arg_quanity 5

void init_matrix(double*** pmatrix, int rows_quanity, int columns_quanity);
void free_matrix(double*** pmatrix, int rows_quanity, int columns_quanity);
int fill_file_with_matrix (FILE * file, double ** matrix, int rows_quanity, int columns_quanity);
int fill_matrix_from_file(FILE * file, double ** matrix, int rows_quanity, int columns_quanity);
void print_matrix(double ** matrix, int rows_quanity, int columns_quanity);
double sum_column(double** matrix, int rows_quanity, int number_column);
int sum_columns(double * rows_sum, double ** matrix, int rows_quanity, int columns_quanity);
void fill_matrix(double** matrix, int rows_quanity, int columns_quanity);

int sum_int(int a, int b);

//int str_to_int(const char* str);
