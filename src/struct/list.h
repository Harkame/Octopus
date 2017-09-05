#ifndef LIST_INT_H
#define LIST_INT_H

#include <stdio.h>
#include <stdlib.h>

struct LIST_INT
{
     int a_value;

     struct LIST_INT* a_next;
};

struct LIST_INT* create_LIST_INT();

void add_element(struct LIST_INT* p_LIST_INT, int p_value_to_add);

void add_first_element(struct LIST_INT* p_LIST_INT, int p_value_to_add);

int remove_first_element(struct LIST_INT* p_LIST_INT);

int size(struct LIST_INT* p_LIST_INT);

void print(struct LIST_INT*);

#endif
