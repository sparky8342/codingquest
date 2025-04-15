#include <stdbool.h>
#include <stdio.h>

void reset_board(int board[7][7]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      board[i][j] = 0;
    }
  }
}

bool check_win(int board[7][7], int player) {
  for (int row = 0; row < 7; row++) {
    for (int col = 0; col < 7; col++) {
      if (board[row][col] != player) {
        continue;
      }
      if (row < 4 && board[row + 1][col] == player &&
          board[row + 2][col] == player && board[row + 3][col] == player) {
        return true;
      }
      if (col < 4 && board[row][col + 1] == player &&
          board[row][col + 2] == player && board[row][col + 3] == player) {
        return true;
      }
      if (col < 4 && row < 4 && board[row + 1][col + 1] == player &&
          board[row + 2][col + 2] == player &&
          board[row + 3][col + 3] == player) {
        return true;
      }
      if (row < 4 && col > 2 && board[row + 1][col - 1] == player &&
          board[row + 2][col - 2] == player &&
          board[row + 3][col - 3] == player) {
        return true;
      }
    }
  }
  return false;
}

void add_piece(int board[7][7], int player, int column) {
  for (int row = 6; row >= 0; row--) {
    if (board[row][column] == 0) {
      board[row][column] = player;
      return;
    }
  }
}

void print_board(int board[7][7]) {
  for (int r = 0; r < 7; r++) {
    for (int c = 0; c < 7; c++) {
      printf("%d", board[r][c]);
    }
    printf("\n");
  }
  printf("\n");
}

int main() {
  int board[7][7];

  FILE *fptr;
  fptr = fopen("inputs/4.txt", "r");
  if (fptr == NULL) {
    printf("Cannot open file\n");
    return 1;
  }

  int wins[4] = {0, 0, 0};
  char buffer[100];
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    reset_board(board);
    int player = 1;
    for (int i = 0; i < sizeof(buffer); i++) {
      if (buffer[i] >= '1' && buffer[i] <= '7') {
        add_piece(board, player, buffer[i] - '1');
        if (check_win(board, player)) {
          wins[player - 1]++;
          break;
        }
        player++;
        if (player == 4) {
          player = 1;
        }
      } else {
        break;
      }
    }
  }

  printf("%d\n", wins[0] * wins[1] * wins[2]);

  return 0;
}
