#include <stdbool.h>
#include <stdio.h>

int main() {
    char guesses[3][7] = {"keyless", "society", "phobias"};
    char results[3][7] = {"YYBBYYG", "YGYYYBB", "BBGBGBG"};

    // green - exact match
    char match[] = "       ";

    // black - can't be in word
    bool not_in[26];
    for (int i = 0; i < 26; i++) {
        not_in[i] = false;
    }

    // yellow - is in word
    bool is_in[26];
    for (int i = 0; i < 26; i++) {
        is_in[i] = false;
    }

    // NOTE: not recording where the yellow letters could be
    // but this wasn't necessary (for this input anyway)

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            if (results[i][j] == 'G') {
                match[j] = guesses[i][j];
            } else if (results[i][j] == 'B') {
                not_in[guesses[i][j] - 'a'] = true;
            } else if (results[i][j] == 'Y') {
                is_in[guesses[i][j] - 'a'] = true;
            }
        }
    }

    FILE *fptr;
    fptr = fopen("inputs/14.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char word[100];
    while (fscanf(fptr, "%s", word) == 1) {
        bool ok = true;
        for (int i = 0; i < 7; i++) {
            if (match[i] != ' ' && match[i] != word[i]) {
                ok = false;
                break;
            }
            if (not_in[word[i] - 'a'] == true) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            continue;
        }

        bool in_word[26];
        for (int i = 0; i < 26; i++) {
            in_word[i] = false;
        }
        for (int i = 0; i < 7; i++) {
            in_word[word[i] - 'a'] = true;
        }

        for (int i = 0; i < 26; i++) {
            if (is_in[i] && !in_word[i]) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            continue;
        }

        printf("%s\n", word);
    }

    return 0;
}
