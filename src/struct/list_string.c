#include "list_string.h"

struct LIST_STRING* create_list_string()
{
     struct LIST_STRING* r_list = malloc(sizeof(struct LIST_STRING));

     r_list->a_value = malloc(255 * sizeof(char));

     r_list->a_value[0] = '\0';

     r_list->a_next  = NULL;

     return r_list;
}

void add_element_list_string(struct LIST_STRING* p_list, char* p_value_to_add)
{
     if(p_list->a_next == NULL)
     {
          strcpy(p_list->a_value, p_value_to_add);

          struct LIST_STRING* t_list = create_list_string();

          p_list->a_next = t_list;
     }
     else
          add_element_list_string(p_list->a_next, p_value_to_add);
}

void add_first_element_list_string(struct LIST_STRING* p_list, char* p_value_to_add)
{
     struct LIST_STRING* t_list = create_list_string();

     t_list->a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list->a_next = p_list->a_next;

     p_list->a_next = t_list;
}

char* remove_first_element_list_string(struct LIST_STRING* p_list)
{
     if(p_list->a_next == NULL)
          return '\0';

     char* r_value = malloc(255 * sizeof(char));
     strcpy(r_value, p_list->a_value);

     p_list->a_value = p_list->a_next->a_value;

     struct LIST_STRING* t_list = p_list->a_next->a_next;

     //fprintf(stdout, "VALUE : %s\n", p_list->a_value);
     //free(&p_list->a_value);

     free(p_list->a_next);

     p_list->a_next = t_list;

     return r_value;
}

int size_list_string(struct LIST_STRING* p_list)
{
     if(p_list->a_next == NULL)
          return 0;
     else
          return 1 + size_list_string(p_list->a_next);
}

void print_list_string(struct LIST_STRING* p_list)
{
     if(p_list->a_next == NULL)
          fprintf(stdout, "|\n");
     else
     {
          fprintf(stdout, "[%s] ->\n", p_list->a_value);

          print_list_string(p_list->a_next);
     }
}

void list_string_to_array(struct LIST_STRING* p_list_string, char** p_array, int p_index, int p_size_array)
{
     if(p_list_string->a_next == NULL)
     {
          return;
     }
     else
     {
          p_array[p_index] = p_list_string->a_value;
          //strcpy(p_array[p_index], p_list_string->a_value);
          list_string_to_array(p_list_string->a_next, p_array, p_index + 1, p_size_array);
     }
}
