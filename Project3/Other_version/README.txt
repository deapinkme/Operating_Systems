README
======
A. This package includes the following files:

|-- Starter.c [as requested in assignment]
|-- Fibb.c [as requested in assignment]
|-- Prime.c [as requested in assignment; in addition Prime only checks odd numbers for primes]
|-- Total.c [as requested in assignment]
|-- input.txt [sample input.txt as indicated in assignment]
|-- run.sh [shell script; in case it is run in Replit]
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

systemprompt> ./Starter input.txt

C. Answer the following questions (1 point each, select/type the right answer).

1. Name the function that is used to create a pipe. Which ends denotes the read and the write ends of a pipe? 
        WEXITSTATUS returns 8 of the least significant bits.

2. Name the function used to map files or devices in to memory?
        #include <sys/wait.h>

3. Name the function used to open a shared memory object? What does it return?
        shm_open(), which returns a file descriptor for the shared memory object that is the lowest numbered file descriptor not currently open for that process.