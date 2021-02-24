#include "../headers/tim.h"

int GetMinrun (int n) {
    int r = 0;

    while (n >= 64) {
        r = (r | n) & 1;
        n++;
    }

    return n + r;
}

void timSort(int *vector, int length){

}