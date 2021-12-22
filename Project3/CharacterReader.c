#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char line[256];

  if (argc != 3) {
    printf("Usage: CharacterReader <file> <readpipefdesc>\n");
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  if (NULL == f) {
    printf("Error opening file. \n");
    exit(1);
  }
  
  int sum = 0;
  while( fgets(line,256,f) ) {
    int lastchar = strlen(line) - 1;
    if (line[lastchar] == '\n') line[lastchar] = '\0'; // Remove the '\n' char at the end

    sum += atoi(line);
  }

  // Write the sum into the pipe
  FILE *stream;
  stream = fdopen(atoi(argv[2]), "w");
  fprintf(stream, "%d", sum);
  fclose(stream);

  return 0;
}