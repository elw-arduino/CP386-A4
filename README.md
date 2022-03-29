# CP386-A4

## Introduction and Features
This repository demonstrates the use of 2 algorithms, Banker's Algorithm (demonstrated in Question1.c) and the Best-Fit algorithm (demonstrated in Question2.c)

**Features:**
  - Algorithms have interactive use, with the makefile included for custom test cases and easy compling
  - Demonstrates 2 important OS algorithms
  - Use of Linux with GCC required

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
	./Question2
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
```
*Important to note that running Question1.c using this makefile will use the testcase ``` 10 5 7 8 ```. Edit that if you wish to use your own*

## Screenshots

**Question1.c (Banker's Algorithm)**
- Below will demonstrate output for a set of commands, following those in the sample output seen in the assignment document

When first running the program, with the test case ``` 10 5 7 8 ```:

![](https://i.imgur.com/f0bLFUJ.png)

RQ - request command:

![](https://i.imgur.com/LnRBGDy.png)

Status - view status:

![](https://i.imgur.com/DO0CSj3.png)

Run - Run:

![](https://i.imgur.com/hbwJrLZ.png)

**Question2.c (Best-Fit Algorithm)**


