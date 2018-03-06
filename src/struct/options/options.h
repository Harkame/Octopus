#ifndef __OPTIONS__H__
#define __OPTIONS__H__

#include "../../header.h"

typedef struct OPTIONS
{
	int a_options_count;

	char** a_options_values;
} OPTIONS;

int create_options(OPTIONS* p_options_to_create);

void delete_options(OPTIONS* p_options_to_create);

#endif
