#include "../utils/cvector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char opcode[4];
    char arg1[3];
    char arg2[3];
} INSTRUCTION;

INSTRUCTION *parse_line(char buffer[]) {
    INSTRUCTION *instruction = (INSTRUCTION *)malloc(sizeof(INSTRUCTION));

    instruction->opcode[0] = buffer[0];
    instruction->opcode[1] = buffer[1];
    instruction->opcode[2] = buffer[2];
    instruction->opcode[3] = '\0';

    int pos = 0;
    int arg = 1;
    for (int i = 4; i < strlen(buffer); i++) {
        if (buffer[i] == '\n') {
            break;
        } else if (buffer[i] == ' ') {
            arg = 2;
            pos = 0;
            continue;
        }
        if (arg == 1) {
            instruction->arg1[pos] = buffer[i];
        } else if (arg == 2) {
            instruction->arg2[pos] = buffer[i];
        }
        pos++;
    }

    return instruction;
}

long long parse_num(char arg[]) {
    bool negative = false;
    int start = 0;
    if (arg[start] == '-') {
        negative = true;
        start++;
    }
    long long n = 0;
    for (int i = start; i < strlen(arg); i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            break;
        }
        n = n * 10 + arg[i] - '0';
    }
    if (negative) {
        n *= -1;
    }
    return n;
}

long long parse_arg(char arg[], long long registers[12]) {
    if (arg[0] >= 'A' && arg[0] <= 'L') {
        return registers[arg[0] - 'A'];
    } else {
        return parse_num(arg);
    }
}

void run(INSTRUCTION **instructions) {
    long long registers[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int pos = 0;
    bool compare;

    while (1) {
        INSTRUCTION *ins = instructions[pos];

        if (strcmp(ins->opcode, "ADD") == 0) {
            registers[ins->arg1[0] - 'A'] += parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "MOD") == 0) {
            registers[ins->arg1[0] - 'A'] %= parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "DIV") == 0) {
            registers[ins->arg1[0] - 'A'] /= parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "MOV") == 0) {
            registers[ins->arg1[0] - 'A'] = parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "JMP") == 0) {
            pos += parse_arg(ins->arg1, registers);
            continue;
        } else if (strcmp(ins->opcode, "JIF") == 0) {
            if (compare) {
                pos += parse_arg(ins->arg1, registers);
                continue;
            }
        } else if (strcmp(ins->opcode, "CEQ") == 0) {
            compare = parse_arg(ins->arg1, registers) ==
                      parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "CGE") == 0) {
            compare = parse_arg(ins->arg1, registers) >=
                      parse_arg(ins->arg2, registers);
        } else if (strcmp(ins->opcode, "OUT") == 0) {
            printf("%lld\n", parse_arg(ins->arg1, registers));
        } else if (strcmp(ins->opcode, "END") == 0) {
            break;
        }

        pos++;
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/6.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    INSTRUCTION **instructions = NULL;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        INSTRUCTION *instruction = parse_line(buffer);
        cvector_push_back(instructions, instruction);
    }

    run(instructions);

    cvector_free(instructions);

    return 0;
}
