#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <error.h>

#ifndef OK
     #define OK       0
#endif

#define ERROR -1

typedef struct LIST
{
     void* a_value;

     struct LIST* a_next;
} LIST;

int list_create(LIST* p_list_to_create);

int list_add_element(LIST* p_LIST, void* p_value_to_add, int p_index);

int list_add_element_auxiliary(LIST* p_LIST, void* p_value_to_add, int p_index, int p_count);

int list_add_first_element(LIST* p_LIST, void* p_value_to_add);

int list_add_last_element(LIST* p_LIST, void* p_value_to_add);

void list_remove_element(LIST* p_LIST, int p_index);

void list_remove_element_auxiliary(LIST* p_LIST, int p_intex, int p_count);

void* list_get_element(LIST* p_list, int p_index);

void* list_get_element_auxiliary(LIST* p_list, int p_index, int p_count);

int list_size(LIST* p_LIST);

void list_to_array(LIST* p_list, char** p_array, int p_index, int p_size_array);

#endif
