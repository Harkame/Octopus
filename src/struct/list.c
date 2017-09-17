#include "list.h"

struct LIST* create_list()
{
     struct LIST* r_list = malloc(sizeof(struct LIST));

     r_list->a_value = NULL;
     r_list->a_next  = NULL;

     return r_list;
}

void add_first_element_list(struct LIST* p_list, void* p_value_to_add)
{
     struct LIST* t_list = create_list();

     t_list->a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list->a_next = p_list->a_next;

     p_list->a_next = t_list;
}

void add_last_element_list(struct LIST* p_list, void* p_value_to_add)
{
     if(p_list->a_next == NULL)
     {
          p_list->a_value = p_value_to_add;

          struct LIST* t_list = create_list();

          p_list->a_next = t_list;
     }
     else
          add_last_element_list(p_list->a_next, p_value_to_add);
}

void remove_element_list(struct LIST* p_list, int p_index)
{
     return remove_element_list_aux(p_list, p_index, 0);
}

void remove_element_list_aux(struct LIST* p_list, int p_index, int p_count)
{
     if(p_index == p_count)
     {
          if(p_list->a_next == NULL)
               return;

          p_list->a_value = p_list->a_next->a_value;

          struct LIST* t_list = p_list->a_next->a_next;

          free(p_list->a_next);

          p_list->a_next = t_list;
     }
     else
          return remove_element_list_aux(p_list->a_next, p_index, p_count + 1);
}

void* get_element_list(struct LIST* p_list, int p_index)
{
     return get_element_list_aux(p_list, p_index, 0);
}

void* get_element_list_aux(struct LIST* p_list, int p_index, int p_count)
{
     if(p_index == p_count)
          return p_list->a_value;
     else
          return get_element_list_aux(p_list->a_next, p_index, p_count + 1);
}

int size_list(struct LIST* p_list)
{
     if(p_list->a_next == NULL)
          return 0;
     else
          return 1 + size_list(p_list->a_next);
}

void print_list(struct LIST* p_list)
{
     if(p_list->a_next == NULL)
          fprintf(stdout, "|\n");
     else
     {
          fprintf(stdout, "[%d] -> ", p_list->a_value);
          print_list(p_list->a_next);
     }
}
