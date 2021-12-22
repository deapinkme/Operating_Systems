#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // from Starter
  char line[256];

  if (argc != 2) {
    printf("Usage: Total <num> \n");
    exit(1);
  }

  int num = atoi(argv[1]);
  int sum = 0;

  for (int i=1; i<=num; i++) {
    sum += i; // add each consecutive number < num to the sum
  }
  printf("Sum [%d]: Sum = %d \n", getpid(), sum);

  return sum; // returns the sum of numbers
}