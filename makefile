CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = Question2 Question3 
OBJFILES = Question2.o Question3.o 
all: $(TARGET)
Question1: Question1.c
	$(CC) $(CFLAGS) -o Question1 Question1.c $(LDFLAGS)
Question2: Question2.c
	$(CC) $(CFLAGS) -o Question2 Question2.c $(LDFLAGS)

runq1: Question1
	./Question1 sample4_in.txt
runq2: Question2
	./Question2
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 