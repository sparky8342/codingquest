typedef struct vector {
    int *items;
    int capacity;
    int len;
} vector;

void vector_init(vector *v) {
    v->capacity = 1;
    v->len = 0;
    v->items = malloc(sizeof(int *) * v->capacity);
}

int vector_len(vector *v) { return v->len; }

static void vector_resize(vector *v, int capacity) {
    int *items = realloc(v->items, sizeof(int *) * capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vector_push(vector *v, int item) {
    if (v->capacity == v->len)
        vector_resize(v, v->capacity * 2);
    v->items[v->len++] = item;
}

int vector_get(vector *v, int index) {
    if (index >= 0 && index < v->len)
        return v->items[index];
    return 0;
}

void vector_free(vector *v) { free(v->items); }
