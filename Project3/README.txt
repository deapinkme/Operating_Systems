README
======
A. This package includes the following files:

|-- CharacterReader.c [as requested in assignment]
|-- Starter.c [as requested in assignment]
|-- Fibb.c [as requested in assignment]
|-- Prime.c [as requested in assignment; in addition Prime only checks odd numbers for primes]
|-- Total.c [as requested in assignment]
|-- input1.txt [sample input1.txt as indicated in assignment]
|-- input2.txt [sample input2.txt as indicated in assignment]
|-- Makefile [build script]
|-- run.sh [build and run script which alleviates replit.com problem with "Makefile"]
|-- README.txt [This file]


B. Use your designed makefile:
To compile the code and build the executable using the command 
systemprompt>  make
// or make Starter

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming we use input.txt) 

systemprompt> ./Starter input1.txt
  or
systemprompt> ./Starter input2.txt

Since replit.com has a problem with "make" to run everything use my script:
systemprompt> ./run.sh

C. Answer the following questions

1. Name the function that is used to create a pipe. Which ends denotes the read and the write
ends of a pipe? (2 points)
  pipe(int thePipe[2]) is used to create a pipe. When you are reading it is the first element (index 0) of the pipe or thePipe[0], while when
  you are writing it is the second element (index 1) of the pipe or thePipe[1].

2. Name the function used to map files or devices in to memory? (1 point)
  mmap is used to map files or devices in to memory.

3. Name the function used to open a shared memory object? What does it return? (2 points)
  shm_open(), which returns a file descriptor.