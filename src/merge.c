#include "../headers/merge.h"

void merge(int *vector, int begin, int half, int end){
	int end1 = 0, end2 = 0;
	int length = end - begin + 1;
	int p1 = begin;
	int p2 = half+1;

	int *temp = (int*)malloc(length*sizeof(int));

	if(temp != NULL){
		for(int i = 0; i < length; i++){
			if(!end1 && !end2){
				// combinar ordenando
				if(vector[p1] < vector[p2])
					temp[i] = vector[p1++];
				else
					temp[i] = vector[p2++];
				
				// verifica se o vetor acabou
				if(p1 > half)
					end1 = 1;
				if(p2 > end)
					end2 = 1;
			}else{
				// copia o que sobrou
				if(!end1)
					temp[i] = vector[p1++];
				else
					temp[i] = vector[p2++];
			}
		}
		int j = begin;
		for(int i = 0; i < length; i++){
			vector[j] = temp[i];
			j++;
		}
	}
	free(temp);
}

void mergeSort(int *V, int begin, int end){
	int half;
	if(begin<end){
		half = (int)((begin+end)/2);  // arredonda a divisão para baixo
		mergeSort(V, begin, half);    // chama a função para
		mergeSort(V, half+1, end);    // as duas metades
		merge(V, begin, half, end);
	}
}
