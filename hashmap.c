#include "headers/hashmap.h"

int* new_int(int value) {
    int* element = (int*) malloc (sizeof(int));
    *element = value;

    return element;
}

HashMap* create_hash_map(size_t capacity){
    HashMap *t = (HashMap*)malloc(sizeof(HashMap));

    t->size = 0;
    t->capacity = capacity;
    t->buckets = (Node**) malloc(sizeof(Node*) * t->capacity);

    printf("Hashmap created\n");

    return t;
}

long hash(void* data) {
    char* str = (char*) malloc(strlen(data) * sizeof(char));
    strcpy(str, data);

    long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int last_hope_hash(HashMap* t, void* key, long (*fptr)(void*)) {

    printf("Is it dieing now?\n");

    long hashing_factor = (*fptr)(key);

    printf("What the hell do I get? %ld\n", hashing_factor);

    //int hash = (int) (((hashing_factor + LONG_MAX) / sizeof(Node)) % t->capacity);
    int hash = (int) (hashing_factor % t->capacity);

    printf("This is the last hope with %d\n", hash);

    return hash;
}

void head_insertion(Node** list, int hash_position, void* key, float value) {
    Node* new_node = (Node*)  malloc(2*sizeof(Node));

    if(!new_node) {
        malloc_exception();
    }

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

void insert(HashMap *t, void* key, float value, long (*fptr)(void*)){
    t->size+=1;

    printf("->->->->->\n");

    int hash = last_hope_hash (t, key, fptr);

    printf("I got a good number from function %d\n", hash);
    printf("buckets ptr: %p\n", t->buckets);

    printf("Create the buckets for the node\n");

    printf("I've created simple structures for the insertion\n");

    head_insertion(t->buckets, hash, key, value);

    printf("I inserted the element properly\n");
}

boolean equal_string(void* element1, void* element2) {
    if(strcmp((char*)element1, (char*)element2) == 0)
        return TRUE;
    
    return FALSE;
}

float lookup(HashMap *t, void* key, long(*fptr)(void*), boolean(*fptr2)(void*, void*)){

    printf("-------------------------------------------------------------\nI'm finding the element %s\n", (char*)key);

    int position = last_hope_hash(t, key, fptr);

    printf("Ready for lookup!\n");
    printf("Found position: %d\n", position);

    Node *list = t->buckets[position];
    
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

int get_size(char** text) {
    int size=0;

    while(text[size])
        size++;

    return size;
}

int main(){
    HashMap *t = create_hash_map(150);

    FILE* fin = fopen("lorem_ipsum.txt", "r");

    char* buffer = (char*)malloc(100*sizeof(char));

    while(fscanf(fin, "%s", buffer) != EOF) {
        printf("Got %s\n", buffer);
        insert(t, buffer, rand()%30, hash);
    }

    //printf("%f\n", lookup(t, "ligula", hash, equal_string));
    printf("%f\n", lookup(t, "dui.", hash, equal_string));

    return 0;
}
