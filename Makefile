CC=gcc
CFLAGS=-g3 -std=c99 -Wall -pedantic
VALGRIND=valgrind -q --tool=memcheck --leak-check=yes --error-exitcode=1

tack: hash.o tack.o stack.o data.o
	$(CC) $(CFLAGs) -g3 -o $@ $^

run: tack
	./tack 

clean:
	$(RM) tack *.o
