#include <stdlib.h>
#include "object.h"
#include <string.h>

void refcount_dec(object_t *obj) {
    if (obj == NULL) return;
    if (obj->refcount == 1) refcount_free(obj);
    else obj->refcount--;
}

void refcount_free(object_t *obj) {
    switch (obj->kind) {
        case STRING:
            free(obj->data.v_string);
            break;
        case ARRAY:
            for (int i = 0; i < obj->data.v_array.size; i++) {
                refcount_dec(obj->data.v_array.elements[i]);
            }
            free(obj->data.v_array.elements);
            break;
    }
    free(obj);
}

void refcount_inc(object_t *obj) {
    if (obj == NULL) return;
    obj->refcount++;
}

object_t *new_object() {
    object_t *new_object = calloc(1, sizeof(object_t));
    if (new_object == NULL) return NULL;
    new_object->refcount = 1;
    return new_object;
}

object_t *add(object_t *a, object_t *b) {
    object_t *result;
    switch (a->kind) {
        case INTEGER:
            switch (b->kind) {
                case INTEGER:
                    result = new_integer(a->data.v_int + b->data.v_int);
                    break;
                case FLOAT:
                    result = new_float(a->data.v_int+b->data.v_float);
                    break;
                default: return NULL;
            }
            break;
        case FLOAT:
            switch (b->kind) {
                case INTEGER:
                    result = new_float(a->data.v_float+b->data.v_int);
                    break;
                case FLOAT:
                    result = new_float(a->data.v_float+b->data.v_float);
                    break;
                default: return NULL;
            }
            break;
        case STRING:
            if (b->kind != STRING) return NULL;
            const size_t size = strlen(a->data.v_string)+strlen(b->data.v_string)+1;
            char *temp = calloc(size, sizeof(char*));
            strcat(temp, a->data.v_string);
            strcat(temp, b->data.v_string);
            result = new_string(temp);
            free(temp);
            break;
        case ARRAY:
            if (b->kind != ARRAY) return NULL;
            result = new_array(a->data.v_array.size + b->data.v_array.size);
            for (int i = 0; i < a->data.v_array.size; i++) {
                array_set(result, i, array_get(a, i));
            }
            for (int i = 0; i < b->data.v_array.size; i++) {
                array_set(result, i+a->data.v_array.size, array_get(b, i));
            }
            break;
        default:
            return NULL;
    }
    refcount_dec(a);
    refcount_dec(b);
    return result;
}

int length(object_t *obj) {
    if (obj == NULL) {
        return -1;
    }
    switch (obj->kind) {
        case INTEGER:
        case FLOAT: return 1;
        case VECTOR3: return 3;
        case STRING: return strlen(obj->data.v_string);
        case ARRAY: return obj->data.v_array.size;
        default: return -1;
    }
}

object_t *array_get(const object_t *array, const size_t index) {
    if (array == NULL) {
        return NULL;
    }
    if (array->kind != ARRAY) {
        return NULL;
    }
    if (index > array->data.v_array.size) {
        return NULL;
    }
    return array->data.v_array.elements[index];
}

bool array_set(object_t *array, size_t index, object_t *value) {
    if (array == NULL || value == NULL) {
        return NULL;
    }
    if (array->kind != ARRAY){
        return false;
    }
    if (array->data.v_array.size < index) {
        return false;
    }
    if (array->data.v_array.elements[index] != NULL) {
        refcount_dec(array->data.v_array.elements[index]);
    }
    refcount_inc(value);
    array->data.v_array.elements[index] = value;
    return true;
}

object_t *new_array(size_t size) {
    object_t *obj = new_object();
    if (obj == NULL) {
        return NULL;
    }

    object_t **elements = calloc(size, sizeof(object_t *));
    if (elements == NULL) {
        free(obj);
        return NULL;
    }

    obj->kind = ARRAY;
    obj->data.v_array = (array_t){.size = size, .elements = elements};

    return obj;
}

object_t *new_integer(int value) {
    object_t *obj = new_object();
    if (obj == NULL) {
        return NULL;
    }

    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}

object_t *new_float(float value) {
    object_t *obj = new_object();
    if (obj == NULL) {
        return NULL;
    }

    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}

object_t *new_string(char *value) {
    object_t *obj = new_object();
    if (obj == NULL) {
        return NULL;
    }

    int len = strlen(value);
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        free(obj);
        return NULL;
    }

    strcpy(dst, value);

    obj->kind = STRING;
    obj->data.v_string = dst;
    return obj;
}