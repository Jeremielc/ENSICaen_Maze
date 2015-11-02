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
*/
typedef struct {
    int height;     /*!< height - The height of the maze.*/
    int width;      /*!< width - The width of the maze.*/
    int** matrix;   /*!< matrix - The maze itself as a tow dimensions table.*/
} GRID;

/**
* @brief A structure that contain coordinates for the differents characters.
*/
typedef struct {
    int pos_y;  /*!< pos_x - The x position of the character (column).*/
    int pos_x;  /*!< pos_y - The y position of the character (lines).*/
    int score;  /*!< score - The score of the character.*/
} CHARACTER;

char*   askForAFileToLoad           ();
char*   askForAName                 ();
char    askForDefaultConfiguration  ();
void    cleanGrid                   (GRID* grid);
void    displayGrid                 (GRID, CHARACTER);
int     displayMenu                 ();
char*   formatName                  (char*);
void    flush                       ();
void    freeMatrix					(int, int**);
GRID    generateGrid                ();
void    generateItems               (GRID*);
void	generateWay	                (GRID*);
void    initGrid                    (GRID*);
void    load                        (GRID*, char*);
void    manageItems                 (GRID*, CHARACTER*);
void    movePlayer                  (GRID*, CHARACTER*, int);
void    save                        (GRID*, char*);
void 	searchAndReplace			(GRID*, int, int);
