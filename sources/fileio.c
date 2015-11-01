/**
* @file fileio.c
* @author Jérémie Leclerc.
*/
#include "mainHeader.h"

/**
* @brief Allow to ask the user to choose a name for the save.
* @return The non well formated name provided by the user.
*/
char* askForAName() {
    printf("Choose a name for the grid : ");
    char* userNamed = (char*) malloc(20*sizeof(char));
    int readed = 0;
    int readNumber = 0;

    do {
        printf("%s\n", "getchar");
        readed = getchar();
        if (readed != '\n' && readed != EOF) {
            if (readNumber < sizeof(userNamed)) {
                printf("%s %d\n", "readNumber < strlen : ", readNumber);
                userNamed[readNumber] = readed;
            } else {
                printf("%s %d\n", "else : ", readNumber);
                userNamed = realloc(userNamed, strlen(userNamed)+1);
                userNamed[readNumber] = readed;
            }
            readNumber++;
        }
    }while (readed != '\n' && readed != EOF);

    char* returnValue = (char*) malloc(strlen(userNamed) * sizeof(char));
    strcpy(returnValue, userNamed);
    printf("%s \n", returnValue);

    free(userNamed);
    return returnValue;
}

/**
* @brief Display all saves from previous execution and ask the user to choose one of them.
* @return The name of the save selected by the user.
*/
char* askForAFileToLoad() {
    int readed = 0;
    int i = 0;
    char* userNamed = (char*) malloc(1 * sizeof(char));

    printf("Here are your saves : \n");
    system("ls *.sav");
    printf("Wich of them do you want to load ? : ");

    do {
        readed = getchar();
        if (readed != '\n' && readed != EOF) {
            userNamed = (char*) realloc(userNamed, (strlen(userNamed) + 1));
            userNamed[i] = readed;
            i++;
        }
    } while (readed != '\n' && readed != EOF);

    return userNamed;
}

/**
* @brief Allow to replace spaces by underscores from a non well formated string.
* @param name - A string provided by the user as a name for the save.
* @return A well formated string for the name of the save.
*/
char* formatName(char* name) {
    char* finalName = (char*) malloc(strlen(name) * sizeof(char));
    int i = 0;

    for (i = 0; i < strlen(name); i++) {
        if (name[i] == ' ') {
            finalName[i] = '_';
        } else {
            finalName[i] = name[i];
        }
    }

    return finalName;
}
/**
* @brief Allow to save the newly created grid.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
* @param name - The name of the grid. Used to name the save file.
* @param personage -
*/
void save(GRID* grid, char* name) {
    char* fileName = (char*) malloc((strlen(name) + 4) * sizeof(char));

    FILE* canal;
    sprintf(fileName, "%s.sav", name);
    canal = fopen(fileName, "wt");

    int i = 0;
    int j = 0;
    for (i = 0; i < grid->height; i++) {
        for (j = 0; j < grid->width; j++) {
            if (grid->matrix[i][j] == WALL) {
                fprintf(canal, "▓");
            } else if (grid->matrix[i][j] == VOID) {
                fprintf(canal, " ");
            } else if (grid->matrix[i][j] == PLAYER) {
                fprintf(canal, "o");
            } else if (grid->matrix[i][j] == BONUS) {
                fprintf(canal, "B");
            } else if (grid->matrix[i][j] == MALUS) {
                fprintf(canal, "M");
            } else {
                continue;
            }
        }
        fprintf(canal, "\n");
    }

    free(fileName);
    fflush(canal);
    fclose(canal);
}

/**
* @brief Allow to load a previously saved grid.
* @param grid - A pointer to a GRID structure that will be used to store the maze matrix and its dimensions.
* @param name - The name of the save file to load (with its extension).
*/
void load(GRID* grid, char* userNamed) {
    FILE* canal;

    int userNamedLength = strlen(userNamed);
    if (userNamed[userNamedLength-1] == 'v') {
        if (userNamed[userNamedLength-2] == 'a') {
            if (userNamed[userNamedLength-3] == 's') {
                if (userNamed[userNamedLength-4 == '.']){
                    canal = fopen(userNamed, "rt");
                }
            }
        }
    } else {
        char* fileName = (char*) malloc((strlen(userNamed) + 4) * sizeof(char));
        sprintf(fileName, "%s.sav", userNamed);
        canal = fopen(fileName, "rt");
        free(fileName);
    }

    int readed = 0;
    int width = 0;
    int height = 0;

    do {
        readed = fgetc(canal);
        if (readed != '\n' && readed != EOF) {
            width++;
        }
    }while (readed != '\n' && readed != EOF);

    printf("Width : %d\n", width);

    fflush(canal);
    fclose(canal);
}
