#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include "headers/inserction.h"
#include "headers/merge.h"
#include "headers/tim.h"
#include "headers/utils.h"

#define INSERCTION 0
#define BINARY_INSERCTION 1
#define MERGE 2
#define OPTIMIZED_MERGE 3
#define SIMPLE_TIM 4
#define SIMPLE_TIM1 5
#define SIMPLE_TIM2 6
#define TIM 7

char algorithm[8][18] = {"Inserction", "Binary Inserction", "Merge", "Optimized Merge", "Simple Tim", "Simple Tim1", "Simple Tim2", "Tim"};
char modes[3][11] = {"Random", "Ascending", "Descending"};

void sort(int *vector, int length, int algorithm){
	switch (algorithm){
		case INSERCTION:
			inserction(vector, length);
		break;

		case BINARY_INSERCTION:
			binary_inserction(vector, length);
		break;

		case MERGE:
			mergeSort(vector, 0, length-1, merge);
		break;

		case OPTIMIZED_MERGE:
			mergeSort(vector, 0, length-1, optimized_merge);
		break;

		case SIMPLE_TIM:
			timSort(vector, length, merge, inserction);
		break;

		case SIMPLE_TIM1:
			timSort(vector, length, merge, binary_inserction);
		break;

		case SIMPLE_TIM2:
			timSort(vector, length, optimized_merge, inserction);
		break;

		case TIM:
			timSort(vector, length, optimized_merge, binary_inserction);
		break;
	}
}

int main(int argc, char **argv){
	srand(time(NULL));
	struct timeval begin, end;
	long seconds, microseconds;

	int *vector = (int*)malloc(sizeof(int)*1000000);
	int *vector2 = (int*)malloc(sizeof(int)*1000000);

	int lengths[] = {1000, 10000, 100000, 1000000};
	
	printf("Execution,length,mode,algorithm,time\n");
	for(int mode = 0; mode < 3; mode++){
		// mode
		for(int j = 0; j < 4; j++){
			// lengths
			for(int k = 0; k < 10; k++){
				// 10 runs

				generateVector(vector, lengths[j], mode);

				for(int alg_id = 0; alg_id < 8; alg_id++){

					printf("%d,%d,%s,%s,", k, lengths[j], modes[mode], algorithm[alg_id]);
					memcpy(vector2, vector, sizeof(int)*lengths[j]);
					gettimeofday(&begin, 0);

					sort(vector2, lengths[j], alg_id);
					
					gettimeofday(&end, 0);
					seconds = end.tv_sec - begin.tv_sec;
					microseconds = end.tv_usec - begin.tv_usec;
					printf("%.6f\n", seconds + microseconds*1e-6);

				}
			}
		}
	}

	free(vector);
	free(vector2);
}