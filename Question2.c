/*
Author:  Brian Ha - 190376250 - haxx6250@mylaurier.ca - Github: https://github.com/Reprodux 
         Eric Wildfong, 190559940 - wild9940@mylaurier.ca - Github: https://github.com/elw-arduino
Repository:
         https://github.com/elw-arduino/CP386-A4

 -------------------------------------
 File:    Question2.c
 Description: Example of Best-Fit Algo
 Version  3/24/2022
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

struct Block
{
    int size; //size of block
    int start_address;
    int end_address;
    struct Block *next;
    char process_id[5];
};

struct Block *head;

int main(int argc, char *argv[]){
	
}