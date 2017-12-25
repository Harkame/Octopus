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

int create_options(OPTIONS* p_options_to_create);

void delete_options(OPTIONS* p_options_to_create);

#endif
