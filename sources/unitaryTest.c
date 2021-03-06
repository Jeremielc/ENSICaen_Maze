/**
* @file unitaryTest.c
* @author Jérémie Leclerc
*/
#include "mainHeader.h"
#include "CUnit/Basic.h"

/*Prototypes*/
void verifyFormatName();
void verifyCleanGrid();
void verifyGenerateItems();
void verifyInitGrid();
void verifySearchAndReplace();
void verifyMovePlayer();
void verifyPlayerCantMove();
void verifyReorderHighscore();

/**
* @brief The main function for unitary tests.
* @param argc - The number of aruments provided to the function.
* @param argv - A string table that corresponds to the value of arguments.
* @return An integer value. 0 if everything is OK.
*/
int main(int argc, char** argv) {
    CU_pSuite pSuite[7] = {};

    CU_initialize_registry();

    pSuite[0] = CU_add_suite("Verify formatName()", NULL, NULL);                /*Verify formatName funtion.*/
    CU_ADD_TEST(pSuite[0], verifyFormatName);

    pSuite[1] = CU_add_suite("Verify cleanGrid()", NULL, NULL);                 /*Verify cleanGrid funtion.*/
    CU_ADD_TEST(pSuite[1], verifyCleanGrid);

    pSuite[2] = CU_add_suite("Verify generateItems()", NULL, NULL);             /*Verify generateItems function.*/
    CU_ADD_TEST(pSuite[2], verifyGenerateItems);

    pSuite[3] = CU_add_suite("Verify initGrid()", NULL, NULL);                  /*Verify initGrid funtion.*/
    CU_ADD_TEST(pSuite[3], verifyInitGrid);

    pSuite[4] = CU_add_suite("Verify searchAndReplace()", NULL, NULL);          /*Verify searchAndReplace function.*/
    CU_ADD_TEST(pSuite[4], verifySearchAndReplace);

    pSuite[5] = CU_add_suite("Verify movePlayer()", NULL, NULL);                /*Verify movePlayer funtion.*/
    CU_ADD_TEST(pSuite[5], verifyMovePlayer);
    CU_ADD_TEST(pSuite[5], verifyPlayerCantMove);

    pSuite[6] = CU_add_suite("Verify reorderHighscore()", NULL, NULL);          /*Verify reorderHighscore function.*/
    CU_ADD_TEST(pSuite[6], reorderHighscore);


    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

/**
* @brief Verify the the formatName function correctly replace spaces by underscores.
*/
void verifyFormatName() {   /*Verify that spaces in the name are replaced by underscores.*/
    char* name = "grille 1";
    char* wellFormatedName = formatName(name);
    CU_ASSERT(strcmp(wellFormatedName, "grille_1") == 0);

    name = "special ! ? ; :";
    wellFormatedName = formatName(name);
    CU_ASSERT(strcmp(wellFormatedName, "special_!_?_;_:") == 0);

    name = NULL;
    wellFormatedName = formatName(NULL);
    CU_ASSERT(wellFormatedName == NULL);
}

/**
* @brief Verify that the cleanGrid function replaced avery remaining number, used during initialization, by VOID value.
*/
void verifyCleanGrid() {
    GRID grid;
    grid.height = 5;
    grid.width = 5;

    int matrix[5][5] = {
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, 1, WALL, 2, WALL},
        {WALL, 3, WALL, 4, WALL},
        {WALL, 5, WALL, 6, WALL},
        {WALL, WALL, WALL, WALL, WALL}
    };

    grid.matrix = (int**) matrix;

    cleanGrid(&grid);
    CU_ASSERT(grid.height == 5);
    CU_ASSERT(grid.width == 5);
    CU_ASSERT(grid.matrix[1][1] == VOID);
    CU_ASSERT(grid.matrix[1][3] == VOID);
    CU_ASSERT(grid.matrix[2][1] == VOID);
    CU_ASSERT(grid.matrix[2][3] == VOID);
    CU_ASSERT(grid.matrix[3][1] == VOID);
    CU_ASSERT(grid.matrix[3][3] == VOID);
}

