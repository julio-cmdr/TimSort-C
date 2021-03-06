#include "../headers/merge.h"
#include "../headers/utils.h"

// only for consecutive vectors
void merge(int *vector, int begin1, int begin2, int end){
	int p1 = begin1;
	int p2 = begin2;
	int length = end - begin1 + 1;

	int *temp = (int*)malloc(length*sizeof(int));

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

/*
	This merge function run two binary searches before starting the merge.
	It only copies a part of the vector, being a middle term between in-place and not in-place.
	It also uses the Galloping mode during merge.
*/
void optimized_merge(int *vector, int begin1, int begin2, int end){
	// ---------- redefines begin1 and end based on binary search

	//looks for the first element of the second vector in the first vector
	begin1 = binarySearch(vector, vector[begin2], begin1, begin2-1);
	//looks for the last element of the first vector in the second vector
	end = binarySearch(vector, vector[begin2-1], begin2, end)-1;

	int p1, p2;	
	int *temp;
	bool rightward;

	// checks which vector is smaller and which will be copied to temp
	
	if(begin2 - begin1 <= end + 1 - begin2){
		// copies a part of vector1 to temp		
		temp = (int*)malloc((begin2 - begin1)*sizeof(int));
		memcpy(temp, vector + begin1, (begin2 - begin1)*sizeof(int));
		
		rightward = true;
	} else {
		// copies a part of vector2 to temp
		temp = (int*)malloc((end + 1 - begin2)*sizeof(int));
		memcpy(temp, vector + begin2, (end + 1 - begin2)*sizeof(int));
		
		rightward = false;
	}

	if(temp != NULL){
		if(rightward){
			// merge the vectors from left to right

			p1 = 0;
			p2 = begin2;

			for(int i = begin1; i < end+1; i++){
				if(p1 < begin2-begin1 && p2 <= end){

					if(temp[p1] < vector[p2])
						vector[i] = temp[p1++];
					else
						vector[i] = vector[p2++];
					
				}else{

					if(p1 < begin2-begin1)
						vector[i] = temp[p1++];
					else
						vector[i] = vector[p2++];
				}
			}

		} else {
			// merge the vectors from right to left

			p1 = begin2-1;
			p2 = end - begin2;

			for(int i = end; i >= begin1; i--){
				if(p1 >= begin1 && p2 >= 0){
					// combinar ordenando
					if(vector[p1] > temp[p2])
						vector[i] = vector[p1--];
					else
						vector[i] = temp[p2--];
					
				}else{
					// copia o que sobrou
					if(p2 >= 0)
						vector[i] = temp[p2--];
					else
						vector[i] = vector[p1--];
				}
			}
		}
	}
	
	free(temp);
}

void mergeSort(int *V, int begin, int end){
	int half;
	if(begin<end){
		half = (int)((begin+end)/2);
		mergeSort(V, begin, half);
		mergeSort(V, half+1, end);
		optimized_merge(V, begin, half+1, end);
	}
}