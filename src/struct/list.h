#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LIST
{
     void* a_value;

     struct LIST* a_next;
} LIST;

struct LIST* create_list();

void add_element_list(struct LIST* p_LIST, void* p_value_to_add);

void add_first_element_list(struct LIST* p_LIST, void* p_value_to_add);

void remove_first_element_list(struct LIST* p_LIST);

void* get_element_list(struct LIST* p_list, int p_index);

void* get_element_list_aux(struct LIST* p_list, int p_index, int p_count);

int size_list(struct LIST* p_LIST);

void print_list(struct LIST*);

void list_to_array(struct LIST* p_list, char** p_array, int p_index, int p_size_array);

#endif
