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
    int boards[2] = {0, 0};

    for (int i = 0; i < 9; i++) {
        int player = (i & 1);
        boards[player] |= (1 << (moves[i] - 1));
        if (check_win(boards[player])) {
            return player + 1;
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

    int results[3] = {0, 0, 0};

    int moves[9];
    while (fscanf(fptr, "%d %d %d %d %d %d %d %d %d", &moves[0], &moves[1],
                  &moves[2], &moves[3], &moves[4], &moves[5], &moves[6],
                  &moves[7], &moves[8]) == 9) {

        int winner = play_moves(moves);
        results[winner]++;
    }
    fclose(fptr);

    printf("%d\n", results[0] * results[1] * results[2]);

    return 0;
}
