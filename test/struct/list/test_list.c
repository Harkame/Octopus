#include "./test_list.h"

int g_array_random_int[] = RANDOM_ELEMENTS_INT;

int test_list_push_first()
{
	LIST* t_list = NULL;

	for(int t_index = 0; t_index < NUMBER_ELEMENTS; t_index++)
	{
		if(list_push_first(&t_list, (void*) (intptr_t) g_array_random_int[t_index]) == -1)
			return -1;

		if(t_list->a_value != (void*) (intptr_t) g_array_random_int[t_index])
			return -1;

		if(list_size(t_list) != t_index + 1)
			return -1;
	}

	if(list_size(t_list) != NUMBER_ELEMENTS)
		return -1;

	list_delete(&t_list);

	if(list_size(t_list) != 0)
		return -1;

	return 0;
}

int test_list_push_last()
{
	LIST* t_list = NULL;

	for(int t_index = 0; t_index < NUMBER_ELEMENTS; t_index++)
	{
		if(list_push_last(&t_list, (void*) (intptr_t) g_array_random_int[t_index]) == -1)
			return -1;

		if(list_get(t_list, t_index) != (void*) (intptr_t) g_array_random_int[t_index])
			return -1;

		if(list_size(t_list) != t_index + 1)
			return -1;
	}

	if(list_size(t_list) != NUMBER_ELEMENTS)
		return -1;

	list_delete(&t_list);

	if(list_size(t_list) != 0)
		return -1;

	return 0;
}

int test_list_pop_first()
{
	LIST* t_list = NULL;

	for(int t_index = 0; t_index < NUMBER_ELEMENTS; t_index++)
	{
		if(list_push_first(&t_list, (void*) (intptr_t) g_array_random_int[t_index]) == -1)
			return -1;

		if(t_list->a_value != (void*) (intptr_t) g_array_random_int[t_index])
			return -1;
	}

	for(int t_index = NUMBER_ELEMENTS - 1; t_index > -1; t_index--)
	{
		if(list_pop_first(&t_list) != (void*) (intptr_t) g_array_random_int[t_index])
			return -1;

		if(list_size(t_list) != t_index)
			return -1;
	}

	if(list_size(t_list) != 0)
		return -1;

	return 0;
}

int test_list_pop_last()
{
	LIST* t_list = NULL;

	for(int t_index = 0; t_index < NUMBER_ELEMENTS; t_index++)
	{
		if(list_push_first(&t_list, (void*) (intptr_t) g_array_random_int[t_index]) == -1)
			return -1;

		if(t_list->a_value != (void*) (intptr_t) g_array_random_int[t_index])
			return -1;
	}

	for(int t_index = NUMBER_ELEMENTS - 1; t_index > -1; t_index--)
	{
		list_pop_last(&t_list);

			/*
		if(list_size(t_list) != t_index)
			return -1;
			*/

	}

	if(list_size(t_list) != 0)
		return -1;

	return 0;
}

int main()
{
	if (test_list_push_first() == -1)
	{
		fprintf(stderr, "ERROR : test_list_push_first\n");
		return EXIT_FAILURE;
	}

	if (test_list_push_last() == -1)
	{
		fprintf(stderr, "ERROR : test_list_push_first\n");
		return EXIT_FAILURE;
	}


	if (test_list_pop_first() == -1)
	{
		fprintf(stderr, "ERROR : test_list_pop_first\n");
		return EXIT_FAILURE;
	}

	if (test_list_pop_last() == -1)
	{
		fprintf(stderr, "ERROR : test_list_pop_first\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
