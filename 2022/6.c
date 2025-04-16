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

    int source_a_val;
    char source_a_reg;
    bool source_a_use_val;

    int source_b_val;
    char source_b_reg;
    bool source_b_use_val;

    char target;
} INSTRUCTION;

int parse_num(char buffer[], int start) {
    bool negative = false;
    if (buffer[start] == '-') {
        negative = true;
        start++;
    }
    int n = 0;
    for (int i = start; i < strlen(buffer); i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            break;
        }
        n = n * 10 + buffer[i] - '0';
    }
    if (negative) {
        n *= -1;
    }
    return n;
}

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

    if (instruction->opcode == ADD || instruction->opcode == MOD ||
        instruction->opcode == DIV || instruction->opcode == MOV) {

        instruction->target = buffer[4];

        char source = buffer[6];
        if (source >= 'A' && source <= 'L') {
            instruction->source_a_reg = source;
            instruction->source_a_use_val = false;
        } else {
            instruction->source_a_val = parse_num(buffer, 6);
            instruction->source_a_use_val = true;
        }
    } else if (instruction->opcode == JMP || instruction->opcode == JIF ||
               instruction->opcode == OUT) {

        char source = buffer[4];
        if (source >= 'A' && source <= 'L') {
            instruction->source_a_reg = source;
            instruction->source_a_use_val = false;
        } else {
            instruction->source_a_val = parse_num(buffer, 4);
            instruction->source_a_use_val = true;
        }
    } else if (instruction->opcode == CEQ || instruction->opcode == CGE) {
        char source = buffer[4];
        if (source >= 'A' && source <= 'L') {
            instruction->source_a_reg = source;
            instruction->source_a_use_val = false;
        } else {
            instruction->source_a_val = parse_num(buffer, 4);
            instruction->source_a_use_val = true;
        }

        int index;
        for (int i = 5; i < strlen(buffer); i++) {
            if (buffer[i] == ' ') {
                index = i + 1;
                break;
            }
        }

        source = buffer[index];
        if (source >= 'A' && source <= 'L') {
            instruction->source_b_reg = source;
            instruction->source_b_use_val = false;
        } else {
            instruction->source_b_val = parse_num(buffer, index);
            instruction->source_b_use_val = true;
        }
    }

    return instruction;
}

void run(INSTRUCTION **instructions) {
    long long registers[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int pos = 0;
    bool compare;

    while (1) {
        INSTRUCTION *ins = instructions[pos];

        long long source_a;
        if (ins->source_a_use_val) {
            source_a = (long long)ins->source_a_val;
        } else {
            source_a = registers[ins->source_a_reg - 'A'];
        }

        long long source_b;
        if (ins->opcode == CEQ || ins->opcode == CGE) {
            if (ins->source_b_use_val) {
                source_b = (long long)ins->source_b_val;
            } else {
                source_b = registers[ins->source_b_reg - 'A'];
            }
        }

        if (ins->opcode == ADD) {
            registers[ins->target - 'A'] += source_a;
        } else if (ins->opcode == MOD) {
            registers[ins->target - 'A'] %= source_a;
        } else if (ins->opcode == DIV) {
            registers[ins->target - 'A'] /= source_a;
        } else if (ins->opcode == MOV) {
            registers[ins->target - 'A'] = source_a;
        } else if (ins->opcode == JMP) {
            pos += source_a;
            continue;
        } else if (ins->opcode == JIF) {
            if (compare) {
                pos += source_a;
                continue;
            }
        } else if (ins->opcode == CEQ) {
            compare = source_a == source_b;
        } else if (ins->opcode == CGE) {
            compare = source_a >= source_b;
        } else if (ins->opcode == OUT) {
            printf("%lld\n", source_a);
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
