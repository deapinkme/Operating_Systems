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

// Forks a child and waits for it to finish
int runCharacterReader(const char *arg) {
  // Create the pipe
  int thePipe[2];
  if (pipe(thePipe)) {
    fprintf (stderr, "Pipe creation failed.\n");
    exit(1);
  }

  const char *command = "./CharacterReader";
  pid_t starter_pid = getpid();
  pid_t pid = fork();
  if (pid < 0) { // Can happen in main Starter process if OS is out of resources
    printf("fork() failed");
    exit(1);
  } else if (0 == pid) { // Child
    close(thePipe[0]);
    char buf[20]; // assuming 20 characters are enough for a text representation of integer
    sprintf(buf, "%d", thePipe[1]);
    execlp(command, command, arg, buf, NULL); // Could check for failure -> return -1; overkill for homework
  } else { // Main Starter process
    int status;
    close(thePipe[1]);
    pid_t childpid = wait(&status);

    // Read the sum from the pipe
    FILE *stream;
    int c;
    char buf[20]; // assuming 20 characters are enough for a text representation of integer
    int i = 0;
    stream = fdopen(thePipe[0], "r");
    while ((c = fgetc(stream)) != EOF)
      buf[i++]= (char)c;
    fclose(stream);

    return atoi(buf);
  }
}

// Fork a new process; do not wait for completion; return the PID of the forked child process
pid_t forknew(const char *command, const char *shmName, const int sum) {
  char sumBuf[20];
  sprintf(sumBuf, "%d", sum);
  pid_t starter_pid = getpid();
  pid_t pid = fork();
  if (pid < 0) { // Can happen in main Starter process if OS is out of resources
    printf("fork() failed");
    exit(1);
  } else if (0 == pid) { // Child
    execlp(command, command, shmName, sumBuf, NULL); // Could check for failure -> return -1; overkill for homework
  } else { // Main Starter process
    return pid;
  }

}

int main(int argc, char *argv[])
{
  const char *shmNameFibb = "SHM_Fibb";
  const char *shmNamePrime = "SHM_Prime";
  const char *shmNameTotal = "SHM_Total";

  char line[256];

  if (argc != 2) {
    printf("Usage: Starter <file> \n");
    exit(1);
  }

  int sum = runCharacterReader(argv[1]);
  printf("Starter[%d]: contents read from the read pipe: %d\n", getpid(), sum);

  // Create shared memory
  int shmFibb = shm_open(shmNameFibb, O_CREAT | O_RDWR, 0666);
  printf("Starter[%d]: Created shared memory %s with FD: %d\n", getpid(), shmNameFibb, shmFibb);
  int shmPrime = shm_open(shmNamePrime, O_CREAT | O_RDWR, 0666);
  printf("Starter[%d]: Created shared memory %s with FD: %d\n", getpid(), shmNamePrime, shmPrime);
  int shmTotal = shm_open(shmNameTotal, O_CREAT | O_RDWR, 0666);
  printf("Starter[%d]: Created shared memory %s with FD: %d\n", getpid(), shmNameTotal, shmTotal);
  ftruncate(shmFibb, 32);
  ftruncate(shmPrime, 32);
  ftruncate(shmTotal, 32);


  // Run each of Fibb/Prime/Total
  // BTW, I am not using the returned PIDs, but here they are
  pid_t pidFibb = forknew("./Fibb", shmNameFibb, sum);
  pid_t pidPrime = forknew("./Prime", shmNamePrime, sum);
  pid_t pidTotal = forknew("./Total", shmNameTotal, sum);

  // Wait for completion
  int status;
  wait(&status); // Ignore the return value - does not matter which child finished
  wait(&status); // Ignore the return value - does not matter which child finished
  wait(&status); // Ignore the return value - does not matter which child finished

  // Read results from shared memory
  int *lastFibb = (int *)mmap(0, 32, PROT_READ, MAP_SHARED, shmFibb, 0);
  int *lastPrime = (int *)mmap(0, 32, PROT_READ, MAP_SHARED, shmPrime, 0);
  int *lastTotal = (int *)mmap(0, 32, PROT_READ, MAP_SHARED, shmTotal, 0);

  printf("Starter[%d]: Fibb last number:  %d\n", getpid(), *lastFibb);
  printf("Starter[%d]: Prime last number:  %d\n", getpid(), *lastPrime);
  printf("Starter[%d]: Total last number:  %d\n", getpid(), *lastTotal);

  shm_unlink(shmNameFibb);
  shm_unlink(shmNamePrime);
  shm_unlink(shmNameTotal);

  return 0;
}