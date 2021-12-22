#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// Forks a child and waits for it to finish
int run(const char *command, const char *arg) {
  pid_t starter_pid = getpid();
  pid_t pid = fork();
  if (pid < 0) { // Can happen in main Starter process if OS is out of resources
    printf("fork() failed");
    exit(1);
  } else if (0 == pid) { // Child
    // printf("Starter [%d]: Forked process with ID %d. \n", starter_pid, getpid()); // Not required in homework
    execlp(command, command, arg, NULL); // Could check for failure -> return -1; overkill for homework
  } else { // Main Starter process
    int status;
    printf("Starter [%d]: Forked process with ID %d. \n", starter_pid, pid); // To print this from child uncomment above
    printf("Starter [%d]: Waiting for process [%d]. \n", starter_pid, pid);
    pid_t childpid = wait(&status);
    printf("Starter: Child process %d returned %d. \n", childpid, WEXITSTATUS(status)); // Only using lower 8 bits of result
    return WEXITSTATUS(status); // For simplicity only using lower 8 bits of result
  }
}

void process(const char *arg) {
  // Running them sequentially
  int f = run("./Fibb", arg);
  int p = run("./Prime", arg);
  int s = run("./Total", arg);
  // Summary - for each line in input
  printf("Fibb: %d \n", f);
  printf("Prime: %d \n", p);
  printf("Total count: %d \n", s);
}

int main(int argc, char *argv[])
{
  char line[256];

  if (argc != 2) {
    printf("Usage: Starter <file> \n");
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  if (NULL == f) {
    printf("Error opening file. \n");
    exit(1);
  }
  
  int i = 1;
  while( fgets(line,256,f) ) {
    int lastchar = strlen(line) - 1;
    if (line[lastchar] == '\n') line[lastchar] = '\0'; // Remove the '\n' char at the end

    process(line);
  }

  return 0;
}