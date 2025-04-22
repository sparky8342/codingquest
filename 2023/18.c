#include "cvector.h"
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fptr;
    fptr = fopen("inputs/18.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    cvector_vector_type(char *) categories = NULL;
    int **amounts = NULL;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        int amount = 0;

        int spaces = 0;
        int str_start;
        int str_end;
        for (int i = 0; i < sizeof(buffer); i++) {
            if (buffer[i] == '\n') {
                str_end = i - 1;
                break;
            } else if (buffer[i] == ' ') {
                spaces++;
                if (spaces == 2) {
                    str_start = i + 1;
                }
            } else if (spaces == 1) {
                amount = amount * 10 + buffer[i] - '0';
            }
        }
        int len = str_end - str_start + 2;
        char category[len];
        int cat_i = 0;
        for (int i = str_start; i <= str_end; i++) {
            category[cat_i] = buffer[i];
            cat_i++;
        }
        category[cat_i] = '\0';

        int category_no = -1;
        for (int i = 0; i < cvector_size(categories); i++) {
            if (strncmp(categories[i], category, sizeof(category)) == 0) {
                category_no = i;
                break;
            }
        }
        if (category_no == -1) {
            cvector_push_back(categories, strdup(category));
            category_no = cvector_size(categories) - 1;
        }

        if (category_no == cvector_size(amounts)) {
            int *n = malloc(sizeof(int));
            *n = amount;
            cvector_push_back(amounts, n);
        } else {
            int *total = *cvector_at(amounts, category_no);
            *total += amount;
        }
    }

    fclose(fptr);

    long product = 1;
    for (int i = 0; i < cvector_size(amounts); i++) {
        product *= *amounts[i] % 100;
    }

    printf("%ld\n", product);

    cvector_free(categories);
    cvector_free(amounts);

    return 0;
}
