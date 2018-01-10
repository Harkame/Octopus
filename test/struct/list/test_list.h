#ifndef TEST_LIST_H
#define TEST_LIST_H
#include <stdint.h>

#include "../../../src/struct/list/list.h"

#define RANDOM_ELEMENTS_INT {42, 3, 52, 48, 12, 1, 0, -89, -4, 12}
#define NUMBER_ELEMENTS 10

extern int g_array_values_int[];

int test_list_initialize();

int test_list_delete();

int test_list_add_element();

int test_list_add_first_element();

int test_list_add_last_element();

int test_list_remove_element();

int test_list_get_element();

int test_list_contais_element();

int test_list_size();

int main(void);

#endif
