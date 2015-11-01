/**
* @file moves.c
* @author Jérémie Leclerc
*/
#include "mainHeader.h"

/**
* @brief Manage the moves of the character.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
* @param player - A pointer to a CHARACTER structure containg player coordinates.
* @param move - A character repreenting the move to make.
*/
void movePlayer(GRID* grid, CHARACTER* player, int move) {
    flush();
    int pos_y = 0;
    int pos_x = 0;

    switch (move) {
        case 'z' :
            pos_y = player->pos_y;
            pos_x = player->pos_x;

            if (grid->matrix[pos_y - 1][pos_x] != WALL) {
                pos_y = pos_y - 1;
                player->pos_y = pos_y;
            }
            break;
        case 'q' :
            pos_y = player->pos_y;
            pos_x = player->pos_x;

            if (grid->matrix[pos_y][pos_x - 1] != WALL) {
                pos_x = pos_x - 1;
                player->pos_x = pos_x;
            }
            break;
        case 's' :
            pos_y = player->pos_y;
            pos_x = player->pos_x;

            if (grid->matrix[pos_y + 1][pos_x] != WALL) {
                pos_y = pos_y + 1;
                player->pos_y = pos_y;
            }
            break;
        case 'd' :
            pos_y = player->pos_y;
            pos_x = player->pos_x;

            if (grid->matrix[pos_y][pos_x + 1] != WALL) {
                pos_x = pos_x + 1;
                player->pos_x = pos_x;
            }
            break;
        default :
            break;
    }
}
