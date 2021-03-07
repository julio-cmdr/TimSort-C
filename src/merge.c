#include "../headers/merge.h"
#include "../headers/utils.h"

#define MIN_GALOPE 7

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

	int count1 = 0;
	int count2 = 0;
	int galope1 = 1;
	int galope2 = 1;
	int last_p1, last_p2;
	int min_galope = MIN_GALOPE;

	if(temp != NULL){
		if(rightward){
			// merge the vectors from left to right

			p1 = 0;
			p2 = begin2;
			last_p1 = p1-1;
			last_p2 = p2-1;

			int i = begin1;
			while(p1 < begin2-begin1){

				if(p2 <= end && temp[p1] >= vector[p2]){
					count1 = 0;
					// checks if p1 is galloping
					if(galope1 > 1){
						p1 = binarySearch(temp, vector[p2], last_p1 + 1, p1);
						
						if(p1-1 - last_p1 > 0){
							memcpy(vector + i, temp + last_p1 + 1, (p1 - last_p1 - 1)*sizeof(int));
							i += p1 - last_p1 - 1;
						}

						last_p1 = p1 - 1;
						galope1 = 1;

					} else {

						count2++;
						
						memmove(vector + i, vector + last_p2 + 1, (p2 - last_p2)*sizeof(int));
						i += p2 - last_p2;							
						
						if(count2 > min_galope && galope2 > 0){						
							if(p2 + 2*galope2 <= end){
								galope2 = galope2*2;
							} else {
								galope2 = end - p2;
							}
						} else {
							galope2 = 1;
						}
						
						last_p2 = p2;
						p2 += galope2;
					}

				}else{
					count2 = 0;
					// checks if p2 is galloping
					if(galope2 > 1){
						p2 = binarySearch(vector, vector[p1], last_p2 + 1, p2);

						if(p2 - 1 - last_p2 > 0){
							memmove(vector + i, vector + last_p2 + 1, (p2 - last_p2 - 1)*sizeof(int));
							i += p2 - last_p2 - 1;
						}
						
						last_p2 = p2 - 1;
						galope2 = 1;
						
					} else {

						count1++;

						memcpy(vector + i, temp + last_p1 + 1, (p1 - last_p1)*sizeof(int));
						i += p1 - last_p1;

						if(count1 > min_galope && galope1 > 0){						
							if(p1 + 2*galope1 <= begin2-begin1-1){
								galope1 = galope1*2;							
							} else {
								galope1 = begin2-begin1-1 - p1;
							}
						} else {
							galope1 = 1;
						}
						
						last_p1 = p1;
						p1 += galope1;
					}
				}
			}

		} else {
			// merge the vectors from right to left

			p1 = begin2-1;
			p2 = end - begin2;

			for(int i = end; i >= begin1 && p2 >= 0; i--){			
				if(p1 >= begin1 && vector[p1] > temp[p2]){
					vector[i] = vector[p1--];
					count1++;
					count2 = 0;
				}else{
					vector[i] = temp[p2--];
					count2++;
					count1 = 0;
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