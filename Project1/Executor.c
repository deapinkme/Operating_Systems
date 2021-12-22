#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // malloc, free

#include "Executor.h"

int isVowel(char c) {
    return NULL != strchr("AEOIU", c); //Assume Y is not a vowel
}

int generator(int lb, int ubExclusive, int rand) {
    return ((rand % (ubExclusive - lb) + lb));
}

int get_iteration_no(int rand) {
    return generator(50, 100, rand);
}

int get_arr_size(int rand) {
    return generator(100, 150, rand);
}

char get_arr_val(int rand) {
    return (char)generator(65, 91, rand);
}

float ratio(char *arr, int size, int *maxCountPointer) {
    int vowels = 0;

    for (int i=0; i<size; i++) {
        if (isVowel(arr[i])) vowels++;
    }

    if (*maxCountPointer < vowels) *maxCountPointer = vowels;

    if (vowels == size) return -1.0; // infinite
    else return ((float)vowels) / ((float)(size-vowels));
}

double get_running_ratio() {
    int maxCount = 0;
    int maxIteration = 0;
    
    int times = get_iteration_no(rand());
    printf("[Executor]: Number of iterations is %d\n", times);
    float ratioSum = 0.0;
    for (int t=0; t<times; t++) {
        int s = get_arr_size(rand());
        char* arr = malloc(s);
        for (int c=0; c<s; c++) {
            arr[c] = get_arr_val(rand());
        }

        int maxCountCopy = maxCount;
        double thisRatio = ratio(arr, s, &maxCountCopy);

        if (ratioSum < 0.0 || thisRatio < 0.0) ratioSum = -1.0; // infinite
        else ratioSum += thisRatio;
        
        if (maxCountCopy > maxCount) {
            maxCount = maxCountCopy;
            maxIteration = t;
        }
        
        free(arr); // comment this line out to leak memory
    }
    printf("[Executor]: Iteration with maximum vowel count is %d\n", maxIteration+1); // because maxIteration is 0-based

    return ratioSum / (float)times;
}