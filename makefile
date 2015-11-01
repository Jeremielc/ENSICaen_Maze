maze : grid.o main.o utils.o fileio.o moves.o
	gcc main.o grid.o utils.o fileio.o moves.o -Wall -ansi -o maze
	ls objects > /dev/null 2>&1 || mkdir objects/
	mv -f *.o objects/

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

clean :
	rm -rf objects
