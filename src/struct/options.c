#include "./options.h"

void create_options(struct OPTIONS* p_options_to_create)
{
     p_options_to_create->a_options_count = 0;

     p_options_to_create->a_options_values = malloc(sizeof(char*) * 20);

     for(int t_index = 0; t_index < 20; t_index++)
          p_options_to_create->a_options_values[t_index] = malloc(sizeof(char) * 50);
}

void delete_options(struct OPTIONS* p_options_to_delete)
{
     for(int t_index = 0; t_index < 20; t_index++)
          free(p_options_to_delete->a_options_values[t_index]);
}
