#include "client.h"

void* read_handler()
{
    char t_received_buffer[BUFSIZ];

    while(1)
    {
        ssize_t t_readed_size = recv(g_socket, t_received_buffer, BUFSIZ, 0);

        if(t_readed_size == 0)
        {
            fprintf(stdout, "Connection lost\n");

            exit_program();
        }
        else if(t_readed_size == -1)
        {
            fprintf(stdout, "Connection lost\n");

            exit_program();
        }
        else
        {
            pthread_mutex_lock(&g_mutex);

            add_element_list_string(g_list_string, t_received_buffer);

            pthread_mutex_unlock(&g_mutex);

            adjust_list_string();

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

        int t_readed_length = get_line_non_blocking(&linep_bufferfer, t_readed_line, BUFSIZ);

        if(t_readed_length > 0)
        {
            if(strcmp(t_readed_line, "exit") == 0)
                exit_program();

            pthread_mutex_lock(&g_mutex);

            add_element_list_string(g_list_string, t_readed_line);

            pthread_mutex_unlock(&g_mutex);

            adjust_list_string();

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
    endwin();

    erase();

    close(g_socket);

    exit(0);
}

void re_initialize_windows()
{
    pthread_mutex_lock(&g_mutex);

    erase();

    g_window_textarea = subwin(stdscr, LINES / 3, COLS - 1, 1, 0);
    g_window_form     = subwin(stdscr, 3,  COLS - 1,  LINES - 3, 0);

    box(g_window_textarea, ACS_VLINE, ACS_HLINE);
    box(g_window_form, ACS_VLINE, ACS_HLINE);

    pthread_mutex_unlock(&g_mutex);
}

void foo()
{
    initialize_windows();

    refresh_windows();

    g_list_string = create_list_string();

    struct sockaddr_in t_sockaddr_in_client;

     g_socket = socket(AF_INET , SOCK_STREAM , 0);

     if (g_socket == -1)
     {
          perror("socket");
          exit_program();
     }

     t_sockaddr_in_client.sin_addr.s_addr = inet_addr(g_ip);
     t_sockaddr_in_client.sin_family           = AF_INET;
     t_sockaddr_in_client.sin_port               = htons(g_port);

     if(connect(g_socket , (struct sockaddr *)&t_sockaddr_in_client, sizeof(t_sockaddr_in_client)) < 0)
          exit_program();

    if(pthread_create(&g_write_thread, NULL, (void*) write_handler, NULL) == -1)
        exit_program();

    if(pthread_create(&g_read_thread, NULL, (void*) read_handler, NULL) == -1)
        exit_program();

    pthread_join(g_read_thread, NULL);
}

void help()
{
     fprintf(stdout, OPTION_IP);
     fprintf(stdout, OPTION_PORT);
     fprintf(stdout, OPTION_DIRECTORY);

     exit_program();
}

void print_textarea()
{
    pthread_mutex_lock(&g_mutex);

    char* t_buffer[size_list_string(g_list_string)];

    for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
        t_buffer[t_index] = alloca(50 * sizeof(char));

    list_string_to_array(g_list_string, t_buffer, 0, size_list_string(g_list_string));

    wclear(g_window_textarea);

    for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
        mvwprintw(g_window_textarea, 1 + t_index, 1, t_buffer[t_index]);

    pthread_mutex_unlock(&g_mutex);
}

void adjust_list_string()
{
    pthread_mutex_lock(&g_mutex);

    if(size_list_string(g_list_string) > (LINES / 3) - 3)
        remove_first_element_list_string(g_list_string);

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
    g_window_form     = subwin(stdscr, 3,  COLS - 1,  LINES - 3, 0);

    box(g_window_textarea, ACS_VLINE, ACS_HLINE);
    box(g_window_form, ACS_VLINE, ACS_HLINE);
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

int main()
{
     foo();

     return 0;
}
