#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 20
// #define SIZE 8

struct Pos {
    int x;
    int y;
    struct Pos *next;
    struct Pos *prev;
} Pos;

int next_fruit(char fruit[], int index, int *x, int *y) {
    *x = fruit[index] - '0';
    while (fruit[++index] != ',') {
        *x = *x * 10 + fruit[index] - '0';
    }
    index++;
    *y = fruit[index] - '0';
    index++;
    while (fruit[index] != ' ' && fruit[index] != '\n') {
        *y = *y * 10 + fruit[index] - '0';
        index++;
    }
    index++;
    return index;
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/24.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    char fruit[2000];
    char moves[2000];
    fgets(fruit, sizeof(fruit), fptr);
    fgets(fruit, sizeof(fruit), fptr);
    fgets(moves, sizeof(moves), fptr);
    fgets(moves, sizeof(moves), fptr);
    fclose(fptr);

    int fruit_i = 0;
    int fruit_x;
    int fruit_y;
    fruit_i = next_fruit(fruit, fruit_i, &fruit_x, &fruit_y);

    int score = 0;

    struct Pos *dummy_head = (struct Pos *)malloc(sizeof(struct Pos));
    struct Pos *part = (struct Pos *)malloc(sizeof(struct Pos));
    struct Pos *dummy_tail = (struct Pos *)malloc(sizeof(struct Pos));
    dummy_head->next = part;
    part->prev = dummy_head;
    part->next = dummy_tail;
    dummy_tail->prev = part;

    part->x = 0;
    part->y = 0;

    for (int i = 0; i < sizeof(moves); i++) {
        struct Pos *part = dummy_head->next;

        int new_x = part->x;
        int new_y = part->y;
        if (moves[i] == 'U') {
            new_y--;
        } else if (moves[i] == 'D') {
            new_y++;
        } else if (moves[i] == 'L') {
            new_x--;
        } else if (moves[i] == 'R') {
            new_x++;
        }

        if (new_x < 0 || new_x == SIZE || new_y < 0 || new_y == SIZE) {
            break;
        }

        int turn_score = 1;

        struct Pos *new_part = (struct Pos *)malloc(sizeof(struct Pos));
        new_part->x = new_x;
        new_part->y = new_y;

        new_part->next = dummy_head->next;
        new_part->next->prev = new_part;
        dummy_head->next = new_part;
        new_part->prev = dummy_head;

        if (new_part->x == fruit_x && new_part->y == fruit_y) {
            turn_score += 100;
            fruit_i = next_fruit(fruit, fruit_i, &fruit_x, &fruit_y);
        } else {
            struct Pos *old = dummy_tail->prev;
            dummy_tail->prev = dummy_tail->prev->prev;
            dummy_tail->prev->next = dummy_tail;
            free(old);
        }

        // check for snake collision
        struct Pos *p = dummy_head->next->next;
        bool collided = false;
        while (p != dummy_tail) {
            if (p->x == new_part->x && p->y == new_part->y) {
                collided = true;
                break;
            }
            p = p->next;
        }
        if (collided) {
            break;
        }

        score += turn_score;
    }

    printf("%d\n", score);

    return 0;
}
