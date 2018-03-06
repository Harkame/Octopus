#include "client.h"

LIST* g_list = NULL;

void add_message(char* p_message)
{
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	char* t_message = malloc(sizeof(char) * strlen(p_message));

	strcpy(t_message, p_message);

	list_push_first(&g_list, t_message);

	if (pthread_mutex_unlock(&g_mutex) == -1)
		exit_program();

	adjust_list();
}

void print_message(char* p_message_to_print)
{
	add_message(p_message_to_print);

	print_textarea();
}

void* read_handler()
{
	//char t_received_buffer[BUFSIZ];
	char t_message[BUFSIZ];

	while(1)
	{
		memset(t_message, 0, BUFSIZ);

		int t_message_length;

		switch(receive_complete(g_socket, (void*) &t_message_length, sizeof(int)))
		{
			case -1:
				pthread_exit(NULL);
			break;

			case 0:
				pthread_exit(NULL);
			break;
		}

		switch(receive_complete(g_socket, (void*) t_message, t_message_length))
		{
			case -1:
				pthread_exit(NULL);
			break;

			case 0:
				pthread_exit(NULL);
			break;
		}

		print_message(t_message);
	}
}

void* write_handler()
{
	struct input_line linep_bufferfer;
	make_input_line(&linep_bufferfer);
	char t_readed_line[BUFSIZ];

	while(1)
	{
		int t_readed_length = get_line_non_blocking(&linep_bufferfer, t_readed_line,
		BUFSIZ);

		if (t_readed_length > 1)
		{
			if (strcmp(t_readed_line, "exit") == 0)
				exit_program();

			int t_size = strlen(t_readed_line);

			if(send_complete(g_socket, (void*) &t_size, sizeof(int)) == -1)
				exit_program();

			if(send_complete(g_socket, (void*) t_readed_line, t_size) == -1)
				exit_program();

			print_message(t_readed_line);

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

	int t_code = 0;

	if(send_complete(g_socket, (void*) &t_code, sizeof(int)) == -1)
	{
		exit_program();
	}

	if(pthread_create(&g_write_thread, NULL, write_handler, NULL) == -1)
		exit_program();

	if(pthread_create(&g_read_thread, NULL, read_handler, NULL) == -1)
		exit_program();

	if(pthread_join(g_read_thread, NULL) == -1)
		exit_program();
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
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	char* t_buffer[list_size(g_list)];

	for(int t_index = 0; t_index < list_size(g_list); t_index++)
		t_buffer[t_index] = alloca(50 * sizeof(char));

	list_to_array(g_list, (void*) t_buffer, 0, list_size(g_list));

	if (wclear(g_window_textarea) == -1)
		exit_program();

	for(int t_index = 0; t_index < list_size(g_list); t_index++)
		if (mvwprintw(g_window_textarea, 1 + t_index, 1, t_buffer[t_index]) == -1)
			exit_program();

	if (pthread_mutex_unlock(&g_mutex) == -1)
		exit_program();

	refresh_windows();
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

	if (list_size(g_list) > (LINES / 3) - 3)
		list_pop_last(&g_list);

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
