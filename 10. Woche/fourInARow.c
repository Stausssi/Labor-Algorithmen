//
// Created by Simon on 07.07.2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COL_COUNT 7
#define ROW_COUNT 6

typedef struct Board {
    char board[ROW_COUNT][COL_COUNT];
    char player;
} Board, *Board_p;

int findOpenRow(Board_p board, int col) {
    int row = ROW_COUNT;

    while (board->board[row][col] != ' ') row--;

    return row;
}

void move(Board_p board, int col) {
    int row = findOpenRow(board, col);

    if (row >= 0)
        board->board[row][col] = board->player;
}

bool hasWonStraight(Board_p board) {
    int count;
    for (int i = 0; i < COL_COUNT; ++i) {
        count = 0;
        for (int j = 0; j < ROW_COUNT; ++j) {
            if (board->board[j][i] == board->player) {
                if (++count == 4)
                    return true;
            } else
                count = 0;
        }
    }

    return false;
}

bool hasWonDiagonal1(Board_p board) {
//    int count;
//    for (int c = 1; c < COL_COUNT - 4; c++) {
//        count = 0;
//        for (int row = 0, col = c; row < ROW_COUNT && col < COL_COUNT; row++, col++) {
//            if (board->board[row][col] == board->player) {
//                if (count++ == 4)
//                    return true;
//            } else
//                count = 0;
//        }
//    }
    return false;
}

bool hasWonDiagonal2(Board_p board) {
//    int count;
//    for (int r = 0; r < ROW_COUNT - 4; r++) {
//        count = 0;
//        for (int col = 0, row = r; row < ROW_COUNT && col < COL_COUNT; row++, col++) {
//            if (board->board[row][col] == board->player) {
//                if (count++ == 4)
//                    return true;
//            } else
//                count = 0;
//        }
//    }
    return false;
}

bool hasWonFlat(Board_p board) {
    int count;
    for (int i = 0; i < ROW_COUNT; ++i) {
        count = 0;
        for (int j = 0; j < COL_COUNT; ++j) {
            if (board->board[i][j] == board->player) {
                if (++count == 4)
                    return true;
            } else
                count = 0;
        }
    }

    return false;
}

bool hasWon(Board_p board) {
    return hasWonDiagonal1(board) || hasWonDiagonal2(board) || hasWonFlat(board) || hasWonStraight(board);
}

void printBoard(Board_p b) {
    system("clear");

    for (int i = 0; i < ROW_COUNT; ++i) {
        fprintf(stdout, "|");
        for (int j = 0; j < COL_COUNT; ++j) {
            fprintf(stdout, "%c", b->board[i][j]);
        }
        fprintf(stdout, "|\n");
    }
    fprintf(stdout, "+-------+\n");
    fprintf(stdout, "Player %c> ", b->player == 'X' ? 'O' : 'X');
}

int main(int argc, char *argv[]) {
    FILE *in = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage:_%s_[<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    Board_p board = malloc(sizeof(Board));
    board->player = 'X';

    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COL_COUNT; ++j)
            board->board[i][j] = ' ';
    }


    char *input = malloc(sizeof(char) * 2);
    int col;

    printBoard(board);

    do {
        input = fgets(input, 2, in);
        col = atoi(input);

        if (col > 0 && col < COL_COUNT) {
            board->player = board->player == 'X' ? 'O' : 'X';

            move(board, col - 1);
            printBoard(board);
        }
    } while (!hasWon(board));

    fprintf(stdout, "%c hat gewonnen!", board->player);

    if (in != stdin) {
        fclose(in);
    }

    exit(EXIT_SUCCESS);
}
