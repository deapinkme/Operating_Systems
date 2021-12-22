#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int isPrime(int number) {
  // this checks if the number is prime
  int i;
  for (i=2; i*i<=number; i++) {
    if (number % i == 0) return 0;
  }
  return 1;
}

int primeNth(int n) {
  int counter = 0;
  int i;
  printf("%d, ", 2);
  if(n == 1) return 2;
  for(i=3; true; i+=2 /* improvement: skip evens */) { // iterates over all numbers, see exit condition inside (will not be an infinite loop)
    if(isPrime(i)) { // finds number that is prime
      counter++; // increment counter
      printf("%d, ", i);
      if(counter == (n-1)) return i; // if completed return nth prime number
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  // from Starter
  char line[256];

  if (argc != 3) {
    printf("Usage: Prime <smname> <num> \n");
    exit(1);
  }
  
  int num = atoi(argv[2]);

  printf("Prime [%d]: First %d prime numbers are: \n", getpid(), num);
  int ret = primeNth(num);
  printf("\n");

  // Write result into shared memory
  int shm;
  shm = shm_open(argv[1], O_RDWR, 0666);
  int *result = mmap(0, 32, PROT_WRITE, MAP_SHARED, shm, 0);
  memcpy(result, &ret, sizeof(ret));
  shm_unlink(argv[1]);

  return 0;
}