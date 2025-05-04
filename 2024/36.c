#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pos {
    int grid_id;
    int x;
    int y;
    int steps;
    struct Pos *next;
} Pos;

int width;
int height;

int main() {
    FILE *fptr;
    fptr = fopen("inputs/36.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    // get size of grid
    char buffer[1000];
    fgets(buffer, sizeof(buffer), fptr);
    for (int i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            width = i;
            break;
        }
    }
    height = 1;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (buffer[0] == '\n') {
            break;
        }
        height++;
    }
    rewind(fptr);

    // create and read in grids
    char grid[2][height][width];
    bool visited[2][height][width];
    for (int grid_id = 0; grid_id <= 1; grid_id++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                visited[grid_id][y][x] = false;
            }
        }
    }

    for (int grid_id = 0; grid_id <= 1; grid_id++) {
        for (int row = 0; row < height; row++) {
            fgets(buffer, sizeof(buffer), fptr);
            memcpy(grid[grid_id][row], buffer, width);
        }
        fgets(buffer, sizeof(buffer), fptr);
    }

    struct Pos *start = (struct Pos *)malloc(sizeof(struct Pos));
    start->grid_id = 0;
    start->x = 0;
    start->y = 1;
    start->steps = 0;
    struct Pos *end = (struct Pos *)malloc(sizeof(struct Pos));
    end->grid_id = 0;
    end->x = width - 1;
    end->y = height - 2;

    struct Pos *head = start;
    struct Pos *tail = start;

    visited[start->grid_id][start->y][start->x] = true;

    static int dirs[] = {0, 1, 0, -1, 1, 0, -1, 0};

    int len = 1;
    while (len > 0) {
        struct Pos *pos = head;

        if (pos->x == end->x && pos->y == end->y &&
            pos->grid_id == end->grid_id) {
            printf("%d\n", pos->steps);
            break;
        }

        for (int i = 0; i < 8; i += 2) {
            int next_grid_id = pos->grid_id;
            int next_x = pos->x + dirs[i];
            int next_y = pos->y + dirs[i + 1];
            if (next_x < 0 || next_x == width || next_y < 0 ||
                next_y == height) {
                continue;
            }
            if (grid[next_grid_id][next_y][next_x] == '#') {
                continue;
            }
            if (visited[next_grid_id][next_y][next_x] == true) {
                continue;
            }

            tail->next = (struct Pos *)malloc(sizeof(struct Pos));
            tail = tail->next;
            tail->grid_id = next_grid_id;
            tail->x = next_x;
            tail->y = next_y;
            tail->steps = pos->steps + 1;
            visited[tail->grid_id][tail->y][tail->x] = true;
            len++;
        }
        if (grid[pos->grid_id][pos->y][pos->x] == '$') {
            tail->next = (struct Pos *)malloc(sizeof(struct Pos));
            tail = tail->next;
            tail->grid_id = (pos->grid_id + 1) % 2;
            tail->x = pos->x;
            tail->y = pos->y;
            tail->steps = pos->steps;
            visited[tail->grid_id][tail->y][tail->x] = true;
            len++;
        }

        struct Pos *last = head;
        head = head->next;
        free(last);
        len--;
    }

    return 0;
}
