#include <stdio.h>

static char secret[] = "Roads? Where We're Going, We Don't Need Roads.";
static char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTU"
                           "VWXYZ0123456789.,;:?! '()";

int get_char_position(char ch) {
    for (int i = 0; i < sizeof(characters); i++) {
        if (characters[i] == ch) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/8.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char buffer[500];
    fgets(buffer, sizeof(buffer), fptr);

    int secret_pos[sizeof(secret) - 1];
    for (int i = 0; i < sizeof(secret); i++) {
        secret_pos[i] = get_char_position(secret[i]);
    }
    int secret_p = 0;

    int len = sizeof(characters) - 1;

    for (int i = 0; i < sizeof(buffer); i++) {
        if (buffer[i] == '\n') {
            break;
        }

        int n = get_char_position(buffer[i]);
        int s = secret_pos[secret_p];

        if (n == -1 || s == -1) {
            printf("%c", buffer[i]);
        } else {
            int new_char_pos = n - s;
            if (new_char_pos > len) {
                new_char_pos -= len;
            } else if (new_char_pos < 1) {
                new_char_pos += len;
            }
            printf("%c", characters[new_char_pos - 1]);
        }
        secret_p = (secret_p + 1) % (sizeof(secret) - 1);
    }

    printf("\n");
    return 0;
}
