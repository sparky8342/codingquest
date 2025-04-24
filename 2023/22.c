#include <stdbool.h>
#include <stdio.h>

#define HEIGHT 10
#define WIDTH 50

int main() {
    bool grid[HEIGHT][WIDTH];
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = false;
        }
    }

    FILE *fptr;
    fptr = fopen("inputs/22.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int start_x;
    int start_y;
    int width;
    int height;

    while (fscanf(fptr, "%d %d %d %d", &start_x, &start_y, &width, &height) ==
           4) {
        for (int y = start_y; y < start_y + height; y++) {
            for (int x = start_x; x < start_x + width; x++) {
                grid[y][x] = !grid[y][x];
            }
        }
    }

    fclose(fptr);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x]) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
