#include <stdbool.h>
#include <stdio.h>

int main() {
    FILE *fptr;
    fptr = fopen("inputs/30.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int val = true;
    int col = 0;
    char c;
    int len = 0;
    while (c = fgetc(fptr)) {
        if (c == ' ' || c == '\n') {
            for (int i = 0; i < len; i++) {
                if (val) {
                    printf("#");
                } else {
                    printf(".");
                }
                col++;
                if (col == 100) {
                    printf("\n");
                    col = 0;
                }
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

    return 0;
}
