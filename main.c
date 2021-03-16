#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/inserction.h"
#include "headers/merge.h"
#include "headers/tim.h"
#include "headers/utils.h"


int main(int argc, char **argv){
	int length = 200;
	srand(time(NULL));  

	int *vector = (int*)malloc(sizeof(int)*length);
	generateVector(vector, length, RANDOM);
	printVector(vector, length);
	printf("\n\n");

	timSort(vector, length, optimized_merge, binary_inserction);
	printf("\nTim\n");
	printVector(vector, length);

	free(vector);
}
