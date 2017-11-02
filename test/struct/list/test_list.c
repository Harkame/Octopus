#include "./test_list.h"

int g_array_values_int[] = RANDOM_VALUES_INT;

int test_list_initialize()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     if(t_list.a_value != (void*) (intptr_t) g_array_values_int[0])
          return EXIT_FAILURE;

     if(t_list.a_next != NULL)
          return EXIT_FAILURE;

     list_delete(&t_list);

     return EXIT_SUCCESS;
}

int test_list_delete()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     list_delete(&t_list);

     /*
     TODO
     */

     return EXIT_SUCCESS;
}

int test_list_add_element()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     for(int t_index = 1; t_index < COUNT; t_index++)
          if(list_add_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index], t_index - 1) == EXIT_FAILURE)
               return EXIT_FAILURE;

     if(list_size(&t_list) == COUNT)
          return EXIT_FAILURE;

     for(int t_index = 0; t_index < COUNT; t_index++)
          if(list_contains_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index]) == EXIT_FAILURE)
               return EXIT_FAILURE;

     list_delete(&t_list);

     return EXIT_SUCCESS;
}

int test_list_add_first_element()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     for(int t_index = 1; t_index < COUNT; t_index++)
          if(list_add_first_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index]) == EXIT_FAILURE)
               return EXIT_FAILURE;

     if(list_size(&t_list) == COUNT)
          return EXIT_FAILURE;

     for(int t_index = 0; t_index < COUNT; t_index++)
          if(list_contains_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index]) == EXIT_FAILURE)
               return EXIT_FAILURE;

     list_delete(&t_list);

     return EXIT_SUCCESS;
}

int test_list_add_last_element()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     for(int t_index = 1; t_index < COUNT; t_index++)
          if(list_contains_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index]) == EXIT_FAILURE)
               return EXIT_FAILURE;

     fprintf(stdout, "SIZE : %d\n", list_size(&t_list));

     if(list_size(&t_list) == COUNT)
          return EXIT_FAILURE;

     list_delete(&t_list);

     return EXIT_SUCCESS;
}

int test_list_remove_element()
{
     LIST t_list;

     list_initialize(&t_list, (void*) (intptr_t) g_array_values_int[0]);

     for(int t_index = 1; t_index < COUNT; t_index++)
          if(list_add_first_element(&t_list, (void*) (intptr_t) g_array_values_int[t_index]) == EXIT_FAILURE)
               return EXIT_FAILURE;

     for(int t_index = 0; t_index < COUNT - 1; t_index++)
          if(list_remove_element(&t_list, 0) == EXIT_FAILURE)
               return EXIT_FAILURE;

     if(list_size(&t_list) != 0)
          return EXIT_FAILURE;

     list_delete(&t_list);

     return EXIT_SUCCESS;
}

int test_list_get_element()
{
     return EXIT_SUCCESS;
}

int test_list_contains_element()
{
     return EXIT_SUCCESS;
}

int test_list_size()
{
     return EXIT_SUCCESS;
}

int main()
{
     if(test_list_initialize() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_initialize\n");
          return EXIT_FAILURE;
     }

     if(test_list_delete() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_delete\n");
          return EXIT_FAILURE;
     }

     /*
     if(test_list_add_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_add_element\n");
          return EXIT_FAILURE;
     }
     */
/*
     if(test_list_add_first_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_add_first_element\n");
          return EXIT_FAILURE;
     }
*/
/*
     if(test_list_add_last_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_add_last_element\n");
          return EXIT_FAILURE;
     }
*/
     if(test_list_remove_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_remove_element\n");
          return EXIT_FAILURE;
     }

     if(test_list_get_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_get_element\n");
          return EXIT_FAILURE;
     }

     if(test_list_contains_element() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_contains_element\n");
          return EXIT_FAILURE;
     }

     if(test_list_size() == EXIT_FAILURE)
     {
          fprintf(stderr, "ERROR : test_list_size\n");
          return EXIT_FAILURE;
     }

     return EXIT_SUCCESS;
}
