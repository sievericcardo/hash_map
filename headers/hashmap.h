#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>

/* Custom boolean type */
typedef enum {FALSE, TRUE} boolean;

void exception(char* message) {
    int errnum = errno;
    fprintf(stderr, "%s: %s\n", message, strerror( errnum ));
    exit(EXIT_FAILURE);
}

void malloc_exception() {
    exception("Error while allocating memory\n");
}

typedef struct _Node {
    void* key;
    float value;
    struct _Node *next;
} Node;

typedef struct _HashMap {
    size_t size;
    size_t capacity;
    Node** buckets;
} HashMap;
