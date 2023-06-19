CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o stack.o student.o
EXEC=prog.exe
RM=rm -rf

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

main.o: main.c stack.h student.h
	$(CC) $(CFLAGS) -c main.c
	 
student.o: student.c stack.h student.h
	$(CC) $(CFLAGS) -c student.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
	
clean:
	$(RM) *.o *.exe
