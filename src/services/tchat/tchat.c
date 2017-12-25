#include "./tchat.h"

void* tchat_handler(void* p_client_number)
{
	int t_client_number = (intptr_t) p_client_number;

	char t_receive_buffer[BUFSIZ];

	char t_buffer[BUFSIZ] = {
		'\0' };

	while(1)
	{
		ssize_t t_receved_bytes = recv(g_connections[t_client_number].a_socket, t_receive_buffer, BUFSIZ, 0);

		sprintf(t_buffer, "%d", t_client_number);
		strcat(t_buffer, " : ");

		if (t_receved_bytes <= 0)
		{
			if (t_receved_bytes == 0)
				strcat(t_buffer, ERROR_RECV_CONNECTION_LOST);
			else
				strcat(t_buffer, ERROR_RECV_CONNECTION_OTHER);

			close_connection(t_client_number);

			add_message(t_buffer);

			print_textarea();

			pthread_exit(NULL);
		}
		else
		{
			strcat(t_buffer, t_receive_buffer);

			add_message(t_buffer);

			print_textarea();

			memset(t_buffer, 0, strlen(t_buffer));
			memset(t_receive_buffer, 0, strlen(t_receive_buffer));
		}
	}

	pthread_exit(NULL);
}
