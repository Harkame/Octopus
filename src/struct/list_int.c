#include "list_int.h"

void create_list_int(struct LIST_INT* p_list_int_to_create)
{
     p_list_int_to_create = malloc(sizeof(struct LIST_INT));

     p_list_int_to_create->a_value = -1;
     p_list_int_to_create->a_next  = NULL;
}

void add_first_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add)
{
     struct LIST_INT t_list;

     create_list_int(&t_list);

     t_list.a_value = p_list_int->a_value;

     p_list_int->a_value = p_value_to_add;

     t_list.a_next = p_list_int->a_next;

     p_list_int->a_next = &t_list;
}

void add_last_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add)
{
     if(p_list_int->a_next == NULL)
     {
          p_list_int->a_value = p_value_to_add;

          struct LIST_INT t_list;

          create_list_int(&t_list);

          p_list_int->a_next = &t_list;
     }
     else
          add_last_element_list_int(p_list_int->a_next, p_value_to_add);
}

void remove_element_list_int(struct LIST_INT* p_list_int, int p_index)
{
     remove_element_list_int_aux(p_list_int, p_index, 0);
}

void remove_element_list_int_aux(struct LIST_INT* p_list_int, int p_index, int p_count)
{
     if(p_index == p_count)
     {
          if(p_list_int->a_next == NULL)
               return;

          p_list_int->a_value = p_list_int->a_next->a_value;

          struct LIST_INT* t_list = p_list_int->a_next->a_next;

          free(p_list_int->a_next);

          p_list_int->a_next = t_list;
     }
     else
          remove_element_list_int_aux(p_list_int->a_next, p_index, p_count + 1);
}

signed int get_element_list_int(struct LIST_INT* p_list, int p_index)
{
     return get_element_list_int_aux(p_list, p_index, 0);
}

signed int get_element_list_int_aux(struct LIST_INT* p_list, int p_index, int p_count)
{
     if(p_index == p_count)
          return p_list->a_value;
     else
          return get_element_list_int_aux(p_list->a_next, p_index, p_count + 1);
}

int size_list_int(struct LIST_INT* p_list_int)
{
     if(p_list_int->a_next == NULL)
          return 0;
     else
          return 1 + size_list_int(p_list_int->a_next);
}

void print_list_int(struct LIST_INT* p_list_int)
{
     if(p_list_int->a_next == NULL)
          fprintf(stdout, "|\n");
     else
     {
          fprintf(stdout, "[%d] -> ", p_list_int->a_value);
          print_list_int(p_list_int->a_next);
     }
}
