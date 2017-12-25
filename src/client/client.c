#include "client.h"

void* read_handler()
{
	char t_received_buffer[BUFSIZ];

	while(1)
	{
		ssize_t t_readed_size = recv(g_socket, t_received_buffer,
		BUFSIZ, 0);

		if (t_readed_size == 0)
		{
			fprintf(stdout, "Connection lost\n");

			exit_program();
		}
		else
			if (t_readed_size == -1)
			{
				fprintf(stdout, "Connection lost\n");

				exit_program();
			}
			else
			{
				pthread_mutex_lock(&g_mutex);

				list_add_last_element(&g_list, t_received_buffer);

				pthread_mutex_unlock(&g_mutex);

				adjust_list();

				print_textarea();

				refresh_windows();
			}
	}
}

void* write_handler()
{
	struct input_line linep_bufferfer;
	make_input_line(&linep_bufferfer);

	while(1)
	{
		char t_readed_line[BUFSIZ];

		int t_readed_length = get_line_non_blocking(&linep_bufferfer, t_readed_line,
		BUFSIZ);

		if (t_readed_length > 0)
		{
			if (strcmp(t_readed_line, "exit") == 0)
				exit_program();

			pthread_mutex_lock(&g_mutex);

			list_add_last_element(&g_list, t_readed_line);

			pthread_mutex_unlock(&g_mutex);

			adjust_list();

			print_textarea();

			send(g_socket, t_readed_line, strlen(t_readed_line), 0);

			refresh_windows();
		}

		render_line(&linep_bufferfer);

		pthread_mutex_lock(&g_mutex);

		move(LINES - 2, 1);

		pthread_mutex_unlock(&g_mutex);
	}
}

void exit_program()
{
	close_windows();

	close(g_socket);

	perror("exit_program");

	exit(0);
}

void re_initialize_windows()
{
	pthread_mutex_lock(&g_mutex);

	erase();

	g_window_textarea = subwin(stdscr, LINES / 3, COLS - 1, 1, 0);
	g_window_form = subwin(stdscr, 3, COLS - 1, LINES - 3, 0);

	box(g_window_textarea, ACS_VLINE, ACS_HLINE);
	box(g_window_form, ACS_VLINE, ACS_HLINE);

	pthread_mutex_unlock(&g_mutex);
}

void foo()
{
	initialize_windows();

	refresh_windows();

	struct sockaddr_in t_sockaddr_in_client;

	g_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (g_socket == -1)
		exit_program();

	t_sockaddr_in_client.sin_addr.s_addr = inet_addr(g_ip);
	t_sockaddr_in_client.sin_family = AF_INET;
	t_sockaddr_in_client.sin_port = htons(g_port);

	if (connect(g_socket, (struct sockaddr *) &t_sockaddr_in_client, sizeof(t_sockaddr_in_client)) < 0)
		exit_program();

	struct input_line linep_bufferfer;
	make_input_line(&linep_bufferfer);

	send(g_socket, "transfer", BUFSIZ, 0);

	while(1)
	{
		char t_readed_line[BUFSIZ];

		int t_readed_length = get_line_non_blocking(&linep_bufferfer, t_readed_line,
		BUFSIZ);

		if (t_readed_length > 0)
		{
			if (strcmp(t_readed_line, "exit") == 0)
				exit_program();

			pthread_mutex_lock(&g_mutex);

			list_add_last_element(&g_list, t_readed_line);

			pthread_mutex_unlock(&g_mutex);

			adjust_list();

			print_textarea();

			send(g_socket, t_readed_line, strlen(t_readed_line), 0);

			FILE* t_file = fopen("/auto_home/ldaviaud/workspace/titi.txt", "w+");

			if (t_file == NULL)
			{
				exit_program();
			}

			if (receive_file(g_socket, t_file) != 0)
				exit_program();

			pthread_mutex_lock(&g_mutex);

			list_add_last_element(&g_list, "File received");

			pthread_mutex_unlock(&g_mutex);

			adjust_list();

			print_textarea();

			fclose(t_file);

			refresh_windows();
		}

		render_line(&linep_bufferfer);

		pthread_mutex_lock(&g_mutex);

		move(LINES - 2, 1);

		pthread_mutex_unlock(&g_mutex);
	}

	/*
	 if(pthread_create(&g_write_thread, NULL, (void*) write_handler, NULL) == -1)
	 exit_program();

	 if(pthread_create(&g_read_thread, NULL, (void*) read_handler, NULL) == -1)
	 exit_program();

	 if(pthread_join(g_read_thread, NULL) == -1)
	 exit_program();
	 */
}

