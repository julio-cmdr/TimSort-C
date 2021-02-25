#include "../headers/tim.h"
#include "../headers/inserction.h"

int getMinrun(int n){
    int r = 0;

    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }

    return n + r;
}

void reverse_vector(int *vector, int length){
    int aux;
    for(int i = 0; i < length/2; i++){
        aux = vector[i];
        vector[i] = vector[length -1 -i];
        vector[length -1 -i] = aux;
    }
}

// this function looks for an ordered subvector at beginning of the next run
// if the sub-vector is ordered in a descending way, it will be reversed
int count_run(int *vector, int length){
    bool descending = false;
    int n = 1;

    if(vector[n-1] > vector[n]){
        descending = true;
    }
    n++;
    
    if(descending){
        while(n < length && vector[n-1] >= vector[n]){
            n++;
        }

        reverse_vector(vector, n);

    } else {
        while(n < length && vector[n] >= vector[n-1]){
            n++;
        }
    }

    return n;
}

Runs timSort(int *vector, int length){
    int n, n_remaining = length;
    int minRun = getMinrun(length);

    printf("\nMinRun: %d\n", minRun);
    
    // allocating a vector of runs
    Runs runs;
    runs.runs = (Run*)malloc(sizeof(Run)*(int)ceil((float)length/minRun));
    runs.n_runs = 0;


    while(n_remaining > 0){
        Run tmp_run;
        tmp_run.vector = vector + length - n_remaining;
        
        tmp_run.length = count_run(tmp_run.vector, n_remaining);

        if(tmp_run.length < minRun){
            if(minRun <= n_remaining)
                tmp_run.length = minRun;
            else
                tmp_run.length = n_remaining;
        }

        n_remaining -= tmp_run.length;

        inserction(tmp_run.vector, tmp_run.length);

        runs.runs[runs.n_runs] = tmp_run;
        runs.n_runs++;
    }

    return runs;
}