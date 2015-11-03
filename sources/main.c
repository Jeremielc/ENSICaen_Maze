/**
* @file main.c
* @author Jérémie Leclerc.
*/
#include "mainHeader.h"

int main (int argc, char ** argv) {
    GRID grid;
    grid.width = 0;
    grid.height = 0;
    grid.matrix = NULL;

    CHARACTER player;
    player.pos_y = 1;
    player.pos_x = 0;
    player.score = 2000;

    int choice = 0;
    char* fileName;

    do {
        choice = displayMenu();

        switch (choice) {
            case 1 :    /*New game*/
                grid = generateGrid();                  /*Creation of the game grid.*/
                initGrid(&grid);                        /*Initialization (empty cells surrounded by walls.)*/
                generateWay(&grid);                     /*Generate a way out of the maze.*/
                cleanGrid(&grid);                       /*Ensure that the grid only contain VOID or WALL values.*/
                printf("generate items\n");generateItems(&grid);
                displayGrid(grid, player);              /*Display the maze and the player at the beggining of the maze.*/

                fileName = askForAName();
                fileName = formatName(fileName);    /*Remove spaces from the name.*/
                save(&grid, fileName);                /*Save the grid to a <name>.sav file.*/
                break;

            case 2 :    /*Load game*/
                system("clear");
                fileName = askForAFileToLoad();
                load(&grid, fileName);                /*Load the grid and configure characters positions.*/
                break;

            case 3 :    /*Play the game*/
                player.pos_y = 1;                       /*Positionning the player at the beggining of the maze.*/
                player.pos_x = 0;                       /*...*/
                player.score = 2000;                    /*Initialize the score.*/

                displayGrid(grid, player);              /*Display the maze and the player at the beggining of the maze.*/
                int keyPressed = 0;                     /*This loop get and mange the desired direction to move the player.*/
                do {
                    keyPressed = 0;
                    keyPressed = getchar();
                    movePlayer(&grid, &player, keyPressed);
                    displayGrid(grid, player);          /*Refresh the grid with the update position of the player.*/
                } while (player.pos_x < (grid.width - 1) && player.pos_y < (grid.height - 1));

                system("clear");
                if (keyPressed != 'p') {
                    printf("You're out !\n");
                    printf("---------- Highscores ----------\n");
                } else {
                    printf("You popped out of the maze !\n");
                    printf("---------- Highscores ----------\n");
                }

                displayHighscore(fileName);
                break;

            case 4 :    /*Close the program*/
                if (grid.matrix != NULL) {
                    freeMatrix(grid.height, grid.matrix);/*De-allocate memory for the maze.*/
                }
                free(fileName);
                printf("Good bye !\n");
                sleep(1);
                system("clear");
                exit(0);
                break;

            default :
                break;
        }
    } while (choice != 4);
    return 0;
}
