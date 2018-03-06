#include "./transfer.h"

void* transfer_handler(void* p_client_number)
{
	int t_client_number = (intptr_t) p_client_number;

	char t_receive_buffer[BUFSIZ];

	char t_buffer[BUFSIZ] = {'\0'};

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

			close(g_connections[t_client_number].a_socket);

			pthread_exit(NULL);
		}
		else
		{
			strcat(t_buffer, t_receive_buffer);

			add_message(t_buffer);

			print_textarea();

			FILE* t_file = fopen(t_receive_buffer, "r");

			if (t_file == NULL)
			{
				close(g_connections[t_client_number].a_socket);
				pthread_exit(NULL);
			}

			if (send_file_traces(g_connections[t_client_number].a_socket, t_file) != 0)
			{
				close(g_connections[t_client_number].a_socket);
				pthread_exit(NULL);
			}

			fclose(t_file);

			memset(t_buffer, 0, strlen(t_buffer));
			memset(t_receive_buffer, 0, strlen(t_receive_buffer));
		}
	}

	pthread_exit(NULL);
}
