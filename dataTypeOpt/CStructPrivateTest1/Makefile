CC=gcc
CFLAGS=-w

all:
	make test1	

test1:obj.o test1.o
	$(CC) obj.o test1.o -o test1

.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<
	
clean :
	rm -rf *.o
	rm -rf test1
    
    
