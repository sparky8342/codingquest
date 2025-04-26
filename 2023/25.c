#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int total_distance(int *distances, int path[], int len) {
    int distance = 0;
    for (int i = 0; i < len - 1; i++) {
        distance += distances[path[i] + len * path[i + 1]];
    }
    distance += distances[path[len - 1]];
    return distance;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/25.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char line[1024], *p, *e;
    int num;
    int count = 0;
    fgets(line, sizeof(line), fptr);
    for (p = line;; p = e) {
        num = (int)strtol(p, &e, 10);
        if (p == e) {
            break;
        }
        count++;
    }
    rewind(fptr);

    int distances[count][count];

    for (int i = 0; i < count; i++) {
        fgets(line, sizeof(line), fptr);
        int index = 0;
        for (p = line;; p = e) {
            num = (int)strtol(p, &e, 10);
            distances[i][index] = num;
            if (p == e) {
                break;
            }
            index++;
        }
    }

    int path[count];
    for (int i = 0; i < count; i++) {
        path[i] = i;
    }

    srand(time(NULL));

    // run until the path doesn't seem to get smaller
    // this doesn't always get the best solution
    // I think it gets stuck in a local minima
    // which would need more than 2 edges swapped
    while (1) {
        int a = rand() % count;
        int b = rand() % count;

        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        if (a == b || a + 1 == b || b + 1 == a) {
            continue;
        }

        // 0 1 2 3 4 5 6 7 8 9 0
        // 0 1 2   3 4 5 6 7   8 9 0

        int dist1 = distances[path[a]][path[a + 1]] +
                    distances[path[b]][path[(b + 1) % count]];
        int dist2 = distances[path[a]][path[b]] +
                    distances[path[a + 1]][path[(b + 1) % count]];

        if (dist2 <= dist1) {
            int p1 = a + 1;
            int p2 = b;
            while (p1 < p2) {
                int tmp = path[p1];
                path[p1] = path[p2];
                path[p2] = tmp;
                p1++;
                p2--;
            }

            if (dist2 < dist1) {
                printf("%d\n", total_distance((int *)distances, path, count));
            }
        }
    }

    return 0;
}
