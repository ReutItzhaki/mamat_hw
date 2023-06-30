CC = gcc
CCLINK = $(CC)
CFLAGS = -g -Wall -std=c99
RM = rm -rf

libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L. 

grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -fPIC -c grades.c 

clean:
	$(RM) *.o libgrades.so
