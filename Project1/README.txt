README
======

A. This package includes the following files:

|-- Starter.c [as requested in assignment; in addition I am handling the case with the wrong number of parameters]
|-- Executor.c [as requested in assignment; in addition I am handling when the ratio is infinite]
|-- Executor.h [headers for functions implemented in Executor.c]
|-- Makefile [build script]
|-- noleak.valgrind.output [valgrind output with no memory leak and correct deallocation]
|-- withleak.valgrind.output [valgrind output with a memory leak cause by lack of free()]
|-- README.txt [This file]


B. Use your designed makefile:
To compile the code and build the executable using the command 

systemprompt>  make
// or make Starter

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming seed is 3) 

systemprompt> ./Starter 3

which will run the program and generate the outputs.

To generate the valgrind files (assuming seed is 3)

// In order to get a leak comment out line 65 in Executer.c (free(arr); // comment this line out to leak memory)
systemprompt> valgrind --leak-check=yes ./Starter 3 > withleak.valgrind.output 2>&1

systemprompt> valgrind --leak-check=yes ./Starter 3 > noleak.valgrind.output 2>&1

C. Answer the following questions (1 point each, select/type the right answer).

    1. Malloc allocates memory dynamically on heap? – True
    2. When dynamically allocating an integer array, Malloc takes the number of elements as the input? – False [It takes the number of bytes]
    3. free() is defined inside which header file? – stdlib.h
    4. How many executable(s) are required to be generated by the Makefile for this assignment? – 1
    5. What command is used to call the default target in Makefile? – make