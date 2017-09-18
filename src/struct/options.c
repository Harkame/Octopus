#include "./options.h"

struct OPTION* create_option()
{
     struct OPTION* r_option = malloc(sizeof(struct OPTION));

     r_option->a_option_title = malloc(100 * sizeof(char));

     r_option->a_option_value = malloc(100 * sizeof(char));

     return r_option;
}
