#include "cvector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define START "TYC"
#define END "EAR"
#define STOP_TIME 600

typedef struct {
    char name[4];
    char **neighbours;
    int **distances;
    int distance;
    bool visited;
} Beacon;

int heap_parent(int i) { return (i - 1) / 2; }
int heap_left(int i) { return 2 * i + 1; }
int heap_right(int i) { return 2 * i + 2; }

void **heap_insert(Beacon **heap, Beacon *beacon) {
    cvector_push_back(heap, beacon);
    int i = cvector_size(heap) - 1;
    while (i != 0) {
        int parent = heap_parent(i);
        if (heap[parent]->distance > heap[i]->distance) {
            Beacon *tmp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = tmp;
            i = parent;
        } else {
            break;
        }
    }
}

void min_heapify(Beacon **heap, int i) {
    int l = heap_left(i);
    int r = heap_right(i);
    int smallest = i;
    if (l < cvector_size(heap) && heap[l]->distance < heap[i]->distance) {
        smallest = l;
    }
    if (r < cvector_size(heap) &&
        heap[r]->distance < heap[smallest]->distance) {
        smallest = r;
    }
    if (smallest != i) {
        Beacon *tmp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = tmp;
        min_heapify(heap, smallest);
    }
}

Beacon *heap_pop(Beacon **heap) {
    Beacon *min = heap[0];
    heap[0] = heap[cvector_size(heap) - 1];
    cvector_pop_back(heap);
    min_heapify(heap, 0);
    return min;
}

Beacon *get_beacon(Beacon **beacons, char *name) {
    for (int i = 0; i < cvector_size(beacons); i++) {
        if (strncmp(beacons[i]->name, name, sizeof(name)) == 0) {
            return beacons[i];
        }
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/27.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

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
        beacon->distance = 999999999;
        beacon->visited = false;

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

    Beacon **heap = NULL;
    Beacon *start = get_beacon(beacons, START);
    start->distance = 0;
    cvector_push_back(heap, start);

    while (cvector_size(heap) > 0) {
        Beacon *beacon = heap_pop(heap);

        if (strncmp(beacon->name, END, 3) == 0) {
            printf("%d\n", beacon->distance - STOP_TIME);
            break;
        }

        if (beacon->visited) {
            continue;
        }
        beacon->visited = true;

        for (int i = 0; i < cvector_size(beacon->neighbours); i++) {
            Beacon *neighbour = get_beacon(beacons, beacon->neighbours[i]);
            int distance = beacon->distance + *beacon->distances[i] + STOP_TIME;
            if (distance < neighbour->distance) {
                neighbour->distance = distance;
                heap_insert(heap, neighbour);
            }
        }
    }

    return 0;
}
