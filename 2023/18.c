#include "../utils/cvector.h"
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

    char category[100];
    int amount;
    while (fscanf(fptr, "%s %d %s", category, &amount, category) == 3) {
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
