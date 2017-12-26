#include "./system.h"

void* system_handler(void* p_client_number)
{
	int t_client_number = (intptr_t) p_client_number;

	while(1)
	{
		int t_command_length;

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) &t_command_length, sizeof(int)))
		{
			case -1:

			break;

			case 0:

			break;
		}

		char t_receive_buffer[t_command_length];

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) t_receive_buffer, t_command_length))
		{
			case -1:

			break;

			case 0:

			break;
		}


	}

	pthread_exit(NULL);
}
