#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers/inserction.h"
#include "headers/merge.h"
#include "headers/tim.h"
#include "headers/utils.h"


int main(int argc, char **argv){
	int length = 100;
	srand(time(NULL));  

	int *vector = (int*)malloc(sizeof(int)*length);
	for (int i = 0; i < length; i++){
		vector[i] = rand() % length;
		printf("%d ", vector[i]);
	}
	printf("\n\n");

	int *vector2 = (int*)malloc(sizeof(int)*length);
	
	memcpy(vector2, vector, sizeof(int)*length);
	binary_inserction(vector2, length);
	printf("Binary Inserction\n");
	printVector(vector2, length);

	memcpy(vector2, vector, sizeof(int)*length);
	mergeSort(vector2, 0, length-1);
	printf("\nMerge\n");
	printVector(vector2, length);

	timSort(vector, length);
	printf("\nTim\n");
	printVector(vector, length);

	free(vector);
	free(vector2);
}
