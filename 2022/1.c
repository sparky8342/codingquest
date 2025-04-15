#include <stdio.h>
#include <stdlib.h>

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

    int size = 1;
    int *nums = malloc(size * sizeof(int));
    if (nums == NULL) {
        printf("Cannot malloc\n");
        return 1;
    }

    int index = 0;
    while (fscanf(fptr, "%d", &nums[index]) == 1) {
        index++;
        if (index == size) {
            size *= 2;
            nums = realloc(nums, size * sizeof(int));
            if (nums == NULL) {
                printf("Cannot realloc\n");
                return 1;
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < 60; i++) {
        sum += nums[i];
    }

    int seconds = check_avg(sum);

    for (int i = 60; i < index; i++) {
        sum = sum + nums[i] - nums[i - 60];
        seconds += check_avg(sum);
    }

    free(nums);

    printf("%d\n", seconds);

    return 0;
}
