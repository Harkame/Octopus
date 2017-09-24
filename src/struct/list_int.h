#ifndef LIST_INT_H
#define LIST_INT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LIST_INT
{
     int a_value;

     struct LIST_INT* a_next;
} LIST_INT;

void create_list_int(struct LIST_INT* p_list_int_to_create);

void add_last_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add);

void add_first_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add);

void remove_element_list_int(struct LIST_INT* p_list_int, int p_index);

void remove_element_list_int_aux(struct LIST_INT* p_list_int, int p_index, int p_count);

int get_element_list_int(struct LIST_INT* p_list, int p_index);

int get_element_list_int_aux(struct LIST_INT* p_list, int p_index, int p_count);

int size_list_int(struct LIST_INT* p_list_int);

void print_list_int(struct LIST_INT*);

#endif
