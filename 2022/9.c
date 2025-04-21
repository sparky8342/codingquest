#include "cvector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
    int steps;
} Pos;

int width;
int height;

void find_start_end(char grid[height][width], Pos *start, Pos *end) {
    for (int x = 0; x < width; x++) {
        if (grid[0][x] == ' ') {
            start->x = x;
            end->y = 0;
        }
        if (grid[height - 1][x] == ' ') {
            end->x = x;
            end->y = height - 1;
        }
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/9.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    // get size of grid
    char buffer[1000];
    fgets(buffer, sizeof(buffer), fptr);
    for (int i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            width = i - 1;
            break;
        }
    }
    height = 1;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (buffer[0] == ' ') {
            break;
        }
        height++;
    }
    rewind(fptr);

    // create and read in grid
    char grid[height][width];
    bool visited[height][width];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            visited[y][x] = false;
        }
    }

    for (int row = 0; row < height; row++) {
        fgets(buffer, sizeof(buffer), fptr);
        memcpy(grid[row], buffer, width);
    }

    Pos *start = (Pos *)malloc(sizeof(Pos));
    start->steps = 1;
    Pos *end = (Pos *)malloc(sizeof(Pos));

    find_start_end(grid, start, end);

    // TODO look at using a linked list queue instead
    Pos **queue = NULL;
    cvector_push_back(queue, start);
    visited[start->y][start->x] = true;

    static int dirs[] = {0, 1, 0, -1, 1, 0, -1, 0};

    while (cvector_size(queue) > 0) {
        Pos *pos = *cvector_at(queue, 0);
        cvector_erase(queue, 0);

        if (pos->x == end->x && pos->y == end->y) {
            printf("%d\n", pos->steps);
            break;
        }

        for (int i = 0; i < 8; i += 2) {
            int next_x = pos->x + dirs[i];
            int next_y = pos->y + dirs[i + 1];
            if (next_x < 0 || next_x == width || next_y < 0 ||
                next_y == height) {
                continue;
            }
            if (grid[next_y][next_x] == '#') {
                continue;
            }
            if (visited[next_y][next_x] == true) {
                continue;
            }

            Pos *next = (Pos *)malloc(sizeof(Pos));
            next->x = next_x;
            next->y = next_y;
            next->steps = pos->steps + 1;
            cvector_push_back(queue, next);
            visited[next->y][next->x] = true;
        }
    }

    cvector_free(queue);

    return 0;
}
