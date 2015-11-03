/**
* @file grid.c
* @author Jérémie Leclerc.
*/
#include "mainHeader.h"

/**
* @brief Allow to ask the user if he wants to use the default maze configuration.
*/
char askForDefaultConfiguration() {
    printf("Do you want to use default configuration (23 by 9) to generate the grid ? [y/n]");

    char saisie = 0;
    saisie = getchar();
    flush();

    return saisie;
}

/**
* @brief Allow to set all "non walls" cells to the VOID value (-1).
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
*/
void cleanGrid(GRID* grid) {
    int y = 0;
    int x = 0;

    for (y = 0; y < grid->height; y++) {
        for (x = 0; x < grid->width; x++) {
            if (grid->matrix[y][x] != WALL) {
                grid->matrix[y][x] = VOID;
            }
        }
    }
}

/**
* @brief Allow to display a maze.
* @param grid - A GRID structure containing the maze matrix that you want to display.
* @param player - A CHARACTER structure containing player coordinates.
*/
void displayGrid(GRID grid, CHARACTER player) {
    system("clear");
    int i = 0;
    int j = 0;

    for (i = 0; i < grid.height; i++) {
        for (j = 0; j < grid.width; j++) {
            if (i == player.pos_y && j == player.pos_x) {
                printf("o");
            } else {
                switch (grid.matrix[i][j]) {
                    case WALL :
                        printf("█");
                        break;
                    case VOID :
                        printf(" ");
                        break;
                    case BONUS :
                        printf("B");
                        break;
                    case MALUS :
                        printf("M");
                        break;
                    default :
                        break;
                }
            }
        }
        printf("\n");
    }
    printf("Score : %d\n", player.score);
}

/**
* @brief Ask the user to specify configuration for the maze and generate a random grid.
* @return A grid object containing maze caracteristics and the maze itself.
*/
GRID generateGrid() {
    GRID grid;
    char saisie = askForDefaultConfiguration();

    if (saisie == 'Y' || saisie == 'y') {
        grid.height = 9 * 2 + 1;
        grid.width = 23 * 2 + 1;
    } else if (saisie == 'N' || saisie == 'n') {
        int height = 0;
        int width = 0;

        printf("Witch value do you want to use for height : ");
        scanf("%d", &height);
        printf("Witch value do you want to use for width : ");
        scanf("%d", &width);
        flush();

        height = height * 2 + 1;
        width = width * 2 + 1;
        grid.height = height;
        grid.width = width;
    } else {
        printf("Please use 'y' or 'n' to answer.\n");
        do {
            saisie = askForDefaultConfiguration();
        }while (saisie != 'Y' && saisie != 'y' && saisie != 'N' && saisie != 'n');
    }

    int** matrix = (int**) calloc(grid.height, sizeof(int*));
    if (matrix == NULL) {
        perror("Unable to allocate memory.\n");
        exit(-1);
    }

    int i = 0;
    for (i = 0;  i < grid.height; i++) {
        matrix[i] = (int*) calloc(grid.width, sizeof(int));
        if (matrix[i] == NULL) {
            perror("Unable to allocate memory.\n");
            exit(-1);
        }
    }

    grid.matrix = matrix;

    return grid;
}

/**
* @brief Place items (bonuses and maluses) at random coordinates in the maze.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
*/
void generateItems(GRID* grid) {
    int numberOfBonuses = grid->height;
    int numberOfMaluses = grid->height - 5;
    int type = 0;
    int y = 0;
    int x = 0;

    srand(time(NULL));
    do {
        y = rand() % (grid->height - 1);
        x = rand() % (grid->width - 1);
        type = rand() % 2;

        if (y != 1 && y != (grid->height - 1) && x != 0 && x != grid->width) {
            if (grid->matrix[y][x] == VOID) {
                if (type == 0) {
                    grid->matrix[y][x] = BONUS;
                    numberOfBonuses--;
                } else if (type == 1) {
                    grid->matrix[y][x] = MALUS;
                    numberOfMaluses--;
                }
            }
        }
    } while(numberOfBonuses != 0 && numberOfMaluses != 0);
}

/**
* @brief Break walls into the maze to generate a way to the exit.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
*/
void generateWay(GRID* grid) {
    int y = 0;
    int x = 0;
    int nbIterationationMax = (((grid->width - 1) / 2) * ((grid->height - 1 ) / 2)) - 1;
    int nbIteration = 0;

    srand(time(NULL));

    while (nbIteration < nbIterationationMax) {
        y = rand() % grid->height -1;
        x = rand() % grid->width -1;

        if (y != 0 && x != 0) {                                                 /*Si differents des bords du labyrinthe*/
            if (x % 2 == 0 && y % 2 == 1) {                                     /*mur entre deux cellules horizontales*/
                if (grid->matrix[y][x-1] != grid->matrix[y][x+1]) {             /*si indices des deux cellules differents*/
                    grid->matrix[y][x] = VOID;
                    nbIteration++;
                    searchAndReplace(grid, grid->matrix[y][x-1], grid->matrix[y][x+1]);
                }
            }

            if (x % 2 == 1 && y % 2 == 0) {                                     /*mur entre deux cellules verticales*/
                if (grid->matrix[y-1][x] != grid->matrix[y+1][x]) {             /*si indices des deux cellules differents*/
                    grid->matrix[y][x] = VOID;
                    nbIteration++;
                    searchAndReplace(grid, grid->matrix[y-1][x], grid->matrix[y+1][x]);
                }
            }
        }
    }
}

/**
* @brief Allow to assign values to each cells of the maze. Used to generate a way out.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
*/
void initGrid(GRID* grid) {
    int number = 1;
    int i = 0;
    int j = 0;

    for (i = 0; i < grid->height; i++) {
        for (j = 0; j < grid->width; j++) {
            if (i % 2 == 1 && j % 2 == 1) {
                grid->matrix[i][j] = number;
                number++;
            } else {
                grid->matrix[i][j] = 0;
            }
        }
    }

    grid->matrix[1][0] = ' ';
    grid->matrix[grid->height - 2][grid->width - 1] = ' ';
}

/**
* @brief Allow to change values of cells the maze. Used to generate a way out.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
* @param old_value - The value you want to replace by the new one.
* @param new_value - The new value that replace the old one.
*/
void searchAndReplace(GRID* grid, int old_value, int new_value) {
	int i = 0;
	int j = 0;

    for (i = 0; i < grid->height; i++) {
        for (j = 0; j < grid->width; j++) {
            if (grid->matrix[i][j] == old_value) {
                grid->matrix[i][j] = new_value;
            } else {

            }
        }
    }
}
