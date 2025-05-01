#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    fptr = fopen("inputs/29.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    int wifi = 0;
    int internal = 0;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        char hex[5] = {buffer[4], buffer[5], buffer[6], buffer[7], '\0'};
        int len = (int)strtol(hex, NULL, 16);
        hex[0] = buffer[24];
        hex[1] = buffer[25];
        hex[2] = '\0';
        int ip1 = (int)strtol(hex, NULL, 16);
        hex[0] = buffer[26];
        hex[1] = buffer[27];
        int ip2 = (int)strtol(hex, NULL, 16);
        hex[0] = buffer[32];
        hex[1] = buffer[33];
        int ip3 = (int)strtol(hex, NULL, 16);
        hex[0] = buffer[34];
        hex[1] = buffer[35];
        int ip4 = (int)strtol(hex, NULL, 16);

        if ((ip1 == 10 && ip2 == 0) || (ip3 == 10 && ip4 == 0)) {
            wifi += len;
        } else if ((ip1 == 192 && ip2 == 168) || (ip3 == 192 && ip4 == 168)) {
            internal += len;
        }
    }

    fclose(fptr);

    printf("%d/%d\n", internal, wifi);

    return 0;
}
