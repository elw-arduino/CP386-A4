/*
Author:  Brian Ha - 190376250 - haxx6250@mylaurier.ca - Github: https://github.com/Reprodux 
         Eric Wildfong, 190559940 - wild9940@mylaurier.ca - Github: https://github.com/elw-arduino
Repository:
         https://github.com/elw-arduino/CP386-A4

 -------------------------------------
 File:    Question2.c
 Description: Example of Best-Fit Algo
 Version  3/29/2022
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
    char pid[5]; // Process id
};

struct Block *head;

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Missing Size\n");
		return 1;
	}
	int size = atoi(argv[1]);
	if(size <= 0) {
		printf("Size must be greater than 0\n");
		return 1;
	}
	head = (struct Block *)malloc(sizeof(struct Block));
	head->size = size;
	head->start_address = 0;
	head->end_address = size-1;
	printf("%i\n",strcmp(head->pid,"") == 0);
}