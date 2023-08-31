#include<stdio.h>
#define EMPTY -1

typedef struct point_t {
    int x;
    int y;
} point_t;

int board[6][8];

void initBoard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = EMPTY;
        }
    }
}

point_t getInput(int player) {

    while (1) {

        point_t input;

        printf("player %c, enter a column: ", player ? 'X' : 'O');

        scanf("%d", &input.x);
        input.x -= 1;

        if (input.x < 0 || input.x > 7) {
            printf("invalid column!\n");
            continue;
        }

        int row = 0;

        while (row < 6 && board[row][input.x] != EMPTY) {
            row++;
        }

        if (row == 6) {
            printf("column %d is full!\n", input.x+1);
            continue;
        }

        input.y = row;

        // printf("[DEBUG] player %c placed a piece at (%d, %d)\n", player ? 'X' : 'O', input.x+1, input.y+1);
        printf("\n");

        return input;
    }
}

void printBoard() {
    for (int i = 5; i >= 0; i--) {
        printf("\n---------------------------------\n");
        printf("|");
        for (int j = 0; j < 8; j++) {
            printf("%s|", board[i][j] < 0 ? "   " : board[i][j] ? " X " : " O ");
        }
    }
    printf("\n=================================\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
    printf("=================================\n");

}

void updateBoard(point_t input, int player) {

    board[input.y][input.x] = player;
    printBoard();
}

point_t directions[8] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};

void checkWinner(int *p1, int *p2) {
    // yeah there are cleaner ways I know
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            
            if (board[i][j] == 1) {

                for (int d = 0; d < 8; d++) {
                    int count = 0;
                    int x = j;
                    int y = i;
                    while (x >= 0 && x < 8 && y >= 0 && y < 6 && board[y][x] == 1) {
                        count++;
                        x += directions[d].x;
                        y += directions[d].y;
                    }
                    if (count >= 4) {
                        *p1 = 1;
                        printf("player X wins!\n");
                        return;
                    }
                }

            } else {

                for (int d = 0; d < 8; d++) {
                    int count = 0;
                    int x = j;
                    int y = i;
                    while (x >= 0 && x < 8 && y >= 0 && y < 6 && board[y][x] == 0) {
                        count++;
                        x += directions[d].x;
                        y += directions[d].y;
                    }
                    if (count >= 4) {
                        *p2 = 1;
                        printf("player O wins!\n");
                        return;
                    }
                }

            }
        }
    }
}

int main() {

    printf("press ctrl+c to quit\n\n");

    initBoard();
    printBoard();

    int moves = 0;
    int won1 = 0;
    int won2 = 0;
    int player = 1;

    while (!won1 && !won2 && moves <= 48) {

        point_t input = getInput(player);
        updateBoard(input, player);
        checkWinner(&won1, &won2);
        
        player ^= 1;
    }

    if (!won1 && !won2) {
        printf("draw!\n");
    }

    return 0;
}