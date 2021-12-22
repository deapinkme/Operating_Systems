#include <stdio.h>
#include <stdlib.h>

#include "Executor.h"

int main( int argc, char * argv [] ) {
    if (argc != 2) {
        fprintf(stderr, "Usage: Starter <seed>\n");
        return -1;
    }
    int seed = atoi(argv[1]);
    
    printf("[Starter]: With seed: %d\n", seed);
    srand(seed);

    double running_ratio = get_running_ratio();
    printf("[Starter]: Running ratio: %f\n", running_ratio);
    
    return 0;
}