#include <stdio.h>
#include <stdlib.h>

#define RANDOM 0
#define ASCENDING 1
#define DESCENDING 2

void printVector(int *vector, int length);
int binarySearch(int *vector, int item, int begin, int end);
void generateVector(int *vector, int length, int mode);