#include "../utils/ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr;
    fptr = fopen("inputs/18.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    ht *categories = ht_create();

    char category[100];
    int amount;
    while (fscanf(fptr, "%s %d %s", category, &amount, category) == 3) {
        void *value = ht_get(categories, category);
        if (value != NULL) {
            int *cat_amount = (int *)value;
            *cat_amount += amount;
            continue;
        }

        int *cat_amount = malloc(sizeof(int));
        *cat_amount = amount;
        ht_set(categories, category, cat_amount);
    }

    fclose(fptr);

    long product = 1;
    hti it = ht_iterator(categories);
    while (ht_next(&it)) {
        product *= *(int *)it.value % 100;
    }

    printf("%ld\n", product);

    return 0;
}
