#include "../utils/cvector.h"
#include <stdio.h>

typedef struct {
    int sequence_no;
    char *message;
} Chunk;

int compare(const void *a, const void *b) {
    Chunk *a_chunk = *(Chunk **)a;
    Chunk *b_chunk = *(Chunk **)b;
    return a_chunk->sequence_no - b_chunk->sequence_no;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/21.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    Chunk **chunks = NULL;

    char line[200];
    while (fscanf(fptr, "%s", line) == 1) {
        if (!(line[0] == '5' && line[1] == '5' && line[2] == '5' &&
              line[3] == '5')) {
            continue;
        }

        char hex[3] = {line[12], line[13], '\0'};
        int sequence_no = (int)strtol(hex, NULL, 16);

        hex[0] = line[14];
        hex[1] = line[15];
        int checksum = (int)strtol(hex, NULL, 16);

        char message[25];
        message[24] = '\0';
        int message_i = 0;
        int total = 0;
        for (int i = 16; i < 88; i += 2) {
            hex[0] = line[i];
            hex[1] = line[i + 1];
            int n = (int)strtol(hex, NULL, 16);
            total += n;
            message[message_i] = n;
            message_i++;
        }

        if (total % 256 != checksum) {
            continue;
        }

        Chunk *chunk = (Chunk *)malloc(sizeof(Chunk));
        chunk->message = malloc(25 * sizeof(char));
        chunk->sequence_no = sequence_no;
        memcpy(chunk->message, message, 25);
        cvector_push_back(chunks, chunk);
    }

    fclose(fptr);

    qsort(chunks, cvector_size(chunks), sizeof(Chunk *), compare);

    for (int i = 0; i < cvector_size(chunks); i++) {
        printf("%s", chunks[i]->message);
    }
    printf("\n");

    cvector_free(chunks);

    return 0;
}
