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