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
    system("ls saves/*.cfg | sed -e 's@saves/@    @g'");
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
* @brief Display the highscore table from the gridName.score file associated to the save.
* @param gridNam - The name for the grid, readed from the user when the grid is newly generated,
* from the name of the specified savefile when user choose one to load.
*/
void displayHighscore(char* gridName) {
    FILE* canal;
    char* fileName = (char*) calloc(strlen(gridName) + 12, sizeof(char));
    sprintf(fileName, "saves/%s.score", gridName);
    canal = fopen(fileName, "rt");

    int i = 0;
    char* readedLine = (char*) calloc(28, sizeof(char));
    char* verify = NULL;
    printf("Rank\tUsername\tScore\n");
    verify = fgets(readedLine, 27, canal);
    do {
        verify = fgets(readedLine, 27, canal);
        for (i = 0; i < strlen(readedLine); i++) {
            if (readedLine[i] != ';') {
                printf("%c", readedLine[i]);
            } else {
                printf("\t");
            }
        }

    } while(verify != NULL);

    printf("--------------------------------\n");
    printf("Press 'c' then it enter to return to menu.\n");
    int c = 0;
    do {
        c = getchar();
    } while (c != 'c');

    free(readedLine);
    free(fileName);
    fclose(canal);
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
* @brief Allow to load a previously saved grid.
* @param grid - A pointer to a GRID structure that will be used to store the maze matrix and its dimensions.
* @param name - The name of the save file to load (with its extension).
*/
void load(GRID* grid, char* userNamed) {
    FILE* canal;

    int userNamedLength = strlen(userNamed);                       /*Verify if the user named his file with the extension.*/
    if (userNamed[userNamedLength-1] == 'g') {
        if (userNamed[userNamedLength-2] == 'f') {
            if (userNamed[userNamedLength-3] == 'c') {
                if (userNamed[userNamedLength-4 == '.']){
                    char* fileName = (char*) malloc((strlen(userNamed) + 6) * sizeof(char));
                    sprintf(fileName, "saves/%s", userNamed);
                    canal = fopen(userNamed, "rt");
                    free(fileName);
                }
            }
        }
    } else {                                                                    /*Add the extension.*/
        char* fileName = (char*) malloc((strlen(userNamed) + 10) * sizeof(char));
        sprintf(fileName, "saves/%s.cfg", userNamed);
        canal = fopen(fileName, "rt");
        free(fileName);
    }

    int readed = 0;
    int width = 0;
    int height = 0;

    do {                                                                        /*Search for the width of the matrix.*/
        readed = fgetc(canal);
        if (readed == '#' || readed == ' ') {
            width++;
        }
    }while (readed != '\n' && readed != EOF);

    rewind(canal);                                                              /*Return to the beggining of the file.*/

    do {                                                                        /*Search for the height of the matrix.*/
        readed = fgetc(canal);
        if (readed == '\n') {
            height++;
        }
    } while (readed != EOF);

    if (width <= 3 && height <= 3) {                                            /*If the file isn't valid.*/
        perror("Warning : The file you choose to load does not exist or is invalid.\n");
        perror("Please load another file or regenerate one from the generate menu entry.\n");
        break;
    }

    if (grid->width < width && grid->height < height) {                         /*If the previous grid is to small, reallocate matrix.*/
        freeMatrix(grid->height, grid->matrix);
        grid->matrix = (int**) calloc(height, sizeof(int*));

        int i = 0;
        for (i = 0; i < height; i++) {
            grid->matrix[i] = (int*) calloc(width, sizeof(int));
        }
    }

    grid->width = width;
    grid->height = height;

    rewind(canal);                                                              /*Return to the beggining of the file.*/

    int i = 0;
    int j = 0;

    do {                                                                        /*Fill the matrix with file data.*/
        readed = fgetc(canal);
        fflush(stdout);

        switch (readed) {
            case '#':
                grid->matrix[i][j] = WALL;
                break;
            case ' ' :
                grid->matrix[i][j] = VOID;
                break;
            case 'B' :
                grid->matrix[i][j] = BONUS;
                break;
            case 'M' :
                grid->matrix[i][j] = MALUS;
                break;
            case '\n' :
                i++;
                height--;
            default :
                break;
        }

        j = (j + 1) % (grid->width + 1);
    } while (readed != EOF && height > 0);

    fflush(canal);
    fclose(canal);
}

void manageHighscore(char* gridName, int score) {

}

/**
* @brief Allow to save the newly created grid.
* @param grid - A pointer to a GRID structure containing the maze matrix and its dimensions.
* @param name - The name of the grid. Used to name the save file.
*/
void save(GRID* grid, char* name) {
    char* fileName = (char*) malloc((strlen(name) + 4) * sizeof(char));

    FILE* canal;
    sprintf(fileName, "%s.cfg", name);
    canal = fopen(fileName, "wt");

    int i = 0;
    int j = 0;
    for (i = 0; i < grid->height; i++) {
        for (j = 0; j < grid->width; j++) {
            switch (grid->matrix[i][j]) {
                case WALL :
                    fprintf(canal, "#");
                    break;
                case VOID :
                    fprintf(canal, " ");
                    break;
                case PLAYER :
                    fprintf(canal, "o");
                    break;
                case BONUS :
                    fprintf(canal, "B");
                    break;
                case MALUS :
                    fprintf(canal, "M");
                    break;
                default :
                    continue;
                    break;
            }
        }
        fprintf(canal, "\n");
    }

    free(fileName);
    fflush(canal);
    fclose(canal);

    FILE* highscore;
    char* highscoreName = (char*) malloc((strlen(name) + 6) * sizeof(char));
    sprintf(fileName, "%s.score", name);
    highscore = fopen(highscoreName, "wt");
    free(highscoreName);

    fprintf(canal, "Rank;Username;Score\n");
    i = 0;
    for (i = 1; i <= 10; i++) {
        fprintf(canal, "%02d;%.20s;%04d\n", i, "John Doe", 0);
    }

    fclose(highscore);

    system("ls saves/ > /dev/null/ 2>&1 || mkdir saves");
    system("mv *.cfg saves/");
    system("mv *.score saves/");
}
