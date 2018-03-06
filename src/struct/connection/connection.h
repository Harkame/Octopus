#ifndef __CONNECTION__H__
#define __CONNECTION__H__

#include "../../header.h"

typedef struct CONNECTION
{
	int a_socket;

	pthread_t a_pthread;
} CONNECTION;

void create_connection(CONNECTION* p_connection_to_create);

#endif
