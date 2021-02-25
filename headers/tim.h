/*
    This code was write based on https://dev.to/jennieji/tim-sort-the-fastest-sort-used-in-v8-and-python-5e76
*/
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

typedef struct run{
    int *vector;
    int length;
}Run;

typedef struct runs{
    Run *runs;
    int n_runs;
}Runs;

void reverse_vector(int *vector, int length);

int count_run(int *vector, int length);

void timSort(int *vector, int length);