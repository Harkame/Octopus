#include "./test_list_string.h"

int test_add_element_list_string()
{

    return 0;
}

int test_list_string_to_array()
{
     struct LIST_STRING* t_list_string = create_list_string();

     add_element_list_string(t_list_string, "Test");
     add_element_list_string(t_list_string, "Test");
     add_element_list_string(t_list_string, "Toto");

     char** t_buffer;
    t_buffer = alloca(15 * sizeof(char*));

    for(int t_index = 0; t_index < 15; t_index++)
         t_buffer[t_index] = alloca(50 * sizeof(char));

     list_string_to_array(t_list_string, t_buffer, 0, 3);

     for(int t_index = 0; t_index < 3; t_index++)
        fprintf(stdout, "%s\n", t_buffer[t_index]);

     free(t_list_string);

     return 0;
}

int main()
{
     test_add_element_list_string();

     test_list_string_to_array();

     return 0;
}
