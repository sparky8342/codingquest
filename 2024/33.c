#include <stdbool.h>
#include <stdio.h>

void find_letter(char grid[25], char letter, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i * 5 + j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int main() {
    bool alphabet[26];
    for (int i = 0; i < 26; i++) {
        alphabet[i] = true;
    }
    alphabet[9] = false; // skip j

    FILE *fptr;
    fptr = fopen("inputs/33.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[100];
    char key[50];
    fgets(buffer, sizeof(buffer), fptr);
    fscanf(fptr, "%s %s %s", key, key, key);
    fgets(buffer, sizeof(buffer), fptr);
    fgets(buffer, sizeof(buffer), fptr);
    fgets(buffer, sizeof(buffer), fptr);

    char grid[25];
    int grid_p;

    for (int i = 0; i < sizeof(key); i++) {
        if (key[i] == '\0') {
            grid_p = i;
            break;
        }
        alphabet[key[i] - 'a'] = false;
        grid[i] = key[i];
    }

    for (int i = 0; i < 26; i++) {
        if (alphabet[i] == true) {
            grid[grid_p] = i + 'a';
            grid_p++;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", grid[j + 5 * i]);
        }
        printf("\n");
    }

    for (int i = 9; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            break;
        } else if (buffer[i] == ' ') {
            continue;
        }

        int row1;
        int col1;
        find_letter(grid, buffer[i], &row1, &col1);

        int row2;
        int col2;
        find_letter(grid, buffer[i + 1], &row2, &col2);

        if (row1 != row2 && col1 != col2) {
            buffer[i] = grid[row1 * 5 + col2];
            buffer[i + 1] = grid[row2 * 5 + col1];
        } else if (row1 == row2) {
            int c1 = col1 - 1;
            if (c1 == -1) {
                c1 = 4;
            }
            int c2 = col2 - 1;
            if (c2 == -1) {
                c2 = 4;
            }
            buffer[i] = grid[row1 * 5 + c1];
            buffer[i + 1] = grid[row2 * 5 + c2];
        } else if (col1 == col2) {
            int r1 = row1 - 1;
            if (r1 == -1) {
                r1 = 4;
            }
            int r2 = row2 - 1;
            if (r2 == -1) {
                r2 = 4;
            }
            buffer[i] = grid[r1 * 5 + col1];
            buffer[i + 1] = grid[r2 * 5 + col1];
        }

        i++;
    }

    printf("%s\n", buffer);

    return 0;
}