/**
* @brief Verify that the generateItems functio generate enought items (bonus or malus).
*/
void verifyGenerateItems() {
    GRID grid;
    grid.height = 15;
    grid.width = 15;

    int matrix[15][15] = {
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL, VOID, WALL},
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
    };

    grid.matrix = (int**) matrix;

    generateItems(&grid);

    int y = 0;
    int x = 0;
    int nbBonusOrMalus = 0;
    int nbOfUnknownItems = 0;

    for (y = 0; y < grid.height; y++) {
        for (x = 0; x < grid.width; x++) {
            if (grid.matrix[y][x] == BONUS || grid.matrix[y][x] == MALUS) {
                nbBonusOrMalus++;
            }

            if (grid.matrix[y][x] != WALL && grid.matrix[y][x] != VOID && grid.matrix[y][x] != BONUS && grid.matrix[y][x] != MALUS) {
                nbOfUnknownItems++;
            }
        }
    }

    CU_ASSERT(nbBonusOrMalus >= grid.height);
    CU_ASSERT(nbOfUnknownItems == 0);
}

/**
* @brief Verify that the initGrid function correctly initialize the grid in order to break the walls between the cells.
*/
void verifyInitGrid() {
    GRID grid;
    grid.height = 5;
    grid.width = 5;

    int matrix[5][5] = {
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, WALL, WALL, WALL, WALL}
    };

    grid.matrix = (int**) matrix;

    initGrid(&grid);

    CU_ASSERT(grid.height == 5);
    CU_ASSERT(grid.width == 5);
    CU_ASSERT(grid.matrix[1][1] == 1);
    CU_ASSERT(grid.matrix[1][3] == 2);
    CU_ASSERT(grid.matrix[2][1] == 3);
    CU_ASSERT(grid.matrix[2][3] == 4);
    CU_ASSERT(grid.matrix[3][1] == 5);
    CU_ASSERT(grid.matrix[3][3] == 6);
}

/**
* @brief Verify that the searchAndReplace function correctly spot remain of an old value and replace them by a new value according to the current step in initialization phase.
*/
void verifySearchAndReplace() {
    GRID grid;
    grid.height = 5;
    grid.width = 5;

    int matrix[5][5] = {
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, 1, 2, 2, WALL},
        {WALL, 1, WALL, 2, WALL},
        {WALL, 1, 1, 2, WALL},
        {WALL, WALL, WALL, WALL, WALL}
    };

    grid.matrix = (int**) matrix;

    searchAndReplace(&grid, 1, 2);

    CU_ASSERT(grid.height == 5);
    CU_ASSERT(grid.width == 5);
    CU_ASSERT(grid.matrix[1][1] == 2);
    CU_ASSERT(grid.matrix[1][2] == 2);
    CU_ASSERT(grid.matrix[1][3] == 2);
    CU_ASSERT(grid.matrix[2][1] == 2);
    CU_ASSERT(grid.matrix[2][3] == 2);
    CU_ASSERT(grid.matrix[3][1] == 2);
    CU_ASSERT(grid.matrix[3][2] == 2);
    CU_ASSERT(grid.matrix[3][3] == 2);
}

