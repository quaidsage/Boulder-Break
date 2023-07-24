/* ENGGEN131 C Project 2022 - Boulder Break */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 10

void InitialiseStory(char *story)
{
    char temp[2000] = "A young scout is found trapped in \nan ancient temple searching for the \nlost secrets of his village. \nLoot and Escape!";
    strcpy(story,temp);
    return;
}

void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char *layout)
{
    int temp[1000];
    for (int i = 0; i < (CAVE_SIZE * CAVE_SIZE); i++){
        if (layout[i] == '1') {
            temp[i] = 1;
        }
        else if (layout[i] == 'E'){
            temp[i]= 2;
        }
        else {
            temp[i] = 0;
        }
    }

    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            cave[i][j] = temp[(i*CAVE_SIZE)+j];
        }
    }
}

void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            if (cave[i][j] == 1) {
                printf("#");
            }
            else if (cave[i][j] == 3){
                printf("X");
            }
            else if (cave[i][j] == 4){
                printf("*");
            }
            else if (cave[i][j] == 5){
                printf("+");
            }
            else if (cave[i][j] == 6){
                printf("O");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int IsBorderComplete(int cave[CAVE_SIZE][CAVE_SIZE])
{
    // top and bottom row
    for (int i = 0; i < CAVE_SIZE; i+=CAVE_SIZE-1) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            if (cave[i][j] == 0) {
                return 0;
            }
        }
    }

    // left and right column
    for (int i = 1; i < CAVE_SIZE - 1; i++) {
        for (int j = 0; j < CAVE_SIZE; j+=CAVE_SIZE-1) {
            if (cave[i][j] == 0) {
                return 0;
            }
        }
    }

    return 1;

}

int IsExitUnique(int cave[CAVE_SIZE][CAVE_SIZE])
{
    int count = 0;
    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            if (cave[i][j] == 2) {
                count++;
            }
        }
    }

    if (count == 1) {
        return 1;
    } else {
        return 0;
    }
}

int IsExitAccessible(int cave[CAVE_SIZE][CAVE_SIZE])
{
    // check inside
    for (int i = 1; i < CAVE_SIZE-1; i++) {
        for (int j = 1; j < CAVE_SIZE-1; j++) {
            if (cave[i][j] == 2) {
                return 0;
            }
        }
    }

    // check corner
    if ((cave[0][0] == 2) || (cave[0][CAVE_SIZE-1] == 2) || (cave[CAVE_SIZE-1][0] == 2) || (cave[CAVE_SIZE-1][CAVE_SIZE-1] == 2)) {
        return 0;
    }


    int count = 0;
    // top and bottom row
    for (int i = 0; i < CAVE_SIZE; i+=CAVE_SIZE-1) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            if (cave[i][j] == 2) {
                count++;
            }
        }
    }

    // left and right column
    for (int i = 1; i < CAVE_SIZE - 1; i++) {
        for (int j = 0; j < CAVE_SIZE; j+=CAVE_SIZE-1) {
            if (cave[i][j] == 2) {
                count++;
            }
        }
    }

    if (count == 0) {
        return 0;
    }
    return 1;
}

void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char *element)
{
    //check if row and col in bounds
    if ((col > CAVE_SIZE - 1) && (row > CAVE_SIZE - 1)) {
        return;
    }

    //check if empty space to place
    if (cave[row][col] != 0) {
        return;
    }

    // get element value
    int i = 0;
    int elementid = 0;
    while (element[i] != '\0') {
        elementid += element[i];
        i++;
    }

    //add item
    if (elementid == 653) {
        for (int i = 0; i < CAVE_SIZE; i++) {
            for (int j = 0; j < CAVE_SIZE; j++) {
                if (cave[i][j] == 3) {
                    return;
                }
            }
        }
        cave[row][col] = 3;
    }
    else if (elementid == 424) {
        cave[row][col] = 4;
    }
    else if (elementid == 875) {
        cave[row][col] = 5;
    }
    else if (elementid == 749) {
        cave[row][col] = 6;
    }
}

void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE]) {
    int temp[CAVE_SIZE][CAVE_SIZE];
    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            temp[i][j] = cave[(CAVE_SIZE-1)-j][i];
        }
    }

    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            cave[i][j] = temp[i][j];
        }
    }
}

