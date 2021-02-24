#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/inserction.h"
#include "headers/merge.h"


int main(int argc, char **argv){
	int length = 10;
	srand(time(NULL));  

	int *vector = (int*)malloc(sizeof(int)*length);
	for (int i = 0; i< length; i++){
		vector[i] = rand() % 50;
		printf("%d ", vector[i]);
	}
	printf("\n\n");

	//inserction(vector, length);
	mergeSort(vector, 0, length);

	for (int i = 0; i< length; i++){
		printf("%d ", vector[i]);
	}
	printf("\n\n");

	return 0;
}
