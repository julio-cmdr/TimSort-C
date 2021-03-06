#include "../headers/utils.h"

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