#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int WIDTH = 20000;
const int HEIGHT = 100000;

typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} RECTANGLE;

RECTANGLE *parse_line(char buffer[]) {
    RECTANGLE *rectangle = (RECTANGLE *)malloc(sizeof(RECTANGLE));

    int nums[4];
    int num = 0;

    int n = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == ' ' || buffer[i] == '\n') {
            nums[num] = n;
            num++;
            n = 0;
        } else {
            n = n * 10 + buffer[i] - '0';
        }
    }

    rectangle->start_x = nums[0];
    rectangle->start_y = nums[1];
    rectangle->end_x = nums[0] + nums[2] - 1;
    rectangle->end_y = nums[1] + nums[3] - 1;

    return rectangle;
}

int compare(const void *a, const void *b) {
    RECTANGLE *a_rect = *(RECTANGLE **)a;
    RECTANGLE *b_rect = *(RECTANGLE **)b;
    return a_rect->start_y - b_rect->start_y;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/7.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[100];
    int no_lines = 0;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        no_lines++;
    }
    rewind(fptr);

    RECTANGLE *rectangles[no_lines];

    int line = 0;
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        RECTANGLE *rectangle = parse_line(buffer);
        rectangles[line] = rectangle;
        line++;
    }

    qsort(rectangles, no_lines, sizeof(RECTANGLE *), compare);

    int total = 0;
    int x = 0;

    while (x <= WIDTH) {
        int y = -1;
        for (int i = 0; i < no_lines; i++) {
            if (rectangles[i]->start_x <= x && x <= rectangles[i]->end_x) {
                if (rectangles[i]->end_y <= y) {
                    continue;
                }

                if (y == -1 || rectangles[i]->start_y > y) {
                    y = rectangles[i]->start_y;
                } else if (rectangles[i]->start_y <= y) {
                    y++;
                }

                total += rectangles[i]->end_y - y + 1;
                y = rectangles[i]->end_y;
            }
        }

        x++;
    }

    printf("%d\n", WIDTH * HEIGHT - total);

    return 0;
}
