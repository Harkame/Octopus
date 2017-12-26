#include "./tchat.h"

void* tchat_handler(void* p_client_number)
{
	int t_client_number = (intptr_t) p_client_number;

	char t_buffer[BUFSIZ];

	while(1)
	{
		int t_message_length;

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) &t_message_length, sizeof(int)))
		{
			case -1:

			break;

			case 0:

			break;
		}

		char t_message[t_message_length];

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) t_message, t_message_length))
		{
			case -1:

			break;

			case 0:

			break;
		}

		sprintf(t_buffer, "%d", t_client_number);
		strcat(t_buffer, " : ");

		strcat(t_buffer, t_message);

		add_message(t_buffer);

		print_textarea();

		memset(t_buffer, 0, strlen(t_buffer));
	}

	pthread_exit(NULL);
}
