#include "../utils/cvector.h"
#include <stdio.h>
#include <stdlib.h>

int outpost_id(char **outposts, char *outpost) {
    for (int i = 0; i < cvector_size(outposts); i++) {
        if (strncmp(outposts[i], outpost, strlen(outpost)) == 0) {
            return i;
        }
    }
    return -1;
}

int distance(int *distances, int size, int outpost1, int outpost2) {
    return distances[outpost1 + size * outpost2];
}

char **split_string(char *string) {
    char **strings = NULL;

    int p1 = 0;

    while (1) {
        while (string[p1] == ' ') {
            p1++;
        }

        int p2 = p1 + 1;
        while (string[p2] != ' ' && string[p2] != '\n') {
            p2++;
        }

        char *str = malloc((p2 - p1 + 1) * sizeof(char));
        int str_p = 0;
        for (int i = p1; i < p2; i++) {
            str[str_p] = string[i];
            str_p++;
        }
        str[str_p] = '\0';

        cvector_push_back(strings, str);

        if (string[p2] == '\n') {
            break;
        }

        p1 = p2;
    }

    return strings;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/32.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[300];
    fgets(buffer, sizeof(buffer), fptr);

    char **outposts = split_string(buffer);

    int size = cvector_size(outposts);

    int distances[size][size];

    for (int i = 0; i < size; i++) {
        fscanf(fptr, "%s", buffer);
        for (int j = 0; j < size; j++) {
            fscanf(fptr, "%d", &distances[i][j]);
        }
    }

    fgets(buffer, sizeof(buffer), fptr);
    fgets(buffer, sizeof(buffer), fptr);

    int total = 0;

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        char **route = split_string(buffer);

        for (int i = 3; i < cvector_size(route) - 1; i += 2) {
            total +=
                distance((int *)distances, size, outpost_id(outposts, route[i]),
                         outpost_id(outposts, route[i + 2]));
        }
    }

    printf("%d\n", total);

    return 0;
}
