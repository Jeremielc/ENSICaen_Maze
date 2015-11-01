/**
* @file utils.c
* @author Jérémie Leclerc.
*/
#include "mainHeader.h"

/**
* @brief Allow to display a menu and read what the user answered.
* @return An integer that corresponds to the choice of the user.
*/
int displayMenu() {
    system("clear");
    printf("******************** Welcome in Maze ! ******************\n");
    printf("*********************************************************\n");
    printf("* 1) New game : generate a new maze and save it.\n");
    printf("* 2) Load game : choose one of your saves.\n");
    printf("* 3) Play : choose one of your saves and launch the game.\n");
    printf("* 4) Exit : Close the program.\n");
    printf("*********************************************************\n");
    printf("Please, choose one of the above numbers.\n");
    printf("Your choice : ");

    int choice = 0;
    scanf("%d", &choice);
    flush();

    return choice;
}

/**
* @brief Allow to empty the stdin buffer
*/
void flush() {
    int c = 0;

    do {
        c = getchar();
    }while (c != '\n' && c != EOF);
}

/**
* @brief Allow to free the memory reserved for the matrix representing the maze.
*/
void freeMatrix(int height, int** matrix) {
    int i = 0;

    for (i = 0; i < height; i++) {
        free(matrix[i]);
    }

    free(matrix);
}
