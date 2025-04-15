#include <stdbool.h>
#include <stdio.h>

int main() {
  bool winning_numbers[100];
  for (int i = 0; i < 100; i++) {
    winning_numbers[i] = false;
  }
  winning_numbers[12] = true;
  winning_numbers[48] = true;
  winning_numbers[30] = true;
  winning_numbers[95] = true;
  winning_numbers[15] = true;
  winning_numbers[55] = true;
  winning_numbers[97] = true;

  FILE *fptr;
  fptr = fopen("inputs/2.txt", "r");
  if (fptr == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  int winnings = 0;
  int draw[6];
  while (fscanf(fptr, "%d %d %d %d %d %d", &draw[0], &draw[1], &draw[2],
                &draw[3], &draw[4], &draw[5]) == 6) {
    int matching = 0;
    for (int i = 0; i < 6; i++) {
      if (winning_numbers[draw[i]] == true) {
        matching++;
      }
    }
    if (matching == 3) {
      winnings += 1;
    } else if (matching == 4) {
      winnings += 10;
    } else if (matching == 5) {
      winnings += 100;
    } else if (matching == 6) {
      winnings += 1000;
    }
  }

  printf("%d\n", winnings);

  return 0;
}
