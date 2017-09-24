#include "./options.h"

void create_options(struct OPTIONS* p_options_to_create)
{
     p_options_to_create->a_options_values = malloc(sizeof(char) * 20);
}

void delete_options(struct OPTIONS* p_options_to_delete)
{
     for(int t_index = 0; t_index < p_options_to_delete->a_options_count; t_index++)
          free(p_options_to_delete->a_options_values[t_index]);

     free(p_options_to_delete->a_options_values);
}
