#include "list_string.h"

void create_list_string(struct LIST_STRING* p_list_string_to_create)
{
     p_list_string_to_create->a_value = malloc(sizeof(char) * 255);

     p_list_string_to_create->a_next  = NULL;
}

void add_element_list_string(struct LIST_STRING* p_list, char* p_value_to_add)
{
     if(p_list->a_next == NULL)
     {
          strcpy(p_list->a_value, p_value_to_add);

          struct LIST_STRING* t_list = malloc(sizeof(struct LIST_STRING));

          create_list_string(t_list);

          p_list->a_next = t_list;
     }
     else
          add_element_list_string(p_list->a_next, p_value_to_add);
}

void add_first_element_list_string(struct LIST_STRING* p_list, char* p_value_to_add)
{
     struct LIST_STRING t_list;

     create_list_string(&t_list);

     t_list.a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list.a_next = p_list->a_next;

     p_list->a_next = &t_list;
}

void remove_first_element_list_string(struct LIST_STRING* p_list)
{
     if(p_list->a_next == NULL)
          return;

     p_list->a_value = p_list->a_next->a_value;

     struct LIST_STRING* t_list = p_list->a_next->a_next;

     //free(p_list->a_next);

     p_list->a_next = t_list;
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
