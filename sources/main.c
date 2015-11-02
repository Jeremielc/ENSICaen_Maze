/**
* @file main.c
* @author Jérémie Leclerc.
*/
#include "mainHeader.h"

int main (int argc, char ** argv) {
    int choice = 0;
    int score = 1000;
    GRID grid;
    grid.matrix = NULL;

    CHARACTER player;
    player.pos_y = 1;
    player.pos_x = 0;

    do {
        choice = displayMenu();

        switch (choice) {
            case 1 :    /*New game*/
                grid = generateGrid();                  /*Creation of the game grid.*/
                initGrid(&grid);                        /*Initialization (empty cells surrounded by walls.)*/
                generateWay(&grid);                     /*Generate a way out of the maze.*/
                cleanGrid(&grid);                       /*Ensure that the grid only contain VOID or WALL values.*/
                printf("generate items\n");generateItems(&grid);

                displayGrid(grid, player, score);       /*Display the maze and the player at the beggining of the maze.*/

                char* fileToSave = askForAName();       /*Ask the user to choose a name for the save.*/
                fileToSave = formatName(fileToSave);    /*Remove spaces from the name.*/
                save(&grid, fileToSave);                /*Save the grid to a <name>.sav file.*/
                free(fileToSave);                       /*De-allocate memory for the name of the file.*/
                break;

            case 2 :    /*Load game*/
                system("clear");
                char* fileToLoad = askForAFileToLoad(); /*Ask the user to choose a name from his saves.*/
                load(&grid, fileToLoad);                /*Load the grid and configure characters positions.*/
                free(fileToLoad);                       /*De-allocate memory for the name of the save.*/
                break;

            case 3 :    /*Play the game*/
                player.pos_y = 1;                       /*Positionning the player at the beggining of the maze.*/
                player.pos_x = 0;                       /*...*/

                displayGrid(grid, player, score);       /*Display the maze and the player at the beggining of the maze.*/
                int keyPressed = 0;                     /*This loop get and mange the desired direction to move the player.*/
                do {
                    keyPressed = 0;
                    keyPressed = getchar();
                    score -= VAL_MOVE;
                    movePlayer(&grid, &player, keyPressed);
                    displayGrid(grid, player, score);   /*Refresh the grid with the update position of the player.*/
                } while (player.pos_x < (grid.width - 1) && player.pos_y < (grid.height - 1));

                system("clear");
                printf("You're out !\n");
                sleep(2);
                break;

            case 4 :    /*Close the program*/
                if (grid.matrix != NULL) {
                    freeMatrix(grid.height, grid.matrix);/*De-allocate memory for the maze.*/
                }

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
