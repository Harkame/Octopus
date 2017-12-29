#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <stdlib.h>

typedef struct CONNECTION
{
	int a_socket;

	pthread_t a_pthread;
} CONNECTION;

void create_connection(CONNECTION* p_connection_to_create);

#endif
