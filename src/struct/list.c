#include "list.h"

struct LIST_INT* create_list()
{
     struct LIST_INT* r_list = malloc(sizeof(struct list));

     r_list->a_value = -1;
     r_list->a_next  = NULL;

     return r_list;
}

void add_element(struct LIST_INT* p_list, int p_value_to_add)
{
     if(p_list->a_next == NULL)
     {
          p_list->a_value = p_value_to_add;

          struct LIST_INT* t_list = create_list();

          p_list->a_next = t_list;
     }
     else
          add_element(p_list->a_next, p_value_to_add);
}

void add_first_element(struct LIST_INT* p_list, int p_value_to_add)
{
     struct LIST_INT* t_list = create_list();

     t_list->a_value = p_list->a_value;

     p_list->a_value = p_value_to_add;

     t_list->a_next = p_list->a_next;

     p_list->a_next = t_list;
}

int remove_first_element(struct LIST_INT* p_list)
{
     if(p_list->a_next == NULL)
          return -1;

     int r_value = p_list->a_value;

     p_list->a_value = p_list->a_next->a_value;

     struct LIST_INT* t_list = p_list->a_next->a_next;

     free(p_list->a_next);

     p_list->a_next = t_list;

     return r_value;
}

int size(struct LIST_INT* p_list)
{
     if(p_list->a_next == NULL)
          return 0;
     else
          return 1 + size(p_list->a_next);
}

void print(struct LIST_INT* p_list)
{
     if(p_list->a_next == NULL)
          fprintf(stdout, "|\n");
     else
     {
          fprintf(stdout, "[%d] -> ", p_list->a_value);
          print(p_list->a_next);
     }
}

int main(int argc, char** argv)
{
     struct LIST_INT* t_list = create_list();

     fprintf(stdout, "%d\n", size(t_list));

     add_first_element(t_list, 42);

     fprintf(stdout, "%d\n", size(t_list));
}
