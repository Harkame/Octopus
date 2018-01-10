#include "./tchat.h"

LIST* g_tchat_socket = NULL;

void* tchat_handler(void* p_client_number)
{
	int t_client_number = (intptr_t) p_client_number;

	char t_buffer[BUFSIZ];
	char t_message[BUFSIZ];

	pthread_mutex_lock(&g_mutex);

	list_push_first(&g_tchat_socket, p_client_number);

	pthread_mutex_unlock(&g_mutex);

	while(1)
	{
		memset(t_buffer, 0, BUFSIZ);
		memset(t_message, 0, BUFSIZ);

		int t_message_length;

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) &t_message_length, sizeof(int)))
		{
			case -1:
				pthread_exit(NULL);
			break;

			case 0:
				pthread_exit(NULL);
			break;
		}

		for(int t_index = 0; t_index < list_size(g_tchat_socket); t_index++)
			if(list_get(g_tchat_socket, t_index) != p_client_number)
				if(send_complete(g_connections[(int) (intptr_t) list_get(g_tchat_socket, t_index)].a_socket, (void*) &t_message_length, sizeof(int)) == -1)
					exit_program();

		switch(receive_complete(g_connections[t_client_number].a_socket, (void*) t_message, t_message_length))
		{
			case -1:
				pthread_exit(NULL);
			break;

			case 0:
				pthread_exit(NULL);
			break;
		}

		for(int t_index = 0; t_index < list_size(g_tchat_socket); t_index++)
			if(list_get(g_tchat_socket, t_index) != p_client_number)
				if(send_complete(g_connections[(int) (intptr_t) list_get(g_tchat_socket, t_index)].a_socket, (void*) &t_message, t_message_length) == -1)
					exit_program();

		sprintf(t_buffer, "%d", t_client_number);
		strcat(t_buffer, " : ");

		strcat(t_buffer, t_message);

		print_message(t_buffer);
	}

	pthread_exit(NULL);
}
