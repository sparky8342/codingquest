#include <stdio.h>

int width;
int height;

int main() {
    FILE *fptr;
    fptr = fopen("inputs/16.txt", "r");
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
    width = (width + 1) / 3;
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
            fscanf(fptr, "%x", &grid[row][col]);
        }
    }

    int diff;
    int bad_row;
    int bad_col;
    for (int row = 0; row < height - 1; row++) {
        int total = 0;
        for (int col = 0; col < width - 1; col++) {
            total += grid[row][col];
        }
        if (total % 256 != grid[row][width - 1]) {
            diff = total % 256 - grid[row][width - 1];
            if (diff < 0) {
                diff += 256;
            }
            bad_row = row;
            break;
        }
    }

    for (int col = 0; col < width - 1; col++) {
        int total = 0;
        for (int row = 0; row < height - 1; row++) {
            total += grid[row][col];
        }
        if (total % 256 != grid[height - 1][col]) {
            bad_col = col;
            break;
        }
    }

    int val = grid[bad_row][bad_col];
    printf("%d\n", val * (val - diff));

    return 0;
}