/**
* @brief verify that the movePlayer function correctly handle moves when the player is cerned by void cells.
*/
void verifyMovePlayer() {
    int x_init = 2;
    int y_init = 2;
    int score_init = 2000;

    GRID grid;
    grid.height = 5;
    grid.width = 5;

    int matrix[5][5] = {
        {WALL, WALL, WALL, WALL, WALL},
        {WALL, VOID, VOID, VOID, WALL},
        {WALL, VOID, PLAYER, VOID, WALL},
        {WALL, VOID, VOID, VOID, WALL},
        {WALL, WALL, WALL, WALL, WALL}
    };

    grid.matrix = (int**) matrix;

    CHARACTER player;
    player.pos_x = x_init;
    player.pos_y = y_init;
    player.score = score_init;

    movePlayer(&grid, &player, 'z');                                            /*Test up move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == (y_init - 1));
    CU_ASSERT(player.score == (score_init - VAL_MOVE));

    grid.matrix[y_init - 1][x_init] = VOID;
    grid.matrix[y_init][x_init] = PLAYER;

    player.pos_x = x_init;
    player.pos_y = y_init;
    player.score = score_init;

    movePlayer(&grid, &player, 'q');                                            /*Test left move.*/
    CU_ASSERT(player.pos_x == (x_init - 1));
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == (score_init - VAL_MOVE));

    grid.matrix[y_init][x_init - 1] = VOID;
    grid.matrix[y_init][x_init] = PLAYER;

    player.pos_x = x_init;
    player.pos_y = y_init;
    player.score = score_init;

    movePlayer(&grid, &player, 's');                                            /*Test down move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == (y_init + 1));
    CU_ASSERT(player.score == (score_init - VAL_MOVE));

    grid.matrix[y_init + 1][x_init] = VOID;
    grid.matrix[y_init][x_init] = PLAYER;

    player.pos_x = x_init;
    player.pos_y = y_init;
    player.score = score_init;

    movePlayer(&grid, &player, 'd');                                            /*Test right move.*/
    CU_ASSERT(player.pos_x == (x_init + 1));
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == (score_init - VAL_MOVE));
}

/**
* @brief verify that the movePlayer function correctly handle moves when the player is cerned by walls.
*/
void verifyPlayerCantMove() {
    int x_init = 1;
    int y_init = 1;
    int score_init = 2000;

    GRID grid;
    grid.height = 3;
    grid.width = 3;

    int matrix[3][3] = {
        {WALL, WALL, WALL},
        {WALL, PLAYER, WALL},
        {WALL, WALL, WALL}
    };

    grid.matrix = (int**) matrix;

    CHARACTER player;
    player.pos_x = x_init;
    player.pos_y = y_init;
    player.score = score_init;

    movePlayer(&grid, &player, 'z');                                            /*Test up move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == score_init);

    movePlayer(&grid, &player, 'q');                                            /*Test left move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == score_init);

    movePlayer(&grid, &player, 's');                                            /*Test down move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == score_init);

    movePlayer(&grid, &player, 'd');                                            /*Test right move.*/
    CU_ASSERT(player.pos_x == x_init);
    CU_ASSERT(player.pos_y == y_init);
    CU_ASSERT(player.score == score_init);
}

/**
* @brief Verify that the reorderHighscore function correctly order highscores.
*/
void verifyReorderHighscore() {
    HIGHSCORE tab[5];
    tab[0].name = "John";
    tab[0].score = 1000;
    tab[1].name = "Emma";
    tab[1].score = 5000;
    tab[2].name = "Peter";
    tab[2].score = 1500;
    tab[3].name = "Moe";
    tab[3].score = 2000;
    tab[4].name = "Homer";
    tab[4].score = 45;

    int nbMember = 5;

    reorderHighscore(tab, nbMember);
    CU_ASSERT(strcmp(tab[0].name, "Homer") == 0);
    CU_ASSERT(strcmp(tab[1].name, "John") == 0);
    CU_ASSERT(strcmp(tab[2].name, "Peter") == 0);
    CU_ASSERT(strcmp(tab[3].name, "Moe") == 0);
    CU_ASSERT(strcmp(tab[4].name, "Emma") == 0);

    CU_ASSERT(tab[4].score >= tab[3].score);
    CU_ASSERT(tab[3].score >= tab[2].score);
    CU_ASSERT(tab[2].score >= tab[1].score);
    CU_ASSERT(tab[1].score >= tab[0].score);
}
