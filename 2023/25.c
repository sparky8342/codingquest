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

    // random swap edges, keep the swap if it's shorter
    // or allow a longer one 1/1000 times to avoid a
    // local minima
    // after 1000 runs with no improvement, stop
    // this seems to work, with no guarantee of course

    int shortest = total_distance((int *)distances, path, count);
    int no_change = 0;
    while (no_change < 1000) {
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

        if (dist2 <= dist1 || rand() % 1000 == 1) {
            int p1 = a + 1;
            int p2 = b;
            while (p1 < p2) {
                int tmp = path[p1];
                path[p1] = path[p2];
                path[p2] = tmp;
                p1++;
                p2--;
            }

            int distance = total_distance((int *)distances, path, count);

            if (distance < shortest) {
                shortest = distance;
                printf("%d\n", distance);
                no_change = 0;
            } else {
                no_change++;
            }
        }
    }

    return 0;
}
