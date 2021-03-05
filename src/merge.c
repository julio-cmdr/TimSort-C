#include "../headers/merge.h"

int *merge(int *vector1, int begin1, int end1, int *vector2, int begin2, int end2){
	int p1 = begin1;
	int p2 = begin2;
	int length = end1 - begin1 + end2 - begin2 + 2;

	int *temp = (int*)malloc((length)*sizeof(int));

	if(temp != NULL){
		for(int i = 0; i < length; i++){
			if(p1 <= end1 && p2 <= end2){
				// combinar ordenando
				if(vector1[p1] < vector2[p2])
					temp[i] = vector1[p1++];
				else
					temp[i] = vector2[p2++];
				
			}else{
				// copia o que sobrou
				if(p1 <= end1)
					temp[i] = vector1[p1++];
				else
					temp[i] = vector2[p2++];
			}
		}
	}
	return temp;
}

void mergeSort_aux(int *V, int begin, int end){
	int half;
	if(begin<end){
		half = (int)((begin+end)/2);
		mergeSort_aux(V, begin, half);
		mergeSort_aux(V, half+1, end);
		
		int *tmp;
		tmp = merge(V, begin, half, V, half+1, end);

		memcpy(V + begin, tmp, (end-begin+1)*sizeof(int));

		free(tmp);

	}
}

// In the last merge I dont copy the vector, I just free it and replace the reference
void mergeSort(int **vector, int length){
	int half = (int)(length/2);
	mergeSort_aux(*vector, 0, half);
	mergeSort_aux(*vector, half+1, length-1);

	int *tmp;
	tmp = merge(*vector, 0, half, *vector, half+1, length-1);

	free(*vector);
	*vector = tmp;
}
