/*
 *  Header file for the HashMap
 * 
 *  File:  hashmap.h
 *  Author: Riccardo Sieve
 *
 *  Created on 19 November 2018, 9:40
 */

#ifndef _HASHMAP_H_INCLUDED_
#define _HASHMAP_H_INCLUDED_

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

typedef struct _MapNode {
    void* key;
    float value;
    struct _MapNode *next;
} MapNode;

typedef struct _HashMap {
    size_t size;
    size_t capacity;
    MapNode** buckets;
} HashMap;

/* Hashing Functions */
long string_hashing(void* );

/* Extra functions */
// New Elements
int* new_int(int);
int64_t* new_big_int(int64_t);
float* new_float(float);
long* new_long(long);
double* new_double(double);
char* new_char(char);
char* new_string(char*);

// Compare elements
int compare_int(void* , void*);
int compare_big_int(void* , void*);
int compare_float(void* , void*);
int compare_long(void* , void*);
int compare_double(void* , void*);
int compare_chars(void* , void*);
int compare_strings(void* , void*);

// Check that two elements are equals
boolean equals_int (void* , void*);
boolean equals_big_int (void* , void*);
boolean equals_float (void* , void*);
boolean equals_long (void* , void*);
boolean equals_double (void* , void*);
boolean equals_char (void* , void*);
boolean equals_strings (void* , void*);

/* HashMap functions */
HashMap* HashMap_create(size_t );
void HashMap_insert(HashMap* , void* , float , long (*fptr)(void*));
float HashMap_lookup(HashMap* , void* , long(*fptr)(void*), boolean(*fptr2)(void*, void*));

#endif
