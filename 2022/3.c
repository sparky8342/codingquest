#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fptr;
  fptr = fopen("inputs/3.txt", "r");
  if (fptr == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  int x = 0;
  int y = 0;
  int z = 0;
  int distance = 0;

  int nx, ny, nz;
  while (fscanf(fptr, "%d %d %d", &nx, &ny, &nz) == 3) {
    distance +=
        sqrt(pow(abs(x - nx), 2) + pow(abs(y - ny), 2) + pow(abs(z - nz), 2));
    x = nx;
    y = ny;
    z = nz;
  }

  printf("%d\n", distance);

  return 0;
}
