#include "./list.h"

void list_initialize(LIST* p_list_to_initialize, void* p_first_value)
{
     p_list_to_initialize->a_value = p_first_value;
     p_list_to_initialize->a_next = NULL;
}

void list_delete(LIST* p_list_to_delete)
{
     if(p_list_to_delete == NULL)
          return;
     else
     {
          list_delete(p_list_to_delete->a_next);

          free(p_list_to_delete->a_next);
     }
}

int list_add_element(LIST* p_list, void* p_value_to_add, int p_index)
{
     return list_add_element_auxiliary(p_list, p_value_to_add, p_index, 0);
}

int list_add_element_auxiliary(LIST* p_list, void* p_value_to_add, int p_index, int p_count)
{
     if(p_list->a_next == NULL)
     {
          if(p_count == p_index)
          {
               LIST* t_list = malloc(sizeof(LIST));

               if(t_list == NULL)
                    return EXIT_SUCCESS;

               t_list->a_value = p_value_to_add;

               p_list->a_next = t_list;
          }
          else
               return EXIT_FAILURE;
     }
     else if(p_count == p_index)
     {
          LIST* t_list = malloc(sizeof(LIST));

          if(t_list == NULL)
               return EXIT_FAILURE;

          t_list->a_value = p_list->a_value;

          p_list->a_value = p_value_to_add;

          t_list->a_next = p_list->a_next;

          p_list->a_next = t_list;
     }
     else
          list_add_element_auxiliary(p_list->a_next, p_value_to_add, p_index, p_count + 1);

     return EXIT_SUCCESS;
}

int list_add_first_element(LIST* p_list, void* p_value_to_add)
{
     LIST* t_list = malloc(sizeof(LIST));

     if(t_list == NULL)
          return EXIT_FAILURE;

     t_list->a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list->a_next = p_list->a_next;

     p_list->a_next = t_list;

     return EXIT_SUCCESS;
}

int list_add_last_element(LIST* p_list, void* p_value_to_add)
{
     if(p_list->a_next == NULL)
     {

          fprintf(stdout, "VALUE : %d\n", p_value_to_add);

          LIST* t_list = malloc(sizeof(LIST));

          if(t_list == NULL)
               return EXIT_FAILURE;

          t_list->a_value = p_value_to_add;
          t_list->a_next = NULL;

          p_list->a_next = t_list;
     }
     else
          list_add_last_element(p_list->a_next, p_value_to_add);

     return EXIT_SUCCESS;
}

int list_remove_element(LIST* p_list, int p_index)
{
     return list_remove_element_auxiliary(p_list, p_index, 0);
}

int list_remove_element_auxiliary(LIST* p_list, int p_index, int p_count)
{
     if(p_list->a_next == NULL)
     {
          if(p_index == p_count)
               free(p_list);
          else
               return EXIT_FAILURE;
     }
     else if(p_index == p_count)
     {
          p_list->a_value = p_list->a_next->a_value;

          p_list->a_next = p_list->a_next->a_next;

          free(p_list->a_next);
     }
     else
          list_remove_element_auxiliary(p_list->a_next, p_index, p_count + 1);

     return EXIT_SUCCESS;
}

void* list_get_element(LIST* p_list, int p_index)
{
     return list_get_element_auxiliary(p_list, p_index, 0);
}

void* list_get_element_auxiliary(LIST* p_list, int p_index, int p_count)
{
     if((p_list->a_next == NULL) || (p_count == p_index))
          return p_list->a_value;
     else
          return list_get_element_auxiliary(p_list->a_next, p_index, p_count + 1);
}

int list_contains_element(LIST* p_list, void* p_value)
{
     if(p_list->a_next == NULL)
          if(p_list->a_value == p_value)
               return EXIT_SUCCESS;
          else
               return EXIT_FAILURE;
     else if(p_list->a_value == p_value)
          return EXIT_SUCCESS;
     else
          return list_contains_element(p_list->a_next, p_value);
}

int list_size(LIST* p_list)
{
     if(p_list->a_next == NULL)
          return 1;
     else
          return 1 + list_size(p_list->a_next);
}

void list_to_array(LIST* p_list_string, char** p_array, int p_index, int p_size_array)
{
     if(p_list_string->a_next == NULL)
          return;
     else
     {
          p_array[p_index] = p_list_string->a_value;
          //strcpy(p_array[p_index], p_list_string->a_value);
          list_to_array(p_list_string->a_next, p_array, p_index + 1, p_size_array);
     }
}
