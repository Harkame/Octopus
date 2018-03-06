#include "./connection.h"

int create_connection(CONNECTION* p_connection_to_create)
{
	if(p_connection_to_create == NULL)
		return -1;

	p_connection_to_create->a_socket = 0;

	p_connection_to_create->a_pthread = 0;

	return 0;
}
