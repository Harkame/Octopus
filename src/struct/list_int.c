#include "list.h"

struct LIST_INT* create_list_int()
{
     struct LIST_INT* r_list = malloc(sizeof(struct LIST_INT));

     r_list->a_value = -1;
     r_list->a_next  = NULL;

     return r_list;
}

void add_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add)
{
     if(p_list_int->a_next == NULL)
     {
          p_list_int->a_value = p_value_to_add;

          struct LIST_INT* t_list = create_list_int();

          p_list_int->a_next = t_list;
     }
     else
          add_element_list_int(p_list_int->a_next, p_value_to_add);
}

void add_first_element_list_int(struct LIST_INT* p_list_int, int p_value_to_add)
{
     struct LIST_INT* t_list = create_list_int();

     t_list->a_value = p_list_int->a_value;

     p_list_int->a_value = p_value_to_add;

     t_list->a_next = p_list_int->a_next;

     p_list_int->a_next = t_list;
}

int remove_first_element_list_int(struct LIST_INT* p_list_int)
{
     if(p_list_int->a_next == NULL)
          return -1;

     int r_value = p_list_int->a_value;

     p_list_int->a_value = p_list_int->a_next->a_value;

     struct LIST_INT* t_list = p_list_int->a_next->a_next;

     free(p_list_int->a_next);

     p_list_int->a_next = t_list;

     return r_value;
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
