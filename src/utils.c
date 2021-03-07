#include "../headers/utils.h"

void printVector(int *vector, int length){
    for(int i = 0; i < length; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int min(int a, int b){
    if(a <= b){
        return a;
    }
    return b;
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