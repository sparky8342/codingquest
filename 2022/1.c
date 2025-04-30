#include <stdio.h>
#include <stdlib.h>
#include "../utils/vector.h"

int check_avg(int sum) {
    int avg = sum / 60;
    if (avg < 1500 || avg > 1600) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/1.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    vector nums;
    vector_init(&nums);

    int n;
    while (fscanf(fptr, "%d", &n) == 1) {
        vector_push(&nums, n);
    }

    int sum = 0;
    for (int i = 0; i < 60; i++) {
        sum += vector_get(&nums, i);
    }

    int seconds = check_avg(sum);

    for (int i = 60; i < vector_len(&nums); i++) {
        sum = sum + vector_get(&nums, i) - vector_get(&nums, i - 60);
        seconds += check_avg(sum);
    }

    vector_free(&nums);

    printf("%d\n", seconds);

    return 0;
}
