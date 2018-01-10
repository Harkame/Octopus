#include "./list.h"

void list_delete(LIST** p_list_to_delete)
{
	LIST* t_list;

	while(*p_list_to_delete != NULL)
	{
		t_list = (*p_list_to_delete)->a_next;

		free(*p_list_to_delete);

		*p_list_to_delete = t_list;
	}
}

int list_push_first(LIST** p_list, void* p_value_to_add)
{
	LIST* t_list = malloc(sizeof(LIST));

	if (t_list == NULL)
		return -1;

	t_list->a_value = p_value_to_add;
	t_list->a_next = *p_list;

	*p_list = t_list;

	return 0;
}

int list_push_last(LIST** p_list, void* p_value_to_add)
{
	if(*p_list == NULL)
	{
		(*p_list) = malloc(sizeof(LIST));

		if ((*p_list) == NULL)
			return -1;

		(*p_list)->a_value = p_value_to_add;
		(*p_list)->a_next = NULL;

		return 0;
	}
	else if((*p_list)->a_next == NULL)
	{
		LIST* t_list = malloc(sizeof(LIST));

		if (t_list == NULL)
			return -1;

		t_list->a_value = p_value_to_add;
		t_list->a_next = NULL;

		(*p_list)->a_next = t_list;

		return 0;
	}
	else
		return list_push_last(&(*p_list)->a_next, p_value_to_add);
}

void* list_pop_first(LIST** p_list)
{
	if(*p_list == NULL)
		return NULL;

	LIST* t_list = (*p_list)->a_next;

	void* r_value = (*p_list)->a_value;

	free(*p_list);

	*p_list = t_list;

	return r_value;
}

void* list_pop_last(LIST** p_list)
{
	if((*p_list)->a_next == NULL)
	{
		if(*p_list == NULL)
			return NULL;

		LIST* t_list = (*p_list)->a_next;

		void* r_value = (*p_list)->a_value;

		free(*p_list);

		*p_list = t_list;

		return r_value;
	}
	else
		return list_pop_last(&(*p_list)->a_next);
}

void list_to_array(LIST* p_list, void** p_buffer, int p_index, int p_list_size)
{
	if(p_index == p_list_size)
		return;
	else
		list_to_array(p_list->a_next, p_buffer, p_index + 1, p_list_size);

	p_buffer[p_index] = p_list->a_value;
}

void* list_get(LIST* p_list, int p_index)
{
	return list_get_auxliary(p_list, p_index, 0);
}

void* list_get_auxliary(LIST* p_list, int p_index, int p_count)
{
	if(p_list == NULL)
		return NULL;

	if(p_index == p_count)
		return p_list->a_value;
	else
		return list_get_auxliary(p_list->a_next, p_index, p_count + 1);
}

int list_size(LIST* p_list)
{
	if (p_list == NULL)
		return 0;
	else
		return 1 + list_size(p_list->a_next);
}

void list_print(LIST* p_list_to_print)
{
	if(p_list_to_print == NULL)
		return;

	if (p_list_to_print->a_next == NULL)
	{
		int t_value = (int) (intptr_t) p_list_to_print->a_value;

		fprintf(stdout, "[%d]\n", t_value);
	}
	else
	{
		int t_value = (int) (intptr_t) p_list_to_print->a_value;

		fprintf(stdout, "[%d] -> ", t_value);

		list_print(p_list_to_print->a_next);
	}
}
