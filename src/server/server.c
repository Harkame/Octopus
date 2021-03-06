#include "./server.h"

int g_port = DEFAULT_VALUE_PORT;

CONNECTION* g_connections;

WINDOW* g_window_textarea;
WINDOW* g_window_form;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t g_command_thread;

LIST* g_list = NULL;

HANDLER* g_services;

sem_t g_semaphore;

int g_number_services = DEFAULT_NUMBER_SERVICES;

void* command_handler()
{
	struct input_line linep_bufferfer;

	make_input_line(&linep_bufferfer);

	struct OPTIONS t_options;

	create_options(&t_options);

	while(1)
	{
		char t_readed_command[BUFSIZ];

		int len = get_line_non_blocking(&linep_bufferfer, t_readed_command,
		BUFSIZ);

		if (len > 0)
		{
			if (strcmp(t_readed_command, "exit") == 0)
			{
				delete_options(&t_options);
				exit_program();
			}

			print_message(t_readed_command);

			//parse_command(&t_options, t_readed_command);

			//initialize_options(&t_options);
		}

		render_line(&linep_bufferfer);

		if (pthread_mutex_lock(&g_mutex) == -1)
			exit_program();

		if (move(LINES - 2, 1) == -1)
			exit_program();

		if (pthread_mutex_unlock(&g_mutex) == -1)
			exit_program();
	}

	pthread_exit(NULL);
}

