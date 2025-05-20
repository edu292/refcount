#include "unity.h"
#include "object.h"

// Setup
void setUp(void) {}
void tearDown(void) {}

void test_new_integer(void) {
    object_t *obj = new_integer(42);
    TEST_ASSERT_NOT_NULL(obj);
    TEST_ASSERT_EQUAL(INTEGER, obj->kind);
    TEST_ASSERT_EQUAL(42, obj->data.v_int);
    TEST_ASSERT_EQUAL(1, obj->refcount);
    refcount_dec(obj);
}

void test_new_float(void) {
    object_t *obj = new_float(3.14f);
    TEST_ASSERT_NOT_NULL(obj);
    TEST_ASSERT_EQUAL(FLOAT, obj->kind);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.14, obj->data.v_float);
    TEST_ASSERT_EQUAL(1, obj->refcount);
    refcount_dec(obj);
}

void test_new_string(void) {
    object_t *obj = new_string("hello");
    TEST_ASSERT_NOT_NULL(obj);
    TEST_ASSERT_EQUAL(STRING, obj->kind);
    TEST_ASSERT_EQUAL_STRING("hello", obj->data.v_string);
    refcount_dec(obj);
}

void test_add_integer_integer(void) {
    object_t *a = new_integer(10);
    object_t *b = new_integer(32);
    object_t *res = add(a, b);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL(INTEGER, res->kind);
    TEST_ASSERT_EQUAL(42, res->data.v_int);
    refcount_dec(res);
}

void test_add_float_integer(void) {
    object_t *a = new_float(2.5f);
    object_t *b = new_integer(1);
    object_t *res = add(a, b);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL(FLOAT, res->kind);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.5, res->data.v_float);
    refcount_dec(res);
}

void test_add_string_string(void) {
    object_t *a = new_string("foo");
    object_t *b = new_string("bar");
    object_t *res = add(a, b);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL(STRING, res->kind);
    TEST_ASSERT_EQUAL_STRING("foobar", res->data.v_string);
    refcount_dec(res);
}

void test_array_set_get(void) {
    object_t *arr = new_array(2);
    object_t *val1 = new_integer(1);
    object_t *val2 = new_integer(2);
    TEST_ASSERT_TRUE(array_set(arr, 0, val1));
    TEST_ASSERT_TRUE(array_set(arr, 1, val2));

    object_t *get1 = array_get(arr, 0);
    object_t *get2 = array_get(arr, 1);

    TEST_ASSERT_EQUAL(val1, get1);
    TEST_ASSERT_EQUAL(val2, get2);

    refcount_dec(val1);
    refcount_dec(val2);
    refcount_dec(arr);
}

void test_length_function(void) {
    object_t *int_obj = new_integer(1);
    object_t *flt_obj = new_float(1.0f);
    object_t *str_obj = new_string("abc");
    object_t *arr_obj = new_array(3);

    TEST_ASSERT_EQUAL(1, length(int_obj));
    TEST_ASSERT_EQUAL(1, length(flt_obj));
    TEST_ASSERT_EQUAL(3, length(str_obj));
    TEST_ASSERT_EQUAL(3, length(arr_obj));

    refcount_dec(int_obj);
    refcount_dec(flt_obj);
    refcount_dec(str_obj);
    refcount_dec(arr_obj);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_integer);
    RUN_TEST(test_new_float);
    RUN_TEST(test_new_string);
    RUN_TEST(test_add_integer_integer);
    RUN_TEST(test_add_float_integer);
    RUN_TEST(test_add_string_string);
    RUN_TEST(test_array_set_get);
    RUN_TEST(test_length_function);
    return UNITY_END();
}
