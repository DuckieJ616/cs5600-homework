#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = 4;
    v->data = malloc(v->capacity * sizeof(int));
    if (!v->data) {
        perror("malloc");
        exit(1);
    }
}

void vector_push(Vector *v, int value) {
    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity * 2;
        int *temp = realloc(v->data, new_capacity * sizeof(int));
        if (!temp) {
            perror("realloc");
            free(v->data);
            exit(1);
        }
        v->data = temp;
        v->capacity = new_capacity;
    }
    v->data[v->size++] = value;
}

void vector_free(Vector *v) {
    free(v->data);
}

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void list_push(Node **head, int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        perror("malloc");
        exit(1);
    }
    node->value = value;
    node->next = *head;
    *head = node;
}

void list_free(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

double elapsed_seconds(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec)
        + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(void) {
    int sizes[] = {10000, 100000, 1000000};

    for (int t = 0; t < 3; t++) {
        int n = sizes[t];
        struct timespec start, end;

        Vector v;
        vector_init(&v);

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < n; i++) {
            vector_push(&v, i);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double vector_time = elapsed_seconds(start, end);

        vector_free(&v);

        Node *head = NULL;

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < n; i++) {
            list_push(&head, i);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double list_time = elapsed_seconds(start, end);

        list_free(head);

        printf("N = %d\n", n);
        printf("Vector:      %.6f seconds\n", vector_time);
        printf("Linked List: %.6f seconds\n\n", list_time);
    }

    return 0;
}
