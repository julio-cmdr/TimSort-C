#include "../headers/utils.h"

void printVector(int *vector, int length){
    for(int i = 0; i < length; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void generateVector(int *vector, int length, int mode){
	switch(mode){
		case RANDOM:
			for (int i = 0; i < length; i++){
				vector[i] = rand() % (length*2);
			}
		break;

		case ASCENDING:
			vector[0] = rand() % 3;
			for (int i = 1; i < length; i++){
				vector[i] = vector[i-1] + rand() % 4;
			}
		break;

		case DESCENDING:
			vector[0] = 3*length;
			for (int i = 1; i < length; i++){
				vector[i] = vector[i-1] - rand() % 4;
			}
		break;
	}
}

int binarySearch(int *vector, int item, int begin, int end){

    if (end <= begin){
        if (item > vector[begin]){
			return begin + 1;
		}
		return begin;
	}

    int mid = (begin + end) / 2;
 
    if (item == vector[mid])
        return mid + 1;
 
    if (item > vector[mid])
        return binarySearch(vector, item, mid + 1, end);
    
	return binarySearch(vector, item, begin, mid - 1);
}