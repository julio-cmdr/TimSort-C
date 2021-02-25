#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/inserction.h"
#include "headers/merge.h"
#include "headers/tim.h"

void printRun(Run run){
	for (int i = 0; i < run.length; i++){
		printf("%d ", run.vector[i]);
	}
	printf("\n");
}

int main(int argc, char **argv){
	int length = 100;
	srand(time(NULL));  

	int *vector = (int*)malloc(sizeof(int)*length);
	for (int i = 0; i < length; i++){
		vector[i] = rand() % length;
		printf("%d ", vector[i]);
	}
	printf("\n\n");

	//inserction(vector, length);
	//mergeSort(vector, 0, length);

	Runs runs = timSort(vector, length);

	for (int i = 0; i < runs.n_runs; i++){
		printRun(runs.runs[i]);
	}
	printf("\n\n");

	return 0;
}
