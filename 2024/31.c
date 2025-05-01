#include "../utils/cvector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float z;
} Star;

float dist(Star *star1, Star *star2) {
    return sqrt(pow(star1->x - star2->x, 2) + pow(star1->y - star2->y, 2) +
                pow(star1->z - star2->z, 2));
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/31.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Star **stars = NULL;

    char buffer[100];
    fgets(buffer, sizeof(buffer), fptr);

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        int i = 0;
        int spaces = 0;
        while (1) {
            if (buffer[i] == ' ') {
                spaces++;
                if (spaces == 2) {
                    break;
                }
            } else if (spaces == 1) {
                spaces = 0;
            }
            i++;
        }

        float nums[4];

        for (int j = 0; j < 4; j++) {
            while (buffer[i] == ' ') {
                i++;
            }

            char str[8];
            int str_p = 0;

            while (buffer[i] != ' ') {
                str[str_p] = buffer[i];
                i++;
                str_p++;
            }
            str[str_p] = '\0';

            nums[j] = atof(str);
        }

        Star *star = (Star *)malloc(sizeof(Star));
        star->x = nums[1];
        star->y = nums[2];
        star->z = nums[3];
        cvector_push_back(stars, star);
    }

    fclose(fptr);

    float smallest = 9999999.0;

    for (int i = 0; i < cvector_size(stars); i++) {
        for (int j = i + 1; j < cvector_size(stars); j++) {
            float d = dist(stars[i], stars[j]);
            if (d < smallest) {
                smallest = d;
            }
        }
    }

    printf("%.3f\n", smallest);

    cvector_free(stars);

    return 0;
}
