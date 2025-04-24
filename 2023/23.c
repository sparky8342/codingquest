#include <stdbool.h>
#include <stdio.h>

#define SIZE 100

void find_gap(bool grid[SIZE][SIZE], int *ret_x, int *ret_y) {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (!grid[y][x]) {
                *ret_x = x;
                *ret_y = y;
                return;
            }
        }
    }
}

int main() {
    bool grid[SIZE][SIZE];
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            grid[y][x] = false;
        }
    }

    FILE *fptr;
    fptr = fopen("inputs/23.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int x;
    int y;
    int vx;
    int vy;

    while (fscanf(fptr, "%d %d %d %d", &x, &y, &vx, &vy) == 4) {
        for (int i = 3600; i < 3660; i++) {
            int px = x + i * vx;
            int py = y + i * vy;
            if (px >= 0 && px < SIZE && py >= 0 && py < SIZE) {
                grid[py][px] = true;
            }
        }
    }

    fclose(fptr);

    find_gap(grid, &x, &y);
    printf("%d:%d\n", x, y);

    return 0;
}
