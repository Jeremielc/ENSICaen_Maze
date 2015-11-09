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
    char* userNamed = (char*) malloc(1*sizeof(char));
    userNamed[0] = '\0';

    int c = 0;
    int i = 0;
    do {
        c = getchar();
        if (c != '\n' && c != EOF) {
            userNamed[i] = c;
            i++;
        }

        if (i >= strlen(userNamed)) {
            userNamed = realloc(userNamed, strlen(userNamed) + 1);
        }
    } while(c != '\n' && c != EOF);

    return userNamed;
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
* @param gridName - The name for the grid, readed from the user when the grid is newly generated,
* from the name of the specified savefile when user choose one to load.
*/
void displayHighscore(char* gridName) {
    FILE* canal;
    char* fileName = (char*) calloc(strlen(gridName) + 12, sizeof(char));
    sprintf(fileName, "saves/%s.score", gridName);
    canal = fopen(fileName, "rt");

    int i = 0;
    int j = 0;
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
        j++;
    } while(verify != NULL && j < 10);

    printf("--------------------------------\n");
    printf("Press 'c' then hit enter to return to menu.\n");
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

    free(name);
    return finalName;
}

/**
* @brief Allow to load a previously saved grid.
* @param grid - A pointer to a GRID structure that will be used to store the maze matrix and its dimensions.
* @param name - The name of the save file to load (with its extension).
* @return 0 if the grid cannot be loaded, 1 if it can.
*/
int load(GRID* grid, char* userNamed) {
    FILE* canal = NULL;

    int userNamedLength = strlen(userNamed);                       /*Verify if the user named his file with the extension.*/
    if (userNamed[userNamedLength-1] == 'g') {
        if (userNamed[userNamedLength-2] == 'f') {
            if (userNamed[userNamedLength-3] == 'c') {
                if (userNamed[userNamedLength-4 == '.']){
                    char* fileName = (char*) malloc((strlen(userNamed) + 6) * sizeof(char));
                    sprintf(fileName, "saves/%s", userNamed);
                    canal = fopen(userNamed, "rt");
                    free(fileName);
                    if (canal == NULL) {                                        /*If the file isn't valid.*/
                        printf("Warning : The file you choose to load does not exist or is invalid.\n");
                        perror("Please load another file or regenerate one from the generate menu entry.\n");
                        sleep(5);
                        return 0;
                    }
                }
            }
        }
    } else {                                                                    /*Add the extension.*/
        char* fileName = (char*) malloc((strlen(userNamed) + 10) * sizeof(char));
        sprintf(fileName, "saves/%s.cfg", userNamed);
        canal = fopen(fileName, "rt");
        free(fileName);
        if (canal == NULL) {                                                    /*If the file isn't valid.*/
            printf("Warning : The file you choose to load does not exist or is invalid.\n");
            perror("Please load another file or regenerate one from the generate menu entry.\n");
            sleep(5);
            return 0;
        }
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

    return 1;
}

/**
* @brief Allow to register a new highscore for the player and save it to a file.
* @param gridName - The name of the actual maze.
* @param score - The actual score of the player.
*/
void manageHighscore(char* gridName, int score) {
    HIGHSCORE* scoreTab = (HIGHSCORE*) calloc(11, sizeof(HIGHSCORE));

    FILE* canal;
    char* fileName = (char*) calloc(strlen(gridName) + 12, sizeof(char));
    sprintf(fileName, "saves/%s.score", gridName);
    canal = fopen(fileName, "rt");

    char* readedLine = (char*) calloc(28, sizeof(char));
    char* verify = NULL;
    verify = fgets(readedLine, 27, canal);

    char* userName;
    char* readedScore = (char*) calloc(4, sizeof(char));
    int convertedScore = 0;

    int i = 0;
    int j = 0;
    int pos = 0;
    int semicolonCount = 0;

    do {
        userName = (char*) calloc(20, sizeof(char));
        verify = fgets(readedLine, 27, canal);
        semicolonCount = 0;
        for (i = 0; i < strlen(readedLine); i++) {
            if (readedLine[i] == ';') {
                semicolonCount++;
                pos = i + 1;
                continue;
            }

            switch (semicolonCount) {
                case 1 :
                    userName[i - pos] = readedLine[i];
                    break;
                case 2 :
                    readedScore[i - pos] = readedLine[i];
                    break;
                default :
                    break;
            }

            convertedScore = atoi(readedScore);
        }

        scoreTab[j].name = userName;
        scoreTab[j].score = convertedScore;

        j++;
    } while(verify != NULL);


    char* name = promptForNewHighscore(score);
    scoreTab[10].name = name;
    scoreTab[10].score = score;

    reorderHighscore(scoreTab, 11);

    fclose(canal);
    canal = fopen(fileName, "wt");

    int index = 0;
    fprintf(canal, "Rank;Username;Score\n");
    for (index = 10; index > 0; index--) {
        fprintf(canal, "%02d;%.20s;%04d\n", 11-index, scoreTab[index].name, scoreTab[index].score);
    }

    fclose(canal);

    for (i = 0; i < 11; i++) {
        free(scoreTab[i].name);
    }
    free(scoreTab);
    free(readedScore);
    free(readedLine);
    free(userName);
    free(fileName);
}

/**
* @brief Prompt the user to give is name in order to register a new highscore.
* @param score - The actual score of the player.
* @return 20 characters for the player name.
*/
char* promptForNewHighscore(int score) {
    printf("You are one of the ten best player on this grid !\n");
    printf("Enter your name to save your score of %d points : ", score);

    char* name = (char*) calloc(20, sizeof(char));
    fgets(name, 20, stdin);
    /*flush(stdin);*/

    name[strlen(name) - 1] = '\0'; /*Remove \n character.*/

    return name;
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

    fprintf(canal, "Rank;Username;Score\n");
    i = 0;
    for (i = 1; i <= 10; i++) {
        fprintf(canal, "%02d;%.20s;%04d\n", i, "John Doe", 0);
    }

    fclose(highscore);
    free(highscoreName);

    system("ls saves/ > /dev/null 2>&1 || mkdir saves");
    system("mv *.cfg saves/");
    system("mv *.score saves/");
}
