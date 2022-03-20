/*
Author:  Brian Ha - 190376250 - haxx6250@mylaurier.ca - Github: https://github.com/Reprodux 
         Eric Wildfong, 190559940 - wild9940@mylaurier.ca - Github: https://github.com/elw-arduino
Repository:
         https://github.com/elw-arduino/CP386-A4

 -------------------------------------
 File:    Question1.c
 Description: Example of Banker's Algorithm
 Version  3/18/2022
 -------------------------------------
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>
#include <stdbool.h>
#include <ctype.h> //For run_cmd



int rows = 0; // number of customers
int columns = 0;  // number of resources

int readfile(char *fileName);


int customers_on_file(char *fname){
        
        FILE *file = fopen(fname,"r");
        int count = 0;
        struct stat st;
	fstat(fileno(file), &st);
	char* content = (char*)malloc(((int)st.st_size+1)* sizeof(char));	
	while(!feof(file))
	{
		char line[100];
                count += 1;
		if(fgets(line,100,file)!=NULL)
		{
			strncat(content,line,strlen(line));
                        
		}
	}
        
        return count;
}

int resource_num(char *fname){
        
        int rescnum = 0;
        char *token;
        FILE *file = fopen(fname, "r");
        if(!feof(file)){
                char line[100];
                
                if(fgets(line,100,file)!=NULL)
		{
                     token = strtok(line, ",");
                     while(token != NULL){
                             rescnum += 1;
                             token = strtok(NULL, ",");
                     }   
                       
		}
        }
        fclose(file);
        return rescnum;
}


void setup_allocation(int allocation[rows][columns], int rows, int columns){
        
        for (int x = 0; x < rows; x++){
                for (int y = 0; y < columns; y++)
                {
                    allocation[x][y] = 0;
                    
                }
        }
        
}

void setup_need(int need[rows][columns], int allocation[rows][columns], int max[rows][columns], int rows, int columns){
        
        for (int x = 0; x < rows; x++){
                for (int y = 0; y < columns; y++){
                        need[x][y] = max[x][y] - allocation[x][y];
                }
                
        }

}


int main(int argc, char *argv[]){
        int columns = resource_num("sample4_in.txt"); //gets the number of different resources, or the amount of columns in later matrix
        int rows = customers_on_file("sample4_in.txt"); //looks through sample file to determine number of customers on file
        

        if(argc < columns + 1){
                printf("lack of command line args\n");
                return 0;
        }
        if(argc > columns + 1){
                printf("excess amount of command line args\n");
                return 0;
        }
        for (int i = 1; i < argc; i++)
        {
            if (isalpha(*argv[i]) != 0)
            {
                printf("non-digit input detected\n");
                return 0;
            }
        }

        //initalize rest of program, sets up matrices
        printf("Number of Customers: %d\n", rows);
       
        printf("Cuurently Available resources: ");
        for (int i = 1; i < columns; i++){
                printf("%s ", argv[i]);
        }
        printf("%s\n", argv[columns]);


        //MAX matrix setup
        printf("Maximum resources from file:\n");
        int max[rows][columns];
        FILE *file = fopen("sample4_in.txt", "r");
        char *token;
        int x = 0;
        while(!feof(file))
	{
		char line[100];
                
		if(fgets(line,100,file)!=NULL)
		{
			printf("%s",line);
                        token = strtok(line, ",");
                        int y = 0;
                        while(token != NULL){
                                max[x][y] = atoi(token);
                                token = strtok(NULL,",");
                                y += 1;
                        }
                                
		}
                x += 1;
	}
        fclose(file);
        printf("\n");
        

        //AVAILABLE setup
        int *available = (int *)malloc(columns * sizeof(int)); 
                for (int i = 0; i < columns; i++){
                        available[i] = atoi(argv[i + 1]); // populates array with the values in command line
                }
       
        
        //ALLOCATION matrix setup
        int allocation[rows][columns];
        setup_allocation(allocation,rows,columns);

        //NEED matrix setup
        int need[rows][columns];
        setup_need(need, allocation, max,rows,columns);
        
        
        int *ptr_available = &available[0];
        int *ptr_max = &max[0][0];
        int *ptr_allocation = &allocation[0][0];
        int *ptr_need = &need[0][0];
        


        

        
        
}