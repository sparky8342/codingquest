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

void scan(char grid[height][width], Pos *start, Pos *end) {
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

    scan(grid, start, end);

    // TODO look at using a linked list queue instead
    Pos **queue = NULL;
    cvector_push_back(queue, start);
    visited[start->y][start->x] = true;

    while (cvector_size(queue) > 0) {
        Pos *pos = *cvector_at(queue, 0);
        cvector_erase(queue, 0);

        if (pos->x == end->x && pos->y == end->y) {
            printf("%d\n", pos->steps);
            break;
        }

        if (pos->y > 0 && grid[pos->y - 1][pos->x] == ' ' &&
            visited[pos->y - 1][pos->x] == false) {
            Pos *next = (Pos *)malloc(sizeof(Pos));
            next->x = pos->x;
            next->y = pos->y - 1;
            next->steps = pos->steps + 1;
            cvector_push_back(queue, next);
            visited[next->y][next->x] = true;
        }
        if (pos->y < height - 1 && grid[pos->y + 1][pos->x] == ' ' &&
            visited[pos->y + 1][pos->x] == false) {
            Pos *next = (Pos *)malloc(sizeof(Pos));
            next->x = pos->x;
            next->y = pos->y + 1;
            next->steps = pos->steps + 1;
            cvector_push_back(queue, next);
            visited[next->y][next->x] = true;
        }
        if (pos->x > 0 && grid[pos->y][pos->x - 1] == ' ' &&
            visited[pos->y][pos->x - 1] == false) {
            Pos *next = (Pos *)malloc(sizeof(Pos));
            next->x = pos->x - 1;
            next->y = pos->y;
            next->steps = pos->steps + 1;
            cvector_push_back(queue, next);
            visited[next->y][next->x] = true;
        }
        if (pos->x < width - 1 && grid[pos->y][pos->x + 1] == ' ' &&
            visited[pos->y][pos->x + 1] == false) {
            Pos *next = (Pos *)malloc(sizeof(Pos));
            next->x = pos->x + 1;
            next->y = pos->y;
            next->steps = pos->steps + 1;
            cvector_push_back(queue, next);
            visited[next->y][next->x] = true;
        }
    }

    return 0;
}
