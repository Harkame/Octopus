#include "./list.h"

int list_add_first_element(LIST* p_list, void* p_value_to_add)
{
	LIST* t_list = calloc(1, sizeof(LIST));

	if (t_list == NULL)
		return -1;

	t_list->a_value = p_list->a_value;
	t_list->a_next = p_list->a_next;

	p_list->a_value = p_value_to_add;
	p_list->a_next = t_list;

	return 0;
}

int list_add_last_element(LIST* p_list, void* p_value_to_add)
{
	if (p_list->a_next == NULL)
	{
		p_list->a_next = calloc(1, sizeof(LIST));

		if (p_list->a_next == NULL)
			return -1;

		p_list->a_value = p_value_to_add;

		return 0;
	}
	else
		return list_add_last_element(p_list->a_next, p_value_to_add);
}

void* list_remove_first_element(LIST* p_list)
{
	if (p_list->a_next != NULL)
	{
		p_list->a_value = p_list->a_next->a_value;

		LIST* t_list = p_list->a_next;

		p_list->a_next = p_list->a_next->a_next;

		void* r_value = t_list->a_value;

		free(t_list);

		return r_value;
	}
	else
		free(p_list);

	return (void*) -1;
}

int list_size(LIST* p_list)
{
	if (p_list->a_next == NULL)
		return 0;
	else
		return 1 + list_size(p_list->a_next);
}

void list_print(LIST* p_list_to_print)
{
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
