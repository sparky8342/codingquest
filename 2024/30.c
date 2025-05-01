#include <stdbool.h>
#include <stdio.h>

int main() {
    bool grid[8000];

    FILE *fptr;
    fptr = fopen("inputs/30.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int val = true;
    int p = 0;
    char c;
    int len = 0;
    while (c = fgetc(fptr)) {
        if (c == ' ' || c == '\n') {
            for (int i = 0; i < len; i++) {
                grid[p] = val;
                p++;
            }
            if (c == '\n') {
                break;
            }
            val = !val;
            len = 0;
        } else {
            len = len * 10 + c - '0';
        }
    }
    fclose(fptr);

    for (int y = 0; y < 80; y++) {
        for (int x = 0; x < 100; x++) {
            if (grid[y * 100 + x]) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }

    return 0;
}
