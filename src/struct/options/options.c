#include "./options.h"

int create_options(OPTIONS* p_options_to_create)
{
	p_options_to_create->a_options_count = 0;

	p_options_to_create->a_options_values = malloc(sizeof(char*) * 20);

	if (p_options_to_create->a_options_values == NULL)
		return -1;

	for(int t_index = 0; t_index < 20; t_index++)
		if ((p_options_to_create->a_options_values[t_index] = malloc(sizeof(char) * 50)) == NULL)
		{
			for(int t_index_2 = 0; t_index_2 < t_index; t_index_2++)
				free(p_options_to_create->a_options_values[t_index_2]);

			return -1;
		}

	return 0;
}

void delete_options(OPTIONS* p_options_to_delete)
{
	for(int t_index = 0; t_index < 20; t_index++)
		free(p_options_to_delete->a_options_values[t_index]);
}
