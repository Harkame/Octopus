#ifndef LIST_STRING_H
#define LIST_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LIST_STRING
{
     char* a_value;

     struct LIST_STRING* a_next;
} LIST_STRING;

struct LIST_STRING* create_list_string();

void add_element_list_string(struct LIST_STRING* p_LIST_STRING, char* p_value_to_add);

void add_first_element_list_string(struct LIST_STRING* p_LIST_STRING, char* p_value_to_add);

char* remove_first_element_list_string(struct LIST_STRING* p_LIST_STRING);

int size_list_string(struct LIST_STRING* p_LIST_STRING);

void print_list_string(struct LIST_STRING*);

void list_string_to_array(struct LIST_STRING* p_list_string, char** p_array, int p_index, int p_size_array);

#endif
