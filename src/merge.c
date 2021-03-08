#include "../headers/merge.h"
#include "../headers/utils.h"

#define INITIAL_MIN_GALLOP 8

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
	Only for consecutive vectors.
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
	int gallop1 = 1;
	int gallop2 = 1;
	int last_p1, last_p2;
	int min_gallop = INITIAL_MIN_GALLOP;

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
					if(gallop1 > 1){
						p1 = binarySearch(temp, vector[p2], last_p1 + 1, p1);
						
						if(p1-1 - last_p1 > 0){
							memcpy(vector + i, temp + last_p1 + 1, (p1 - last_p1 - 1)*sizeof(int));
							i += p1 - last_p1 - 1;
						}

						last_p1 = p1 - 1;
						gallop1 = 1;

					} else {

						count2++;
						
						memmove(vector + i, vector + last_p2 + 1, (p2 - last_p2)*sizeof(int));
						i += p2 - last_p2;							
						
						if(count2 > 1){
							if(count2 > min_gallop && gallop2 > 0){						
								if(p2 + 2*gallop2 <= end){
									gallop2 = gallop2*2;
								} else {
									gallop2 = end - p2;
								}
							} else {
								gallop2 = 1;
							}
							min_gallop--;
						}else{
							min_gallop++;
						}
						
						last_p2 = p2;
						p2 += gallop2;
					}

				}else{
					count2 = 0;
					// checks if p2 is galloping
					if(gallop2 > 1){
						p2 = binarySearch(vector, temp[p1], last_p2 + 1, p2);

						if(p2 - 1 - last_p2 > 0){
							memmove(vector + i, vector + last_p2 + 1, (p2 - last_p2 - 1)*sizeof(int));
							i += p2 - last_p2 - 1;
						}
						
						last_p2 = p2 - 1;
						gallop2 = 1;
						
					} else {

						count1++;

						memcpy(vector + i, temp + last_p1 + 1, (p1 - last_p1)*sizeof(int));
						i += p1 - last_p1;

						if(count1 > 1){
							if(count1 > min_gallop && gallop1 > 0){						
								if(p1 + 2*gallop1 <= begin2-begin1-1){
									gallop1 = gallop1*2;							
								} else {
									gallop1 = begin2-begin1-1 - p1;
								}
							} else {
								gallop1 = 1;
							}
							min_gallop--;
						}else{
							min_gallop++;
						}
						
						last_p1 = p1;
						p1 += gallop1;
					}
				}
			}

		} else {
			// merge the vectors from right to left

			p1 = begin2-1;
			p2 = end - begin2;
			last_p1 = p1+1;
			last_p2 = p2+1;

			int i = end;
			while(p2 >= 0){			
				if(p1 >= begin1 && vector[p1] > temp[p2]){
					count2 = 0;

					if(gallop2 > 1){
						p2 = binarySearch(temp, vector[p1], p2, last_p2 - 1);

						if(last_p2 - p2 > 0){
							i -= last_p2 - p2;
							memcpy(vector + i + 1, temp + p2, (last_p2 - p2)*sizeof(int));							
						}

						last_p2 = p2;
						p2--;
						gallop2 = 1;

					}else{
						count1++;
						i -= last_p1 - p1;
						memmove(vector + i + 1, vector + p1, (last_p1 - p1)*sizeof(int));

						if(count1 > 1){
							if(count1 > min_gallop && gallop1 > 0){						
								if(p1 - 2*gallop1 >= begin1){
									gallop1 = gallop1*2;							
								} else {
									gallop1 = p1 - begin1;
								}
							} else {
								gallop1 = 1;
							}
							min_gallop--;
						}else{
							min_gallop++;
						}
						
						last_p1 = p1;
						p1 -= gallop1;
					}
					
				}else{
					count1 = 0;

					if(gallop1 > 1){
						p1 = binarySearch(vector, temp[p2], p1, last_p1 - 1);

						if(last_p1 - p1 > 0){
							i -= last_p1 - p1;
							memmove(vector + i + 1, vector + p1, (last_p1 - p1)*sizeof(int));
						}

						last_p1 = p1;
						p1--;
						gallop1 = 1;

					} else {
						count2++;

						i -= last_p2 - p2;
						memcpy(vector + i + 1, temp + p2, (last_p2 - p2)*sizeof(int));

						if(count2 > 1){
							if(count2 > min_gallop && gallop2 > 0){						
								if(p2 - 2*gallop2 >= 0){
									gallop2 = gallop2*2;
								} else {
									gallop2 = p2;
								}
							} else {
								gallop2 = 1;
							}
							min_gallop--;
						}else{
							min_gallop++;
						}
						
						last_p2 = p2;
						p2 -= gallop2;
					}				
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