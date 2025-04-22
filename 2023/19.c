#include <stdio.h>

int bitcount(int n) {
    int c = 0;
    while (n > 0) {
        if (n & 1 == 1) {
            c++;
        }
        n >>= 1;
    }
    return c;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/19.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int total = 0;
    int amount = 0;

    int n;
    while (fscanf(fptr, "%d", &n) == 1) {
        if ((bitcount(n) & 1) == 0) {
            n &= 0b111111111111111;
            total += n;
            amount++;
        }
    }
    fclose(fptr);

    float avg = (float)total / (float)amount;
    printf("%0.f\n", avg);

    return 0;
}
