#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int fibonacci(int n) {
  int ret = 0;
  int t1 = 0, t2 = 1, nth = 0; // Initalize t1 and t2

  for (int i = 1; i <= n; i++) {
    if(i == 1) { // this is the first fibonacci number
        printf("%d, ", t1);
    } else if(i == 2) { // this is the second fibonacci number
        printf("%d, ", t2);
    } else {
      // this loops and updates the nth and the two preceeding numbers
      nth = t1 + t2;
      t1 = t2;
      t2 = nth;
      
      printf("%d, ", nth);
      ret = nth;
    }
  }
  return ret;
}

int main(int argc, char *argv[]) {
  // from Starter
  char line[256];

  if (argc != 3) {
    printf("Usage: Fibb <smname> <num>");
    exit(1);
  }

  int num = atoi(argv[2]);
  
  printf("Fibb [%d]: Number of terms in fibonacci series is %d \n", getpid(), num);
  printf("Fibb [%d]: The first %d numbers of the Fibonacci series are: \n", getpid(), num);
  int ret = fibonacci(num); // returns the nth fibb number
  printf("\n");

  // Write result into shared memory
  int shm;
  shm = shm_open(argv[1], O_RDWR, 0666);
  int *result = mmap(0, 32, PROT_WRITE, MAP_SHARED, shm, 0);
  memcpy((void *)result, (void *)&ret, sizeof(ret));
  shm_unlink(argv[1]);

  return 0;
}