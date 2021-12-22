#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // from Starter
  char line[256];

  if (argc != 3) {
    printf("Usage: Total <smname> <num> \n");
    exit(1);
  }

  int num = atoi(argv[2]);
  int sum = 0;

  for (int i=1; i<=num; i++) {
    sum += i; // add each consecutive number < num to the sum
  }
  printf("Total [%d]: Sum = %d \n", getpid(), sum);

  // Write result into shared memory
  int shm;
  shm = shm_open(argv[1], O_RDWR, 0666);
  int *result = mmap(0, 32, PROT_WRITE, MAP_SHARED, shm, 0);
  memcpy(result, &sum, sizeof(sum));
  shm_unlink(argv[1]);

  return 0;
}