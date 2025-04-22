#include <stdbool.h>
#include <stdio.h>

bool check_win(int board) {
    static int wins[8] = {0b111000000, 0b000111000, 0b000000111, 0b100100100,
                          0b010010010, 0b001001001, 0b100010001, 0b001010100};
    for (int i = 0; i < 8; i++) {
        if ((board & wins[i]) == wins[i]) {
            return true;
        }
    }
    return false;
}

int play_moves(int moves[9]) {
    int board1 = 0;
    int board2 = 0;

    for (int i = 0; i < 9; i++) {
        int player = (i & 1) + 1;

        if (player == 1) {
            board1 |= (1 << (moves[i] - 1));
            if (check_win(board1)) {
                return 1;
            }
        } else if (player == 2) {
            board2 |= (1 << (moves[i] - 1));
            if (check_win(board2)) {
                return 2;
            }
        }
    }

    return 0;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/20.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int wins1 = 0;
    int wins2 = 0;
    int draws = 0;

    int moves[9];
    while (fscanf(fptr, "%d %d %d %d %d %d %d %d %d", &moves[0], &moves[1],
                  &moves[2], &moves[3], &moves[4], &moves[5], &moves[6],
                  &moves[7], &moves[8]) == 9) {

        int winner = play_moves(moves);
        if (winner == 1) {
            wins1++;
        } else if (winner == 2) {
            wins2++;
        } else {
            draws++;
        }
    }
    fclose(fptr);

    printf("%d\n", wins1 * wins2 * draws);

    return 0;
}
