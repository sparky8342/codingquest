#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pos {
    int x;
    int y;
    int steps;
    struct Pos *next;
} Pos;

int width;
int height;

void find_start_end(char grid[height][width], struct Pos *start,
                    struct Pos *end) {
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

    struct Pos *start = (struct Pos *)malloc(sizeof(struct Pos));
    start->steps = 1;
    struct Pos *end = (struct Pos *)malloc(sizeof(struct Pos));

    find_start_end(grid, start, end);

    // TODO look at using a linked list queue instead

    struct Pos *head = start;
    struct Pos *tail = start;

    visited[start->y][start->x] = true;

    static int dirs[] = {0, 1, 0, -1, 1, 0, -1, 0};

    while (1) {
        struct Pos *pos = head;

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

            tail->next = (struct Pos *)malloc(sizeof(struct Pos));
            tail = tail->next;
            tail->x = next_x;
            tail->y = next_y;
            tail->steps = pos->steps + 1;
            visited[tail->y][tail->x] = true;
        }

        struct Pos *last = head;
        head = head->next;
        free(last);
    }

    return 0;
}
