#include "../headers/inserction.h"

void inserction(int *vector, int length){
	int j;
	int aux;
	for(int i = 1; i < length; i++){
		aux = vector[i];
		for(j = i; (j > 0) && (aux < vector[j-1]); j--)
			vector[j] = vector[j-1];
		vector[j] = aux;
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

void binary_inserction(int *vector, int length){
	int j, aux, index;

	for(int i = 1; i < length; i++){
		aux = vector[i];

		index = binarySearch(vector, aux, 0, i-1);

		printf("index %d\n", index);
		// move all elements from index to i one position right 
		memmove(vector + index + 1, vector + index, (i-index)*sizeof(int));
				
		vector[index] = aux;
	}
}