/**
* @file mainHeader.h
* @author Jérémie Leclerc.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define WALL 0
#define VOID -1
#define PLAYER 1
#define BONUS 2
#define MALUS 3
#define VAL_MOVE 5;
#define VAL_BONUS 50;
#define VAL_MALUS 45;

/**
* @brief A structure used to contain the grid and its dimensions.
* @param height - The height of the maze.
* @param width - The width of the maze.
* @param matrix - The maze itself as a tow dimensions table.
*/
typedef struct {
    int height;
    int width;
    int** matrix;
} GRID;

/**
* @brief A structure that contain coordinates for the differents characters.
* @param pos_x - The x position of the character (column).
* @param pos_y - The y position of the character (lines).
*/
typedef struct {
    int pos_y;
    int pos_x;
} CHARACTER;

char*   askForAFileToLoad           ();
char*   askForAName                 ();
char    askForDefaultConfiguration  ();
void    cleanGrid                   (GRID* grid);
void    displayGrid                 (GRID, CHARACTER, int);
int     displayMenu                 ();
char*   formatName                  (char*);
void    flush                       ();
void    freeMatrix					(int, int**);
GRID    generateGrid                ();
void    generateItems               (GRID*);
void	generateWay	                (GRID*);
void    initGrid                    (GRID*);
void    load                        (GRID*, char*);
void    movePlayer                  (GRID*, CHARACTER*, int);
void    save                        (GRID*, char*);
void 	searchAndReplace			(GRID*, int, int);