void refresh_windows()
{
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	if (box(g_window_textarea, ACS_VLINE, ACS_HLINE) == -1)
		exit_program();

	if (box(g_window_form, ACS_VLINE, ACS_HLINE) == -1)
		exit_program();

	if (wrefresh(g_window_textarea) == -1)
		exit_program();

	if (wrefresh(g_window_form) == -1)
		exit_program();

	if (refresh() == -1)
		exit_program();

	if (move(LINES - 2, 1) == -1)
		exit_program();

	if (pthread_mutex_unlock(&g_mutex) == -1)
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

void adjust_list()
{
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	if (list_size(g_list) > (LINES / 3) - 3)
	{
		free(list_get(g_list, list_size(g_list)));
		list_pop_last(&g_list);
	}

	if (pthread_mutex_unlock(&g_mutex) == -1)
		exit_program();
}

void initialize_socket(int p_server_socket_to_initialize)
{
	struct sockaddr_in t_sockaddr_in_server;

	t_sockaddr_in_server.sin_family = AF_INET;
	t_sockaddr_in_server.sin_addr.s_addr = INADDR_ANY;
	t_sockaddr_in_server.sin_port = htons(g_port);

	if (bind(p_server_socket_to_initialize, (struct sockaddr *) &t_sockaddr_in_server, sizeof(t_sockaddr_in_server)) == -1)
		exit_program();

	if (listen(p_server_socket_to_initialize, 10) == -1)
		exit_program();
}

void print_message(char* p_message_to_print)
{
	add_message(p_message_to_print);

	print_textarea();
}

void initialize()
{
	if(sem_init(&g_semaphore, 0, 0) == -1)
	{
		exit_program();
	}

	g_services = malloc(sizeof(HANDLER) * g_number_services);

	if(g_services == NULL)
	{
		//TODO
		exit_program();
	}

	g_connections = malloc(sizeof(CONNECTION) * g_number_services);

	initialize_services();

	initialize_connections();

	initialize_windows();

	refresh_windows();
}

void foo()
{
	if (pthread_create(&g_command_thread, NULL, command_handler, NULL) == -1)
		exit_program();

	int t_server_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (t_server_socket == -1)
		exit_program();

	initialize_socket(t_server_socket);

	struct sockaddr_in t_sockaddr_in_client;

	while(1)
	{
		int t_index;

		if(sem_getvalue(&g_semaphore, &t_index) == -1)
		{
		    perror(ERROR_MESSAGE_SEM_GETVALUE);

		    exit_program();
		}

		char t_receive_buffer[BUFSIZ];
		socklen_t t_socketlen = sizeof(t_sockaddr_in_client);
		g_connections[t_index].a_socket = accept(t_server_socket, (struct sockaddr*) &t_sockaddr_in_client, &t_socketlen);

		if (g_connections[t_index].a_socket == -1)
			exit_program();

		int t_service_id;

		switch (receive_complete(g_connections[t_index].a_socket, (void*) &t_service_id, sizeof(int)))
		{
			case -1:

				break;

			case 0:

				break;
		}

		char t_buffer[BUFSIZ];
		char t_buffer_int[BUFSIZ];

		sprintf(t_buffer_int, "%d", t_index);

		strcpy(t_buffer, "New connection (");
		strcat(t_buffer, "yoyo");
		strcat(t_buffer, ") ");
		strcat(t_buffer, " -> ");

		print_message(t_buffer);

		if (pthread_create(&g_connections[t_index].a_pthread,
		NULL, g_services[t_service_id].a_service_handler, (void*) (intptr_t) t_index) != OK)
			exit_program();

		memset(t_receive_buffer, 0, BUFSIZ);

		if(sem_post(&g_semaphore) == -1)
		{
			perror(ERROR_MESSAGE_SEM_POST);
		}
	}
}

void help()
{
	close_windows();

	close_sockets();

	fprintf(stdout, HELP_OPTIONS_PORT);

	exit(1);
}

void read_command_parameters(char* p_command_to_read)
{
	fprintf(stdout, "%s\n", p_command_to_read);
	//int t_inserted = 0;

	/*

	 for(int t_index = 0; p_command_to_read[t_index] != '\0'; t_index++)
	 {
	 if(p_command_to_read[t_index] == '-')
	 {
	 t_index++;
	 int t_save_index = t_index;

	 if(p_command_to_read[t_index] == '-') //Long option
	 {
	 t_index++;
	 t_save_index = t_index;

	 while(p_command_to_read[t_index] != ' ')
	 {
	 strcat(t_options[t_inserted], &p_command_to_read[t_index]);
	 t_index++;
	 }

	 t_inserted++;
	 }
	 else if(p_command_to_read[t_index] != ' ') //Short option
	 {
	 strcat(t_options[t_inserted], &p_command_to_read[t_index]);

	 t_index++;

	 t_inserted++;
	 }
	 else
	 while(p_command_to_read[t_index] == ' ')
	 t_index++;
	 }
	 }

	 for(int t_index = 0; t_index < t_count_command_parameters; t_index++)
	 {
	 fprintf(stdout, "[]%s]\n", t_command_to_read[t_index]);
	 }
	 */
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

void close_windows()
{
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	if (erase() == -1)
		exit_program();

	if (endwin() == -1)
		exit_program();

	if (pthread_mutex_unlock(&g_mutex) == -1)
		exit_program();
}

void close_sockets()
{
	if (pthread_mutex_lock(&g_mutex) == -1)
		exit_program();

	int t_sem_value;

	if(sem_getvalue(&g_semaphore, &t_sem_value) == -1)
	{
		perror(ERROR_MESSAGE_SEM_GETVALUE);
	}

	if(pthread_mutex_unlock(&g_mutex) == -1)
		exit_program();
}

void exit_program()
{
	close_windows();

	close_sockets();

	exit(errno);
}

void initialize_services()
{
	g_services[0].a_service_handler = tchat_handler;
	g_services[1].a_service_handler = system_handler;
	g_services[2].a_service_handler = transfer_handler;
}

void initialize_connections()
{
	for(int t_index = 0; t_index < 10; t_index++)
		create_connection(&g_connections[t_index]);
}

void parse_command(struct OPTIONS* p_options_readed, char* p_command)
{
	const char t_separator[1] = " ";
	char* t_token;

	t_token = strtok(p_command, t_separator);

	int t_count = 0;

	while(t_token != NULL)
	{
		strcpy(p_options_readed->a_options_values[t_count], t_token);
		t_token = strtok(NULL, p_command);
	}

	p_options_readed->a_options_count = t_count - 1;
}

void initialize_options(OPTIONS* p_options)
{
	int t_result_option = 0;
	int t_option_index = 0;
	struct option t_long_options[] =
	{
		{
			"help", no_argument, NULL, 'h'}, {
			NULL, 0, NULL, 0 }
	};

	while((t_result_option = getopt_long(p_options->a_options_count, p_options->a_options_values, "h", t_long_options, &t_option_index)) != -1)
	{
		switch (t_result_option)
		{
			case 0:
				//if(strcasecmp("help", optarg))
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
		}
	}
}

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

int close_connection(int p_number_client)
{
	if (pthread_mutex_lock(&g_mutex) == EXIT_FAILURE)
		return -1;

	if(sem_wait(&g_semaphore) == -1)
	{
		perror(ERROR_MESSAGE_SEM_WAIT);
	}

	close(g_connections[p_number_client].a_socket);

	if (pthread_mutex_lock(&g_mutex) == EXIT_FAILURE)
		return -1;

	return 0;
}

int main(int p_count_arguments, char** p_arguments_values)
{
	struct sigaction t_sigaction;
	t_sigaction.sa_handler = &exit_program;
	t_sigaction.sa_flags = 0;

	if(sigaction(SIGINT, &t_sigaction, NULL) == -1)
	{
		perror(ERROR_MESSAGE_SIGACTION);
		exit_program();
	}

	OPTIONS t_options;
	t_options.a_options_count = p_count_arguments;
	t_options.a_options_values = p_arguments_values;

	initialize();

	initialize_options(&t_options);

	foo();

	return EXIT_SUCCESS;
}
