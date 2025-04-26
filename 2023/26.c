#include <stdio.h>
#include <stdlib.h>

struct Node {
    long val;
    struct Node *left;
    struct Node *right;
} Node;

struct Entry {
    struct Node *node;
    struct Entry *next;
} Entry;

int widths[100];

void add_node(struct Node *node, struct Node *new_node) {
    if (new_node->val < node->val) {
        if (node->left != NULL) {
            add_node(node->left, new_node);
        } else {
            node->left = new_node;
        }
    } else {
        if (node->right != NULL) {
            add_node(node->right, new_node);
        } else {
            node->right = new_node;
        }
    }
}

int dfs(struct Node *node, int depth, int *max_depth) {
    widths[depth]++;
    if (node->left == NULL && node->right == NULL) {
        if (depth > *max_depth) {
            *max_depth = depth;
        }
    } else {
        if (node->left != NULL) {
            dfs(node->left, depth + 1, max_depth);
        }
        if (node->right != NULL) {
            dfs(node->right, depth + 1, max_depth);
        }
    }
}

int main() {
    FILE *fptr;
    fptr = fopen("inputs/26.txt", "r");
    if (fptr == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    char str[100];
    fscanf(fptr, "%s", &str);

    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->val = strtol(str, NULL, 16);
    head->left = NULL;
    head->right = NULL;

    while (fscanf(fptr, "%s", &str) == 1) {
        struct Node *node = (struct Node *)malloc(sizeof(struct Node));
        node->val = strtol(str, NULL, 16);
        node->left = NULL;
        node->right = NULL;
        add_node(head, node);
    }

    int max_depth;
    for (int i = 0; i < 100; i++) {
        widths[i] = 0;
    }
    dfs(head, 1, &max_depth);

    int max_width = 0;
    for (int i = 0; i < 100; i++) {
        if (widths[i] > max_width) {
            max_width = widths[i];
        }
    }

    printf("%d\n", max_width * max_depth);

    return 0;
}
