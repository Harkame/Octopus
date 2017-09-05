#ifndef LIST_INT_H
#define LIST_INT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LIST_INT
{
     int a_value;

     struct LIST_INT* a_next;
} LIST_INT;

struct LIST_INT* create_list_int();

void add_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add);

void add_first_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add);

int remove_first_element_list_int(struct LIST_INT* p_list_int);

int size_list_int(struct LIST_INT* p_list_int);

void print_list_int(struct LIST_INT*);

#endif
