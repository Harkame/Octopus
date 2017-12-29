#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <stdint.h>

typedef struct LIST
{
     void* a_value;

     struct LIST* a_next;
} LIST;

int list_add_first_element(LIST* p_list, void* p_value_to_add);

int list_add_last_element(LIST* p_list, void* p_value_to_add);

void* list_remove_first_element(LIST* p_list);

int list_size(LIST* p_list);

void list_print(LIST* p_list_to_print);

#endif
