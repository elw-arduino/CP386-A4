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

void allocate(char pid[5], int requested) {
	struct Block *temp = head;
	int smallestSize = 999999;
	struct Block *smallestBlock = NULL;
	while(temp != NULL) {
		if(strcmp(temp->pid,"") == 0 && temp->size < smallestSize && temp->size >= requested) {
			smallestSize = temp->size; // Update the size
			smallestBlock = temp; // Maintain reference to the block for later
		}
		temp = temp->next;
	}
	if(smallestBlock != NULL) {
		// Free block found
		int free = smallestBlock->size - requested;
		smallestBlock->size = requested;
		strcpy(smallestBlock->pid,pid);
		if(free > 0) {
			// Block is bigger than requested
			struct Block *newBlock = (struct Block *)malloc(sizeof(struct Block));
			newBlock->end_address = smallestBlock->end_address; // Copy End address
			smallestBlock->end_address = smallestBlock->start_address + requested; // Update end address of old block
			newBlock->start_address = smallestBlock->end_address + 1; // Set start address of new block
			newBlock->size = free;
			newBlock->next = smallestBlock->next; // Maintain reference to next block in list
			smallestBlock->next = newBlock; // Insert new block
		}
		printf("Successfully allocated %i to process %s",requested,pid);
	}
	else {
		// No room
		printf("No hole of sufficient size");
	}
}

int main(int argc, char *argv[]) {
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
}