#include "cvector.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[4];
    char **neighbours;
    int **distances;
} Beacon;

int main() {
    FILE *fptr;
    fptr = fopen("inputs/27.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    // EAR => DEV:2694 MGE:4668 TYT:8730

    Beacon **beacons = NULL;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        Beacon *beacon = (Beacon *)malloc(sizeof(Beacon));
        beacon->name[0] = buffer[0];
        beacon->name[1] = buffer[1];
        beacon->name[2] = buffer[2];
        beacon->name[3] = '\0';
        beacon->neighbours = NULL;
        beacon->distances = NULL;

        int i = 7;
        while (1) {
            char *name = (char *)malloc(sizeof(char) * 4);
            name[0] = buffer[i];
            name[1] = buffer[i + 1];
            name[2] = buffer[i + 2];
            name[3] = '\0';
            i += 4;
            int *distance = (int *)malloc(sizeof(int));
            *distance = 0;
            while (buffer[i] >= '0' && buffer[i] <= '9') {
                *distance = *distance * 10 + buffer[i] - '0';
                i++;
            }
            cvector_push_back(beacon->neighbours, name);
            cvector_push_back(beacon->distances, distance);
            if (buffer[i] == '\n') {
                break;
            }
            i++;
        }

        cvector_push_back(beacons, beacon);
    }

    for (int i = 0; i < cvector_size(beacons); i++) {
        printf("%s\n", beacons[i]->name);
        for (int j = 0; j < cvector_size(beacons[i]->neighbours); j++) {
            printf("    %s %d\n", beacons[i]->neighbours[j],
                   *beacons[i]->distances[j]);
        }
    }

    return 0;
}
