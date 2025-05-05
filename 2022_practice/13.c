#include <stdbool.h>
#include <stdio.h>

#define SIZE 20

int move(int grid[SIZE * SIZE], int pos, int die) {
    pos -= die;
    while (grid[pos] != 0) {
        pos -= grid[pos];
    }
    return pos;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/13.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int grid[SIZE * SIZE];

    bool reverse = false;
    for (int i = 0; i < SIZE; i++) {
        if (reverse) {
            for (int j = SIZE - 1; j >= 0; j--) {
                fscanf(fptr, "%d", &grid[i * SIZE + j]);
            }
        } else {
            for (int j = 0; j < SIZE; j++) {
                fscanf(fptr, "%d", &grid[i * SIZE + j]);
            }
        }
        reverse = !reverse;
    }

    int p1 = SIZE * SIZE - 1;
    int p2 = SIZE * SIZE - 1;
    int d1;
    int d2;
    int moves = 0;
    while (fscanf(fptr, "%d %d", &d1, &d2) == 2) {
        moves++;
        p1 = move(grid, p1, d1);
        if (p1 <= 0) {
            printf("%d\n", moves);
            break;
        }
        p2 = move(grid, p2, d2);
        if (p2 <= 0) {
            printf("%d\n", moves * 2);
            break;
        }
    }

    return 0;
}
