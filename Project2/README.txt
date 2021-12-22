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

1. How many of the least significant bits of the status does WEXITSTATUS return?
        WEXITSTATUS returns 8 of the least significant bits.

2. Which header file has to be included to use the WEXITSTATUS?
        #include <sys/wait.h>

3. What is the return value for the fork() in a child process?
        The return in a child process is 0.

4. Give a reason for the fork() to fail?
        Fork can fail if there are a lot of forks running and not enough resources.

5. In the program written by you, are we doing a sequential processing or a concurrent processing with respect to the child processes? Sequential processing is when only one of the child processes is running at one time, and concurrent processing is when more than one child process can be running at the same time.

My program is sequential. This is because I wait for each child to finish before I fork another child with the next calculation.
I could easily make it concurrent if I fork and execlp all 3 calculations before starting to wait for all 3 to finish. In this case I would
have to keep track which process is responsible for which calculation so the results do not get mixed up, as they are not guaranteed to finish
in the same order they are started/forked.

6. Do you Observe any anomalies in the output from child process and the output from parent
process. Provide a reason for that observation. ( 2points )

The WEXITSTATUS result is the lower 8 bits of the program exit value. So, for example if the input line is 100, the 100th prime number is
541. In this case WEXITSTATUS is 541 % (2^8) = 541 % 256 = 29. So the result printed from the Starter program is 29 instead of 541. To
make this better, we should use some kind of inter-process cimmunication, like a pipe or concurrency safe queue.

Note: All calculations are using int values, but Fibonacci series grows very quickly (exponentially - it more than doubles up in each step).
To make this calculation better, we should use large number calculations (represented as strings or something similar). For this homework I ignore this, as it is irellevant to the process forking exercise.

Note 2: When using Replit(online IDE), it converts tabs into spaces, which breaks the Makefile. I am attaching a functioning Makefile, however to run in replit.com, please use my shell script "run.sh". See someone else as well complaining about this at: https://replit.com/talk/ask/Makefile-error/86487 .

Note 3: The output in the hw2.pdf file prints out the summary of the results in Starter only for the last line. I made it print the summary for
each line in "input.txt".