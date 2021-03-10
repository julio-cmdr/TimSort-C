#include "../headers/tim.h"
#include "../headers/inserction.h"
#include "../headers/merge.h"

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

void timSort(int *vector, int length){
    int n, n_remaining = length;
    int minRun = getMinrun(length);
 
    // allocating a vector of runs
    Runs runs;
    runs.runs = (Run*)malloc(sizeof(Run)*(int)ceil((float)length/minRun));
    runs.n_runs = 0;


    while(n_remaining > 0){
        Run tmp_run;
        tmp_run.vector = vector + length - n_remaining;
        
        tmp_run.length = count_run(tmp_run.vector, n_remaining);

        // if the vector is already sorted it doesn't need to perform binary insertion
        if(tmp_run.length != length){

            if(tmp_run.length < minRun){
                if(minRun <= n_remaining)
                    tmp_run.length = minRun;
                else
                    tmp_run.length = n_remaining;
            }
        
            binary_inserction(tmp_run.vector, tmp_run.length);
        }

        n_remaining -= tmp_run.length;

        runs.runs[runs.n_runs] = tmp_run;
        runs.n_runs++;
    }
    
    int removedRun;

    while(runs.n_runs > 1){
        if(runs.n_runs > 2){
            if(runs.runs[0].length > (runs.runs[1].length + runs.runs[2].length) && 
                runs.runs[1].length > runs.runs[2].length) {
                
                // merge run0 and run1
                optimized_merge(runs.runs[0].vector, 0, runs.runs[0].length, runs.runs[0].length + runs.runs[1].length-1);    
                runs.runs[0].length = runs.runs[0].length + runs.runs[1].length;
                    
                // remove run1 from the vector
                memmove(runs.runs + 1, runs.runs + 2, (runs.n_runs-2)*sizeof(Run));
                
            } else {
                // merge run1 and run2
                optimized_merge(runs.runs[1].vector, 0, runs.runs[1].length, runs.runs[1].length + runs.runs[2].length-1);    
                runs.runs[1].length = runs.runs[1].length + runs.runs[2].length;
                
                if(runs.n_runs > 3){
                    // remove run2 from the vector
                    memmove(runs.runs + 2, runs.runs + 3, (runs.n_runs-3)*sizeof(Run));
                }

            }
        }else{
            // merge run0 and run1
            optimized_merge(runs.runs[0].vector, 0, runs.runs[0].length, runs.runs[0].length + runs.runs[1].length-1);    
            runs.runs[0].length = runs.runs[0].length + runs.runs[1].length;
        }

        runs.n_runs--;
    }

    if(length != runs.runs[0].length){
        printf("TimSort Error %d %d\n", length, runs.runs[0].length);
    }

    free(runs.runs);
}