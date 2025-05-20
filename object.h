#pragma once
#include <stdbool.h>

typedef enum ObjectKind {
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY
} object_kind_t;

typedef struct Object object_t;

typedef struct Array {
    size_t size;
    object_t **elements;
} array_t;

typedef union ObjectData {
    int v_int;
    float v_float;
    char *v_string;
    array_t v_array;
} object_data_t;

typedef struct Object {
    object_kind_t kind;
    object_data_t data;
    int refcount;
} object_t;



object_t *new_integer(int value);
object_t *new_float(float value);
object_t *new_string(char *value);
object_t *new_array(size_t size);

bool array_set(object_t *array, size_t index, object_t *value);
object_t *array_get(const object_t *array, size_t index);

int length(object_t *obj);
object_t *add(object_t *a, object_t *b);

void refcount_inc(object_t *obj);
void refcount_dec(object_t *obj);
void refcount_free(object_t *obj);