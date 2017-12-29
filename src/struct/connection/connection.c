#include "./connection.h"

void create_connection(CONNECTION* p_connection_to_create)
{
	p_connection_to_create->a_socket = 0;

	p_connection_to_create->a_pthread = 0;
}
