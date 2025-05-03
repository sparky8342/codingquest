#include "../utils/cvector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct File {
    char *name;
    int size;
    struct File **files;
};

void dfs(struct File *file, long *total, bool delete) {
    if (delete || strstr(file->name, "temporary") != NULL ||
        strstr(file->name, "delete") != NULL) {
        *total += file->size;
        delete = true;
    }

    for (int i = 0; i < cvector_size(file->files); i++) {
        dfs(file->files[i], total, delete);
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/34.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int size;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (buffer[0] == 'F') {
            int i = 8;
            int n = 0;
            while (buffer[i] >= '0' && buffer[i] <= '9') {
                n = n * 10 + buffer[i] - '0';
                i++;
            }
            size = n;
        }
    }
    size++;

    struct File **files = (struct File **)malloc(sizeof(struct File *) * size);
    for (int i = 0; i < size; i++) {
        files[i] = malloc(sizeof(struct File));
        files[i]->files = NULL;
        files[i]->size = 0;
    }
    files[0]->name = "/";

    int folder_no = -1;

    rewind(fptr);
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        if (buffer[0] == 'F') {
            folder_no++;
            continue;
        }

        int i = 3;
        while (buffer[i] != ' ') {
            i++;
        }

        char *name = malloc(sizeof(char) * (i - 3 + 1));
        int name_p = 0;
        for (int j = 3; j < i; j++) {
            name[name_p] = buffer[j];
            name_p++;
        }
        name[name_p] = '\0';

        i++;
        if (buffer[i] >= '0' && buffer[i] <= '9') {
            int n = 0;
            while (buffer[i] >= '0' && buffer[i] <= '9') {
                n = n * 10 + buffer[i] - '0';
                i++;
            }

            struct File *file = malloc(sizeof(struct File));
            file->name = name;
            file->size = n;
            file->files = NULL;

            cvector_push_back(files[folder_no]->files, file);
        } else {
            while (buffer[i] != ' ') {
                i++;
            }
            i++;
            int n = 0;
            while (buffer[i] != ']') {
                n = n * 10 + buffer[i] - '0';
                i++;
            }
            files[n]->name = name;

            cvector_push_back(files[folder_no]->files, files[n]);
        }
    }

    long total = 0;
    dfs(files[0], &total, false);

    printf("%ld\n", total);

    return 0;
}