int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
    int playerRow, playerCol;

    for (int i = 0; i < CAVE_SIZE; i++) {
        for (int j = 0; j < CAVE_SIZE; j++) {
            if (cave[i][j] == 3) {
                playerRow = i;
                playerCol = j;
            }
        }
    }

    if (move == 's') {
        if (cave[playerRow + 1][playerCol] == 0) {
            cave[playerRow][playerCol] = 0;
            cave[playerRow + 1][playerCol] = 3;
            return 0;
        } else if (cave[playerRow + 1][playerCol] == 4) {
            cave[playerRow][playerCol] = 0;
            return 1;
        } else if (cave[playerRow + 1][playerCol] == 5) {
            cave[playerRow + 1][playerCol] = 3;
            cave[playerRow][playerCol] = 0;
            return 0;
        } else if (cave[playerRow + 1][playerCol] == 6) {
            for (int i = (playerRow + 2); i < CAVE_SIZE; i++) {
                if (cave[i][playerCol] == 4) {
                    cave[i - 1][playerCol] = 0;
                    cave[i][playerCol] = 0;
                    return 0;
                } else if ((cave[i][playerCol] == 5) || (cave[i][playerCol] == 1) || (cave[i][playerCol] == 6)){
                    cave[i-1][playerCol] = 6;
                    return 0;
                } else {
                    cave[i][playerCol] = 6;
                    cave[i-1][playerCol] = 0;
                }
            }
        } else if (cave[playerRow + 1][playerCol] == 1) {
            return 0;
        } else {
            cave[playerRow + 1][playerCol] = 3;
            printf("CONGRATULATIONS!!\nYou escaped!");
            return 2;
        }
    } else if (move == 'w') {
        if (cave[playerRow - 1][playerCol] == 0) {
            cave[playerRow][playerCol] = 0;
            cave[playerRow - 1][playerCol] = 3;
            return 0;
        } else if (cave[playerRow - 1][playerCol] == 4) {
            cave[playerRow][playerCol] = 0;
            return 1;
        } else if (cave[playerRow - 1][playerCol] == 5) {
            cave[playerRow - 1][playerCol] = 3;
            cave[playerRow][playerCol] = 0;
            return 0;
        } else if (cave[playerRow - 1][playerCol] == 6) {
            for (int i = (playerRow - 2); i >= 0; i--) {
                if (cave[i][playerCol] == 4) {
                    cave[i + 1][playerCol] = 0;
                    cave[i][playerCol] = 0;
                    return 0;
                } else if ((cave[i][playerCol] == 5) || (cave[i][playerCol] == 1) || (cave[i][playerCol] == 6)){
                    cave[i+1][playerCol] = 6;
                    return 0;
                } else {
                    cave[i][playerCol] = 6;
                    cave[i+1][playerCol] = 0;
                }
            }
        } else if (cave[playerRow - 1][playerCol] == 1) {
            return 0;
        } else {
            cave[playerRow - 1][playerCol] = 3;
            printf("CONGRATULATIONS!!\nYou escaped!");
            return 2;
        }
    } else if (move == 'a') {
        if (cave[playerRow][playerCol - 1] == 0) {
            cave[playerRow][playerCol] = 0;
            cave[playerRow][playerCol - 1] = 3;
            return 0;
        } else if (cave[playerRow][playerCol - 1] == 4) {
            cave[playerRow][playerCol] = 0;
            return 1;
        } else if (cave[playerRow][playerCol - 1] == 5) {
            cave[playerRow][playerCol - 1] = 3;
            cave[playerRow][playerCol] = 0;
            return 0;
        } else if (cave[playerRow][playerCol - 1] == 6) {
            for (int j = (playerCol - 2); j >= 0; j--) {
                if (cave[playerRow][j] == 4) {
                    cave[playerRow][j + 1] = 0;
                    cave[playerRow][j] = 0;
                    return 0;
                } else if ((cave[playerRow][j] == 5) || (cave[playerRow][j] == 1) || (cave[playerRow][j] == 6)){
                    cave[playerRow][j + 1] = 6;
                    return 0;
                } else {
                    cave[playerRow][j] = 6;
                    cave[playerRow][j + 1] = 0;
                }
            }
        } else if (cave[playerRow][playerCol - 1] == 1) {
            return 0;
        } else {
            cave[playerRow][playerCol - 1] = 3;
            printf("CONGRATULATIONS!!\nYou escaped!");
            return 2;
        }
    } else if (move == 'd') {
        if (cave[playerRow][playerCol + 1] == 0) {
            cave[playerRow][playerCol] = 0;
            cave[playerRow][playerCol + 1] = 3;
            return 0;
        } else if (cave[playerRow][playerCol + 1] == 4) {
            cave[playerRow][playerCol] = 0;
            return 1;
        } else if (cave[playerRow][playerCol + 1] == 5) {
            cave[playerRow][playerCol + 1] = 3;
            cave[playerRow][playerCol] = 0;
            return 0;
        } else if (cave[playerRow][playerCol + 1] == 6) {
            for (int j = (playerCol + 2); j < CAVE_SIZE; j++) {
                if (cave[playerRow][j] == 4) {
                    cave[playerRow][j - 1] = 0;
                    cave[playerRow][j] = 0;
                    return 0;
                } else if ((cave[playerRow][j] == 5) || (cave[playerRow][j] == 1) || (cave[playerRow][j] == 6)){
                    cave[playerRow][j - 1] = 6;
                    return 0;
                } else {
                    cave[playerRow][j] = 6;
                    cave[playerRow][j - 1] = 0;
                }
            }
        } else if (cave[playerRow][playerCol + 1] == 1) {
            return 0;
        } else {
            cave[playerRow][playerCol + 1] = 3;


            printf("CONGRATULATIONS!!\nYou escaped!");
            return 2;
        }
    } else {
        return 0;
    }
}

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
    char layout[200] = "1111111111100000000110000000011000000001100000000E10000000011000000001100000000110000000011111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = {0};
	int gameOver = 0;

	InitialiseStory(story);
	InitialiseCave(cave, layout);

	AddItem(cave, 7, 3, "player");
    AddItem(cave, 2, 2, "boulder");
    AddItem(cave, 2, 3, "boulder");
    AddItem(cave, 4, 6, "boulder");
    AddItem(cave, 5, 7, "boulder");
    AddItem(cave, 6, 8, "boulder");
    AddItem(cave, 7, 1, "hole");
    AddItem(cave, 8, 3, "hole");
    AddItem(cave, 6, 4, "treasure");
    AddItem(cave, 3, 5, "treasure");
    AddItem(cave, 1, 1, "treasure");
    AddItem(cave, 8, 8, "treasure");
    AddItem(cave, 5, 1, "hole");
    AddItem(cave, 6, 1, "hole");

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		} else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}
