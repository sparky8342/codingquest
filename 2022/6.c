#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ADD = 1,
    MOD,
    DIV,
    MOV,
    JMP,
    JIF,
    CEQ,
    CGE,
    OUT,
    END,
} OPCODE;

typedef struct {
    OPCODE opcode;
    char arg1[3];
    char arg2[3];
} INSTRUCTION;

INSTRUCTION *parse_line(char buffer[]) {
    INSTRUCTION *instruction = (INSTRUCTION *)malloc(sizeof(INSTRUCTION));

    char op[] = {buffer[0], buffer[1], buffer[2], '\0'};
    if (strcmp(op, "ADD") == 0) {
        instruction->opcode = ADD;
    } else if (strcmp(op, "MOD") == 0) {
        instruction->opcode = MOD;
    } else if (strcmp(op, "DIV") == 0) {
        instruction->opcode = DIV;
    } else if (strcmp(op, "MOV") == 0) {
        instruction->opcode = MOV;
    } else if (strcmp(op, "JMP") == 0) {
        instruction->opcode = JMP;
    } else if (strcmp(op, "JIF") == 0) {
        instruction->opcode = JIF;
    } else if (strcmp(op, "CEQ") == 0) {
        instruction->opcode = CEQ;
    } else if (strcmp(op, "CGE") == 0) {
        instruction->opcode = CGE;
    } else if (strcmp(op, "OUT") == 0) {
        instruction->opcode = OUT;
    } else if (strcmp(op, "END") == 0) {
        instruction->opcode = END;
    }

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

        if (ins->opcode == ADD) {
            registers[ins->arg1[0] - 'A'] += parse_arg(ins->arg2, registers);
        } else if (ins->opcode == MOD) {
            registers[ins->arg1[0] - 'A'] %= parse_arg(ins->arg2, registers);
        } else if (ins->opcode == DIV) {
            registers[ins->arg1[0] - 'A'] /= parse_arg(ins->arg2, registers);
        } else if (ins->opcode == MOV) {
            registers[ins->arg1[0] - 'A'] = parse_arg(ins->arg2, registers);
        } else if (ins->opcode == JMP) {
            pos += parse_arg(ins->arg1, registers);
            continue;
        } else if (ins->opcode == JIF) {
            if (compare) {
                pos += parse_arg(ins->arg1, registers);
                continue;
            }
        } else if (ins->opcode == CEQ) {
            compare = parse_arg(ins->arg1, registers) ==
                      parse_arg(ins->arg2, registers);
        } else if (ins->opcode == CGE) {
            compare = parse_arg(ins->arg1, registers) >=
                      parse_arg(ins->arg2, registers);
        } else if (ins->opcode == OUT) {
            printf("%lld\n", parse_arg(ins->arg1, registers));
        } else if (ins->opcode == END) {
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

    int size = 1;

    INSTRUCTION **instructions = malloc(size * sizeof(INSTRUCTION *));

    if (instructions == NULL) {
        printf("Cannot malloc\n");
        return 1;
    }

    int index = 0;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        INSTRUCTION *instruction = parse_line(buffer);
        instructions[index] = instruction;

        index++;
        if (index == size) {
            size *= 2;
            instructions = realloc(instructions, size * sizeof(INSTRUCTION *));
            if (instructions == NULL) {
                printf("Cannot realloc\n");
                return 1;
            }
        }
    }

    run(instructions);

    free(instructions);

    return 0;
}
