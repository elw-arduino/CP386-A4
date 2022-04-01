# CP386-A4

## Introduction
This repository demonstrates the use of 2 algorithms, Banker's Algorithm (demonstrated in Question1.c) and the Best-Fit algorithm (demonstrated in Question2.c)

## Features

### Question1.c:

**RQ: Request Resource** - Requests resources

```RQ [int customer_number] [int Resource 1] [int Resource 2] ... [int Resource 4] ```

**RL: Release Resource** - Release resources, data structures updated accordingly

```RL [int customer_number] [int Resource 1] [int Resource 2] ... [int Resource 4] ```

**Status: Status** - Displays status, prints all arrays and matrices used (available, maximum, allocation, and need)

```Status```

**Run: Run** - Executes customers as threads in a safe sequence. Each thread requests the resources it needs, releases them, and lets the next thread in the sequence run.

```Run```

**Exit: Exits Program** - Exits the loop and the program

```Exit```

### Question2.c

**RQ: Request Resource** - Requests resources

```RQ <process number> <size> <B> ``` 

*B refers to best-fit


**RL: Release Resource** - Release memory that has allocated to a process

```RL <process number/name>```

**Status: Status** - Displays status, used for reporting the status of memory is entered

```Status```

**Exit: Exits Program** - Exits the loop and the program

```Exit```


## Makefile

Below is the code in the makefile, it is already included in the repository, but if you wish to make your own:
```
CC = gcc
CFLAGS =  -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = Question1 Question2 
OBJFILES = Question1.o Question2.o 
all: $(TARGET)

Question1: Question1.c
	$(CC) $(CFLAGS) -o Question1 Question1.c $(LDFLAGS)
Question2: Question2.c
	$(CC) $(CFLAGS) -o Question2 Question2.c $(LDFLAGS)

runq1: Question1
	./Question1 10 5 7 8
runq2: Question2
	./Question2 1000000
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
```
*Important to note that running Question1.c using this makefile will use the testcase ``` 10 5 7 8 ```. Edit that if you wish to use your own*
*Important to note that running Question2.c using this makefile will use the testcase ```10000000```. Edit that if you wish to use your own*

- Linux system with GCC complier required to run both files
- To run question1.c with this makefile, enter ``` make runq1 ``` on command line 
- To run question2.c with this makefile, enter ``` make runq2 ``` on command line 

## Screenshots and Tests

### Question1.c (Banker's Algorithm)
- Below will demonstrate output for a set of commands, following those in the sample output seen in the assignment document

When first running the program, with the test case ``` 10 5 7 8 ```:

![](https://i.imgur.com/f0bLFUJ.png)

**RQ** - request command:

![](https://i.imgur.com/LnRBGDy.png)

**Status** - view status:

![](https://i.imgur.com/DO0CSj3.png)

**Run** - Run:

![](https://i.imgur.com/hbwJrLZ.png)

**Exit** - exits program:

![](https://i.imgur.com/XyhuHgj.png)

### Question2.c (Best-Fit Algorithm)
- Below will demonstrate output for a set of commands, following those in the sample output seen in the assignment document

When first running the program, with the test case ``` 1000000 ```:

![](https://i.imgur.com/k7fyL3k.png)

**RQ** - request command:

![](https://i.imgur.com/cdHqW0D.png)

**RL** - release command:

![](https://i.imgur.com/QemHRTj.png)

**Status** - view status:

![](https://i.imgur.com/qYsSnZO.png)

**Exit** - exits program:

![](https://i.imgur.com/rxlG3rn.png)

## Individual Contribution

### Question1.c (Banker's Algorithm)

```int customers_on_file(char *fname) ```  Brian

```void setup_allocation(int allocation[rows][columns], int rows, int columns) ```  Brian 

```void setup_need(int need[rows][columns], int allocation[rows][columns], int max[rows][columns], int rows, int columns)```  Brian

```int valid_resc_request(int args[]) ```  Brian, Eric

```void *execute_thread() ```  Brian, Eric

```int resc_release(int args[]) ```  Brian

```int main(int argc, char *argv[]) ```  Brian, Eric

### Question2.c (Best-Fit Algorithm)

```void allocate(char pid[5], int requested) ``` Eric

```void freeMemory(char pid[5]) ``` Eric

```void status() ``` Eric

```int main(int argc, char *argv[]) ``` Eric, Brian

## About Developers 

- [Brian Ha](https://github.com/Reprodux)
- [Eric Wildfong](https://github.com/elw-arduino) 

## License

This project is licensed under the MIT License.



