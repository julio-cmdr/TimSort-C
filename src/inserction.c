#include "../headers/inserction.h"
#include "../headers/utils.h"

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

void binary_inserction(int *vector, int length){
	int j, aux, index;

	for(int i = 1; i < length; i++){
		if(vector[i-1] > vector[i]){
			aux = vector[i];
			
			index = binarySearch(vector, aux, 0, i-1);

			// move all elements from index to i one position right 
			memmove(vector + index + 1, vector + index, (i-index)*sizeof(int));
					
			vector[index] = aux;
		}
	}
}