void help()
{
	fprintf(stdout, HELP_OPTION_IP);
	fprintf(stdout, HELP_OPTION_PORT);
	fprintf(stdout, HELP_OPTION_DIRECTORY);

	exit_program();
}

void print_textarea()
{
	pthread_mutex_lock(&g_mutex);

	char* t_buffer[list_size(&g_list)];

	for(int t_index = 0; t_index < list_size(&g_list); t_index++)
		t_buffer[t_index] = alloca(50 * sizeof(char));

	list_to_array(&g_list, t_buffer, 0, list_size(&g_list));

	wclear(g_window_textarea);

	for(int t_index = 0; t_index < list_size(&g_list); t_index++)
		mvwprintw(g_window_textarea, 1 + t_index, 1, t_buffer[t_index]);

	pthread_mutex_unlock(&g_mutex);
}

void close_windows()
{
	pthread_mutex_lock(&g_mutex);

	erase();

	endwin();

	pthread_mutex_unlock(&g_mutex);
}

void adjust_list()
{
	pthread_mutex_lock(&g_mutex);

	if (list_size(&g_list) > (LINES / 3) - 3)
		list_remove_element(&g_list, 0);

	pthread_mutex_unlock(&g_mutex);
}

void initialize_windows()
{
	initscr();

	cbreak();
	nonl();
	timeout(0);
	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	intrflush(stdscr, 0);
	leaveok(stdscr, 1);

	g_window_textarea = subwin(stdscr, LINES / 3, COLS - 1, 1, 0);
	g_window_form = subwin(stdscr, 3, COLS - 1, LINES - 3, 0);

	box(g_window_textarea, ACS_VLINE, ACS_HLINE);
	box(g_window_form, ACS_VLINE, ACS_HLINE);
}

void initialize_options(struct OPTIONS* p_options)
{
	int t_result_option = 0;
	int t_option_index = 0;
	struct option t_long_options[] = {
		{
			"help", 0, NULL, 0 }, {
			NULL, 0, NULL, 0 } };

	while((t_result_option = getopt_long(p_options->a_options_count, p_options->a_options_values, "c:p:", t_long_options, &t_option_index)) != -1)
	{
		switch (t_result_option)
		{
			case 0:
				//if(strcasecmp("help", optarg_list)
				//help();
				break;

			case 'i':
				break;

			case 'p':
				g_port = atoi(optarg);
				break;

			case 'd':
				break;

			case 'f':
				break;

			default:
				//help();
				break;
		}
	}
}

void refresh_windows()
{
	pthread_mutex_lock(&g_mutex);

	box(g_window_textarea, ACS_VLINE, ACS_HLINE);
	box(g_window_form, ACS_VLINE, ACS_HLINE);

	wrefresh(g_window_textarea);
	wrefresh(g_window_form);

	refresh();

	move(LINES - 2, 1);

	pthread_mutex_unlock(&g_mutex);
}

int main(int p_count_arguments, char** p_arguments_values)
{
	struct OPTIONS t_options;
	t_options.a_options_count = p_count_arguments;
	t_options.a_options_values = p_arguments_values;

	initialize_options(&t_options);

	foo();

	return 0;
}
