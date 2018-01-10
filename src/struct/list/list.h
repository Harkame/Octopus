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

void list_delete(LIST** p_list_to_delete);

int list_push_first(LIST** p_list, void* p_value_to_add);

int list_push_last(LIST** p_list, void* p_value_to_add);

void* list_pop_first(LIST** p_list);

void* list_pop_last(LIST** p_list);

void list_remove_element(LIST* p_list, int p_index);

void* list_get(LIST* p_list, int p_index);

void* list_get_auxliary(LIST* p_list, int p_index, int p_count);

void list_to_array(LIST* p_list, void** p_buffer, int p_index, int p_list_size);

int list_size(LIST* p_list);

void list_print(LIST* p_list_to_print);

#endif
