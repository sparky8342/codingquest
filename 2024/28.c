#include "../utils/ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr;
    fptr = fopen("inputs/28.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    ht *spacelines = ht_create();

    char spaceline[100];
    char item[100];
    int amount;
    while (fscanf(fptr, "%s %s %d", spaceline, item, &amount) == 3) {
        if (strcmp(item, "Discount") == 0 || strcmp(item, "Rebate") == 0) {
            amount *= -1;
        }

        void *value = ht_get(spacelines, spaceline);
        if (value == NULL) {
            int *total = malloc(sizeof(int));
            *total = amount;
            ht_set(spacelines, spaceline, total);
        } else {
            int *total = (int *)value;
            *total += amount;
        }
    }

    fclose(fptr);

    int cheapest = 9999999;
    hti it = ht_iterator(spacelines);
    while (ht_next(&it)) {
        int n = *(int *)it.value;
        if (n < cheapest) {
            cheapest = n;
        }
    }

    printf("%d\n", cheapest);

    return 0;
}
