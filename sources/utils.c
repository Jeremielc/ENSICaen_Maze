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
* @param height - The number of lines in the matrix.
* @param matrix - The tow dimensional tab to free.
*/
void freeMatrix(int height, int** matrix) {
    int i = 0;

    for (i = 0; i < height; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

/**
* @brief Allow to order the a tab from the less significant value to the most significant.
* @param tab - A HIGHSCORE tab containing the list of hightscores.
* @param length - The length of the tab.
*/
void reorderHighscore(HIGHSCORE* tab, int length) {
    int i = 0;
    int j = 0;
    int imin = 0;
    HIGHSCORE inter;

    for (i = 0; i < length - 1; i++) {
        imin = i;

        for (j = i + 1; j < length; j++) {
            if (tab[j].score < tab[imin].score) {
                imin = j;
            }
        }

        if (i != imin) {
            inter = tab[imin];
            tab[imin] = tab[i];
            tab[i] = inter;
        }
    }
}
