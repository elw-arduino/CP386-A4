/*
Author:  Brian Ha - 190376250 - haxx6250@mylaurier.ca - Github: https://github.com/Reprodux 
         Eric Wildfong, 190559940 - wild9940@mylaurier.ca - Github: https://github.com/elw-arduino
Repository:
         https://github.com/elw-arduino/CP386-A4

 -------------------------------------
 File:    Question2.c
 Description: Example of Best-Fit Algo
 Version  3/31/2022
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct Block
{
    int size; //size of block
    int start_address;
    int end_address;
    struct Block *next;
    char pid[5]; // Process id
};

struct Block *head;
int globalMax;

void allocate(char pid[5], int requested) {
    
	if(requested <= 0) {
		printf("Size must be positive\n");
		return;
	}
	struct Block *temp = head;
	int smallestSize = globalMax+1;
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
			smallestBlock->end_address = smallestBlock->start_address + requested - 1; // Update end address of old block
			newBlock->start_address = smallestBlock->end_address + 1; // Set start address of new block
			newBlock->size = free;
			newBlock->next = smallestBlock->next; // Maintain reference to next block in list
			smallestBlock->next = newBlock; // Insert new block
		}
		printf("Successfully allocated %i to process %s\n",requested,pid);
	}
	else {
		// No room
		printf("No hole of sufficient size\n");
	}
}

void freeMemory(char pid[5]) {
	struct Block *previous = NULL;
	struct Block *temp = head;
	printf("releasing memory for process %s\n",pid);
	while(temp != NULL) {
		if(strcmp(temp->pid,pid) == 0 ) {
			// Block allocated to the process
			strcpy(temp->pid,""); // Free the block
		}
		if(previous != NULL && strcmp(previous->pid,"") == 0 && strcmp(temp->pid,"") == 0 ) {
			// Previous block is free so condense them
			previous->end_address = temp->end_address;
			previous->size += temp->size; // Update size
			previous->next = temp->next; // Pop 2nd block from list
			free(temp); // Free the 2nd block
			temp = previous->next; // Look at next block
		}
		else {
			previous = temp; // Update reference to previous block
			temp = temp->next; // Look at next block
		}
	}
	printf("Successfully released memory for process %s\n",pid);
}

void status() {
	int freeMem = 0;
	char freeBlocks[1000] = "";
	int usedMem = 0;
	char usedBlocks[1000] = "";
	
	struct Block *temp = head;
	while(temp != NULL) {
		if(strcmp(temp->pid,"") == 0 ) {
			// Block is Free
			char str[200];
			sprintf(str,"Address [%i:%i] len = %i\n",temp->start_address,temp->end_address,temp->size);
			freeMem += temp->size;
			strcat(freeBlocks,str);
		}
		else {
			// Block is used
			char str[200];
			sprintf(str,"Address [%i:%i] Process %s\n",temp->start_address,temp->end_address,temp->pid);
			usedMem += temp->size;
			strcat(usedBlocks,str);
		}
		temp = temp->next;
	}
	printf("Partitions [Allocated memory = %i]:\n",usedMem);
	printf("%s\n",usedBlocks);
	printf("Holes [Free memory = %i]:\n",freeMem);
	printf("%s",freeBlocks);
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
	globalMax = size;
	head = (struct Block *)malloc(sizeof(struct Block));
	head->size = size;
	head->start_address = 0;
	head->end_address = size-1;
	printf("Allocated %i bytes of memory\n",size);
	
	char cmd[100];
	bool running = true;
	while (running){
		printf("command>");
		fgets(cmd, 100, stdin);
		cmd[strcspn(cmd, "\r\n")] = 0; // Remove trailing newline
		char *token = strtok(cmd, " "); //removes all white spaces and retrieves only the command
		char *args[4];
		token = strtok(NULL, " ");
		int j = 0;
		while (token != NULL){
            args[j] = token;
			token = strtok(NULL, " ");
            //printf("%d %s\n",j,args[j]);
			j += 1;
		}
		//Remove Caps
		for (char *cmd_lower = cmd; *cmd_lower; cmd_lower++){
			*cmd_lower = tolower(*cmd_lower);
		}
        
		//displays the current status of the processes
		if(strstr(cmd,"status")){
			status();
		}
		else if (strstr(cmd, "rq") != NULL) {
            //printf("%s\n",args[2]);
            if(strcmp(args[2],"b") == 0 || strcmp(args[2],"B") == 0){
                allocate(args[0],atoi(args[1]));
            }
            else {
				printf("Missing Algorithm Specifier\n");
			}
		}
		else if (strstr(cmd, "rl") != NULL) {
			freeMemory(args[0]);
		}
		else if (strstr(cmd, "exit") != NULL){
			printf("Exiting program\n");
			running= false;
		}
		else{
			printf("Invalid input, use one of RQ, RL, Status, Exit\n");
		}
	}
	return 0;
}