#!/bin/bash -v
gcc -o CharacterReader CharacterReader.c
gcc -o Fibb Fibb.c -lrt
gcc -o Prime Prime.c -lrt
gcc -o Total Total.c -lrt
gcc -o Starter Starter.c -lrt
./Starter input1.txt
./Starter input2.txt