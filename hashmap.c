#include "headers/hashmap.h"

void exception(char* message) {
    int errnum = errno;
    fprintf(stderr, "%s: %s\n", message, strerror( errnum ));
    exit(EXIT_FAILURE);
}

void malloc_exception() {
    exception("Error while allocating memory\n");
}

void head_insertion(MapNode** list, int hash_position, void* key, float value) {
    MapNode* new_node = (MapNode*)  malloc(2*sizeof(MapNode));

    if(!new_node)
        malloc_exception();

    new_node->key = key;
    new_node->value = value;
    
    if(list[hash_position]) {
        new_node->next = list[hash_position];
        list[hash_position] = new_node;
    } else {
        new_node->next = NULL;
        list[hash_position] = new_node;
    }

    printf("Inserting element in list\n");

    assert(list); // It MUST exist by now
}

HashMap* HashMap_create(size_t capacity){
    HashMap *t = (HashMap*)malloc(sizeof(HashMap));

    if(!t)
        malloc_exception();

    t->size = 0;
    t->capacity = capacity;
    t->buckets = (MapNode**) malloc(sizeof(MapNode*) * t->capacity);

    if(!t->buckets)
        malloc_exception();

    printf("Hashmap created\n");

    return t;
}

int hashing_function(HashMap* t, void* key, long (*fptr)(void*)) {

    printf("Is it dieing now?\n");

    long hashing_factor = (*fptr)(key);

    printf("What the hell do I get? %ld\n", hashing_factor);

    int hash = (int) (hashing_factor % t->capacity);

    printf("This is the last hope with %d\n", hash);

    return hash;
}

void HashMap_insert(HashMap* t, void* key, float value, long (*fptr)(void*)){
    t->size+=1;

    printf("->->->->->\n");

    int hashing_position = hashing_function (t, key, fptr);

    printf("I got a good number from function %d\n", hashing_position);
    printf("buckets ptr: %p\n", t->buckets);

    printf("Create the buckets for the node\n");

    printf("I've created simple structures for the insertion\n");

    head_insertion(t->buckets, hashing_position, key, value);

    printf("I inserted the element properly\n");
}

float HashMap_lookup(HashMap* t, void* key, long(*fptr)(void*), boolean(*fptr2)(void*, void*)){

    printf("-------------------------------------------------------------\nI'm finding the element %s\n", (char*)key);

    int hashing_position = hashing_function(t, key, fptr);

    printf("Ready for lookup!\n");
    printf("Found position: %d\n", hashing_position);

    MapNode *list = t->buckets[hashing_position];
    
    if(!list)
        printf("What happened?\n");

    while(list){
        printf("Parsing the list\n");
        if((*fptr2)(list->key, key)){
            printf("I've found a value\n");
            return list->value;
        }
        list = list->next;
    }
    
    return -1;
}

int main() {
    HashMap *t = HashMap_create(150);

    FILE* fin = fopen("lorem_ipsum.txt", "r");

    char* buffer = (char*)malloc(100*sizeof(char));

    while(fscanf(fin, "%s", buffer) != EOF) {
        printf("Got %s\n", buffer);
        HashMap_insert(t, buffer, rand()%30, string_hashing);
    }

    printf("%f\n", HashMap_lookup(t, "dui.", string_hashing, equals_strings));

    return 0;
}

/* Hashing functions */

// Function to hash the map according to strings
long string_hashing(void* data) {
    char* str = (char*) malloc(strlen(data) * sizeof(char));
    strcpy(str, data);

    long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/*
 * The following functions serve us to create new elements that we need when
 * we insert the into the list.
 * We create a function for almost every type */
int* new_int(int value) {
    int* element = (int*) malloc (sizeof(int));
    *element = value;

    return element;
}

int64_t* new_big_int(int64_t value) {
    int64_t* element = (int64_t*) malloc (sizeof(int));
    *element = value;

    return element;
}

float* new_float(float value) {
    float* element = (float*) malloc (sizeof(float));

    if(!element)
        malloc_exception();

    *element = value;

    return element;
}

long* new_long(long value) {
    long* element = (long*) malloc (sizeof(long));

    if(!element)
        malloc_exception();

    *element = value;

    return element;
}

double* new_double(double value) {
    double* element = (double*) malloc (sizeof(double));

    if(!element)
        malloc_exception();

    *element = value;

    return element;
}

char* new_char(char value) {
    char* element = (char*) malloc(sizeof(char));

    if(!element)
        malloc_exception();

    *element = value;

    return element;
}

char* new_string(char* string) {
    char* new_string = (char*) malloc (strlen(string) * sizeof(char));

    if(!new_string)
        malloc_exception();

    strcpy(new_string, string);

    return new_string;
}

/*
 * Functions used to compare elements in the arraylist */
int compare_int (void* element1, void* element2) {
    if(*(int*)element1 < *(int*)element2)
        return -1;
    else if (*(int*)element1 == *(int*)element2)
        return 0;
    
    return 1;
}

int compare_big_int (void* element1, void* element2) {
    if(*(int64_t*)element1 < *(int64_t*)element2)
        return -1;
    else if (*(int64_t*)element1 == *(int64_t*)element2)
        return 0;
    
    return 1;
}

int compare_float (void* element1, void* element2) {
    if(*(float*)element1 < *(float*)element2)
        return -1;
    else if (*(float*)element1 == *(float*)element2)
        return 0;
    
    return 1;
}

int compare_long (void* element1, void* element2) {
    if(*(long*)element1 < *(long*)element2)
        return -1;
    else if (*(long*)element1 == *(long*)element2)
        return 0;
    
    return 1;
}

int compare_double (void* element1, void* element2) {
    if(*(double*)element1 < *(double*)element2)
        return -1;
    else if (*(double*)element1 == *(double*)element2)
        return 0;
    
    return 1;
}

int compare_chars (void* element1, void* element2) {
    if(strcmp((char*) element1, (char*) element2) < 0)
        return -1;
    else if (strcmp((char*) element1, (char*) element2) == 0)
        return 0;
    
    return 1;
}

int compare_strings (void* element1, void* element2) {
    if(strcmp((char*) element1, (char*) element2) < 0)
        return -1;
    else if (strcmp((char*) element1, (char*) element2) == 0)
        return 0;
    
    return 1;
}

/* We could just call the compare and look that the result is 0
 * I implement separate functions just for make them more intuitive. */
boolean equals_int (void* element1, void* element2) {
    return (*(int*)element1 == *(int*)element2);
}

boolean equals_big_int (void* element1, void* element2) {
    return (*(int64_t*)element1 == *(int64_t*)element2);
}

boolean equals_float (void* element1, void* element2) {
    return (*(float*)element1 == *(float*)element2);
}

boolean equals_long (void* element1, void* element2) {
    return (*(long*)element1 == *(long*)element2);
}

boolean equals_double (void* element1, void* element2) {
    return (*(double*)element1 == *(double*)element2);
}

boolean equals_char (void* element1, void* element2) {
    return (*(char*) element1 == *(char*)element2);
}

boolean equals_strings (void* element1, void* element2) {
    return (strcmp((char*) element1, (char*) element2) == 0);
}
