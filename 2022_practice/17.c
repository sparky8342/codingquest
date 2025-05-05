#include "../utils/cvector.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
    FILE *fptr;

    char **codes = NULL;
    char **letters = NULL;

    fptr = fopen("17_lookup.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[500];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        char *letter = malloc(sizeof(char));
        *letter = buffer[0];
        cvector_push_back(letters, letter);

        int i = 3;
        while (buffer[i] != '\n') {
            i++;
        }

        char *code = malloc(sizeof(char) * i - 3 + 2);
        int code_p = 0;
        for (int j = 2; j < i; j++) {
            code[code_p] = buffer[j];
            code_p++;
        }
        code[code_p] = '\0';

        cvector_push_back(codes, code);
    }
    fclose(fptr);

    fptr = fopen("inputs/17.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    fgets(buffer, sizeof(buffer), fptr);
    fclose(fptr);

    char binary[2000];
    int bin_p = 0;

    for (int i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            break;
        }
        int n;
        if (buffer[i] >= 'a') {
            n = buffer[i] - 'a' + 10;
        } else {
            n = buffer[i] - '0';
        }

        char buf[5];
        sprintf(buf, "%04b", n);

        for (int j = 0; j < 4; j++) {
            binary[bin_p] = buf[j];
            bin_p++;
        }
    }
    binary[bin_p] = '\0';

    int p1 = 0;
    int p2 = 3;

    while (p2 <= bin_p) {
        char str[p2 - p1 + 1];
        int str_p = 0;
        for (int i = p1; i <= p2; i++) {
            str[str_p] = binary[i];
            str_p++;
        }
        str[str_p] = '\0';

        bool found = false;
        for (int i = 0; i < cvector_size(codes); i++) {
            if (strncmp(str, codes[i], sizeof(codes[i])) == 0) {
                printf("%c", letters[i][0]);
                found = true;
                break;
            }
        }
        if (found) {
            p1 = p2 + 1;
            p2 = p1 + 2;
        }

        p2++;
    }

    printf("\n");

    return 0;
}
