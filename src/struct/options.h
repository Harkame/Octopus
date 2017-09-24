#ifndef OPTIONS_H
#define OPTINOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OPTIONS
{
     int a_options_count;

     char** a_options_values;
} OPTIONS;

void create_options(struct OPTIONS*);

void delete_options(struct OPTIONS*);

#endif
