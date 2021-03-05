#include "../headers/merge.h"

// only for consecutive vectors
void merge(int *vector, int begin1, int begin2, int end){
	int p1 = begin1;
	int p2 = begin2;
	int length = end - begin1 + 1;

	int *temp = (int*)malloc((length)*sizeof(int));

	if(temp != NULL){
		for(int i = 0; i < length; i++){
			if(p1 <= begin2-1 && p2 <= end){
				// combinar ordenando
				if(vector[p1] < vector[p2])
					temp[i] = vector[p1++];
				else
					temp[i] = vector[p2++];
				
			}else{
				// copia o que sobrou
				if(p1 <= begin2-1)
					temp[i] = vector[p1++];
				else
					temp[i] = vector[p2++];
			}
		}
	}
	
	memcpy(vector + begin1, temp, (end-begin1+1)*sizeof(int));
	free(temp);
}

void mergeSort(int *V, int begin, int end){
	int half;
	if(begin<end){
		half = (int)((begin+end)/2);
		mergeSort(V, begin, half);
		mergeSort(V, half+1, end);
		merge(V, begin, half+1, end);
	}
}