#include "./list.h"

int list_create(LIST* p_list_to_create)
{
     p_list_to_create = malloc(sizeof(LIST));

     if(p_list_to_create == NULL)
          return ERROR;

     p_list_to_create->a_value = NULL;
     p_list_to_create->a_next  = NULL;

     return OK;
}

int list_add_element(LIST* p_list, void* p_value_to_add, int p_index)
{
     return list_add_element_auxiliary(p_list, p_value_to_add, p_index, 0);
}

int list_add_element_auxiliary(LIST* p_list, void* p_value_to_add, int p_index, int p_count)
{
     if(p_count == p_index)
     {
          p_list->a_value = p_value_to_add;

          LIST t_list;

          if(list_create(&t_list) == ERROR)
               return ERROR;

          p_list->a_next = &t_list;
     }
     else if(p_list->a_next == NULL && p_index != p_count)
          return ERROR;
     else
          list_add_last_element(p_list->a_next, p_value_to_add);

     return OK;
}

int list_add_first_element(LIST* p_list, void* p_value_to_add)
{
     LIST t_list;

     if(list_create(&t_list) == ERROR)
          return ERROR;

     t_list.a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list.a_next = p_list->a_next;

     p_list->a_next = &t_list;

     return OK;
}

int list_add_last_element(LIST* p_list, void* p_value_to_add)
{
     if(p_list->a_next == NULL)
     {
          p_list->a_value = p_value_to_add;

          LIST t_list;

          if(list_create(&t_list) == ERROR)
               return ERROR;

          p_list->a_next = &t_list;
     }
     else
          list_add_last_element(p_list->a_next, p_value_to_add);

     return OK;
}

void list_remove_element(LIST* p_list, int p_index)
{
     list_remove_element_auxiliary(p_list, p_index, 0);
}

void list_remove_element_auxiliary(LIST* p_list, int p_index, int p_count)
{
     if(p_index == p_count)
     {
          if(p_list->a_next == NULL)
               return;

          p_list->a_value = p_list->a_next->a_value;

          LIST* t_list = p_list->a_next->a_next;

          free(p_list->a_next);

          p_list->a_next = t_list;
     }
     else
          list_remove_element_auxiliary(p_list->a_next, p_index, p_count + 1);
}

void* list_get_element(LIST* p_list, int p_index)
{
     return list_get_element_auxiliary(p_list, p_index, 0);
}

void* list_get_element_auxiliary(LIST* p_list, int p_index, int p_count)
{
     if(p_index == p_count)
          return p_list->a_value;
     else
          return list_get_element_auxiliary(p_list->a_next, p_index, p_count + 1);
}

int list_size(LIST* p_list)
{
     if(p_list->a_next == NULL)
          return 0;
     else
          return 1 + list_size(p_list->a_next);
}

void list_to_array(LIST* p_list_string, char** p_array, int p_index, int p_size_array)
{
     if(p_list_string->a_next == NULL)
     {
          return;
     }
     else
     {
          p_array[p_index] = p_list_string->a_value;
          //strcpy(p_array[p_index], p_list_string->a_value);
          list_to_array(p_list_string->a_next, p_array, p_index + 1, p_size_array);
     }
}

int main()
{
     return 0;
}
