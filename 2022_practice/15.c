#include <stdio.h>

int width;
int height;

void dfs(int grid[height][width], int row, int col, int *mass) {
    if (row < 0 || row == height || col < 0 || col == width ||
        grid[row][col] == 0) {
        return;
    }

    *mass += grid[row][col];
    grid[row][col] = 0;

    dfs(grid, row - 1, col, mass);
    dfs(grid, row + 1, col, mass);
    dfs(grid, row, col - 1, mass);
    dfs(grid, row, col + 1, mass);
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/15.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[1000];
    fgets(buffer, sizeof(buffer), fptr);
    for (int i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            width = i;
            break;
        }
    }
    width = (width + 1) / 2;
    height = 1;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (buffer[0] == '\n') {
            break;
        }
        height++;
    }
    rewind(fptr);

    // create and read in grid
    int grid[height][width];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fscanf(fptr, "%d", &grid[row][col]);
        }
    }

    int asteroids = 0;
    int total = 0;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (grid[row][col] != 0) {
                int mass = 0;
                dfs(grid, row, col, &mass);
                total += mass;
                asteroids++;
            }
        }
    }

    printf("%d\n", total / asteroids);

    return 0;
}
