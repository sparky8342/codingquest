// sha256 code from: https://github.com/BareRose/lonesha256
#define LONESHA256_STATIC
#include "../utils/lonesha256.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int find_split(char *buffer, int amount) {
    int pipes = 0;
    int l = strlen(buffer);
    for (int i = 0; i < l; i++) {
        if (buffer[i] == '|') {
            pipes++;
            if (pipes == amount) {
                return i;
            }
        }
    }
    return 0;
}

bool hashes_match(unsigned char *hash, char *buffer, int divider) {
    for (int i = 0; i < 32; i++) {
        char hash_no[3];
        sprintf(hash_no, "%02x", hash[i]);
        char buffer_hash[3];
        sprintf(buffer_hash, "%c%c", buffer[divider + 1 + i * 2],
                buffer[(divider + 1 + i * 2) + 1]);
        if (hash_no[0] != buffer_hash[0] || hash_no[1] != buffer_hash[1]) {
            printf("bad hash\n");
            return false;
        }
    }
    return true;
}

char *generate_new_string(char *buffer, unsigned char *hash, int mine) {
    int divider = find_split(buffer, 1);

    int digits = 1;
    int cpy = mine;
    while (cpy > 9) {
        cpy /= 10;
        digits++;
    }

    char mine_str[digits];
    int pos = digits - 1;
    mine_str[pos] = '0';
    cpy = mine;
    while (cpy > 0) {
        mine_str[pos] = '0' + cpy % 10;
        cpy /= 10;
        pos--;
    }

    int len = divider + 1 + digits + 1 + 64 + 1;

    char *str = malloc(len * sizeof(char));

    for (int i = 0; i < divider; i++) {
        str[i] = buffer[i];
    }
    int strpos = divider;
    str[strpos] = '|';
    strpos++;
    for (int i = 0; i < digits; i++) {
        str[strpos] = mine_str[i];
        strpos++;
    }
    str[strpos] = '|';
    strpos++;

    for (int i = 0; i < 32; i++) {
        char hash_no[3];
        sprintf(hash_no, "%02x", hash[i]);
        str[strpos] = hash_no[0];
        str[strpos + 1] = hash_no[1];
        strpos += 2;
    }
    str[strpos] = '\0';

    return str;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/5.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    // find bad hash
    char buffer[200];
    unsigned char hash[32];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("%s", buffer);

        int divider = find_split(buffer, 3);

        if (lonesha256(hash, buffer, divider)) {
            printf("ERROR\n");
        }

        int hashpos = 0;
        if (!hashes_match(hash, buffer, divider)) {
            divider = find_split(buffer, 2);
            char hex[3];
            for (int i = divider + 1; i < divider + 1 + 64; i += 2) {
                hex[0] = buffer[i];
                hex[1] = buffer[i + 1];
                hex[2] = '\0';
                int number = (int)strtol(hex, NULL, 16);
                hash[hashpos] = number;
                hashpos++;
            }
            break;
        }
    }

    // recalculate rest of the hashes
    while (1) {
        int mine = 0;

        char *new_str;

        while (1) {

            new_str = generate_new_string(buffer, hash, mine);

            unsigned char new_hash[32];
            if (lonesha256(new_hash, new_str, strlen(new_str))) {
                printf("ERROR\n");
            }

            if (new_hash[0] == 0 && new_hash[1] == 0 && new_hash[2] == 0) {
                printf("%s ", new_str);
                for (int i = 0; i < 32; i++) {
                    printf("%02x", new_hash[i]);
                }
                printf("\n");

                memcpy(hash, new_hash, 32);
                break;
            }

            free(new_str);
            mine++;
        }

        if (fgets(buffer, sizeof(buffer), fptr) == NULL) {
            break;
        }
    }

    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
