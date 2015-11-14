all : maze clean unitary_test

maze : grid.o main.o utils.o fileio.o moves.o
	gcc main.o grid.o utils.o fileio.o moves.o -Wall -ansi -o maze

main.o : sources/main.c
	gcc -c sources/main.c -Wall -ansi

grid.o : sources/grid.c
	gcc -c sources/grid.c -Wall -ansi

utils.o : sources/utils.c
	gcc -c sources/utils.c -Wall -ansi

fileio.o : sources/fileio.c
	gcc -c sources/fileio.c -Wall -ansi

moves.o : sources/moves.c
	gcc -c sources/moves.c -Wall -ansi

unitary_test : sources/unitaryTest.c
	gcc sources/unitaryTest.c -Wall -ansi -o unitaryTest
	./unitaryTest

clean :
	rm -f *.o
