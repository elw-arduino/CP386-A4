/*
Author:  Brian Ha - 190376250 - haxx6250@mylaurier.ca - Github: https://github.com/Reprodux 
         Eric Wildfong, 190559940 - wild9940@mylaurier.ca - Github: https://github.com/elw-arduino
Repository:
         https://github.com/elw-arduino/CP386-A4

 -------------------------------------
 File:    Question1.c
 Description: Example of Banker's Algorithm
 Version  3/24/2022
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



int rows; // number of customers
int columns;  // number of resources
int *ptr_available;  // represents the number of available resources of each type
int *ptr_max;        // matrix representing max num of instances of each resc process can request (m x n)
int *ptr_allocation; // matrix representing the num of resources of each type currently allocated to process (m x n)
int *ptr_need;       // represents the remaining resource needs of each process (m x n)
int *temp_avail; 
int *temp_alloc; 
int *temp_need; 

typedef struct thread{ //represents a single thread, you can add more members if required

	char tid[4]; //id of the thread as read from file
	unsigned int startTime;
	int state;
	pthread_t handle;
	int retVal;
} Thread;

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




// deals with determining resource requesting
int valid_resc_request(int args[]){
        bool valid;
        bool safe;

        int customer= args[0];     // first number in the command represents the customer number
        int request[columns];             // resources from the command line
        //temp ptrs in the case that upcoming changes lead to an unsafe state
        temp_avail = ptr_available; 
        temp_alloc = ptr_allocation; 
        temp_need = ptr_need;   

        //gets the resources from customer
        for (int i = 0; i < columns; i++){
                request[i] = args[i + 1];
        }

        for (int i = 0; i < columns && valid; i++){
                valid = request[i] <= *(temp_need + (customer * columns + i));
        }

        
        //checks if resource exceeds max
        if (valid == true)
        {
                for (int i = 0; i < columns && valid; i++){
                //request[i] recived from available[i]
                valid = request[i] <= *(temp_need + i); // request[i <= available[i]
                }
                if (valid == true){
                        for (int i = 0; i < columns; i++){
                                temp_avail[i] -= request[i];
                                *((temp_alloc + customer * columns) + i) += request[i];

                                *((temp_need + customer * columns) + i) -= request[i];

                                
                        }    
                        //code that determines the safe state
                        int work[columns];
                        for (int i = 0; i < columns; i++) {
                                work[i] = *(temp_avail + i); 
                        }
                    

                        bool finish[columns];
                        for (int i = 0; i < columns; i++){
                                finish[i] = false;
                        }

                        

                        int index = 0;
                        while (index < rows){
                                bool resc = false;
                                for (int i = 0; i < rows; i++){
                                        if (finish[i] == false){
                                                int j = 0;
                                                for (j = 0; j < columns; j++){
                                                if (*((temp_need + i * columns) + j) > work[j]){
                                                        break;
                                                }
                                                }       
                                                if (j == columns){
                                                for (int y = 0; y < columns; y++){
                                                        work[y] += *((temp_alloc + i * columns) + y);
                                                }
                                                finish[i] = true;
                                                resc = true;
                                                index++;
                                                
                                                }
                                        }       
                                }
                                        if (resc == false){
                                                printf("System is not in safe state\n");
                                                safe = false;
                                        }
                        }
                        
                        if(safe){
                                printf("State is safe, and request is satisfied:\n");
                                //confirm changes
                                ptr_available = temp_avail;
                                ptr_allocation = temp_alloc;
                                ptr_need = temp_need;
                                
                                return 1;
                        }
                        //danger(probably)
                        else{
                                return 0; 
                        }
                }
                else{
                return 0; // not enough resources
                }
        }
        else{
                return 0; 
        }
}



void *execute_thread(){
        char order[100];
        int rescs[columns];
        int process[10];
        int index = 0;
        int current;
        printf("Safe Sequence is: ");
        fgets(order, 100, stdin);
        printf("\n");
        char *token = strtok(order, " ");

        while(token != NULL){
                process[index] = atoi(token);
                token = strtok(NULL, " ");
                index += 1;

        }

        for (int i = 0; i < index; i++){
                printf("--> Customer/Thread %d\n", process[i]);
                printf("\tAllocated resources: ");
                for (int x = 0; x < columns; x++){
                        current =  ptr_allocation[process[i] * columns + x];
                        printf("%d ", current); 
                        rescs[x] = current;
                }
        printf("\n\tNeeded: ");
        for (int r = 0; r < columns; r++){
                current = ptr_need[process[i] * columns + r];
                printf("%d ", current);
        }
        printf("\n\tAvailable: ");
        for (int r = 0; r < columns; r++){
                printf("%d ", ptr_available[r]);
        }
        printf("\n");

        

        printf("\tThread has started\n");
       
        printf("\tThread has finished\n");
       
        printf("\tThread is releasing resources\n");

        for (int w = 0; w < columns; w++)
        {
            ptr_available[w] += rescs[w];
            *((ptr_allocation+ process[i] * columns) + w) -= rescs[w];
            *((ptr_need + process[i] * columns) + w) += rescs[w]; //Resources get released and added back to available

        }
       

        printf("\tNew Available: ");
        for (int r = 0; r < columns; r++){
            printf("%d ", ptr_available[r]);
        }
        printf("\n");

    }
    return NULL;


        
}



//deals with resource releasing
int resc_release(int args[]){
        int i;
        int customer = args[0];
        int rescs[columns];
        bool valid = true;

        for (i = 0; i < columns; i++){
                rescs[i] = args[i + 1];
        }

        //ensures no accidental duplication
        for (i = 0; i < columns; i++){
                if (rescs[i] > *((ptr_allocation + customer * columns) + i)){
                        valid = false;
                }
                if (valid == true){
                        for (i = 0; i < columns; i++){
                        ptr_available[i] += rescs[i];
                        *((ptr_allocation + customer * columns) + i) -= rescs[i];
                        *((ptr_need + customer * columns) + i) += rescs[i]; 

                }
                return 1;
                }
                else{
                return 0; // release not allowed
                }
        }

        return 0;
}


int main(int argc, char *argv[]){
        columns = resource_num("sample4_in.txt"); //gets the number of different resources, or the amount of columns in later matrix
        rows = customers_on_file("sample4_in.txt"); //looks through sample file to determine number of customers on file
        int max[rows][columns];
        int allocation[rows][columns];
        int need[rows][columns];
        if(argc > columns + 1){
                printf("excess amount of command line args\n");
                return 0;
        }
        if(argc < columns + 1){
                printf("lack of command line args\n");
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
        setup_allocation(allocation,rows,columns);

        //NEED matrix setup
        setup_need(need, allocation, max,rows,columns);
        
        
        ptr_available = &available[0];
        ptr_max = &max[0][0];
        ptr_allocation = &allocation[0][0];
        ptr_need = &need[0][0];
        
        
}
