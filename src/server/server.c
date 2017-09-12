#include "server.h"

void* command_handler()
{
    struct input_line linep_bufferfer;
    make_input_line(&linep_bufferfer);

    int lines_read = 0;
    while(1)
    {
        char t_readed_command[BUFSIZ];
        int len = -42;
    //    int len = get_line_non_blocking(&linep_bufferfer, t_readed_command, BUFSIZ);
        if(len > 0)
        {
            if(strcmp(t_readed_command, "exit") == 0)
                exit_program();

            pthread_mutex_lock(&g_mutex);

            add_element_list_string(g_list_string, t_readed_command);

            pthread_mutex_unlock(&g_mutex);


            adjust_list_string();

            //read_command_parameters(t_readed_command);

            print_textarea();

            lines_read++;

            refresh_windows();
        }
        //render_line(&linep_bufferfer);
    }
}

void refresh_windows()
{


    pthread_mutex_lock(&g_mutex);

    move(LINES - 2, 1);
    clrtoeol();

    box(g_window_textarea, ACS_VLINE, ACS_HLINE);
    box(g_window_form, ACS_VLINE, ACS_HLINE);

    wrefresh(g_window_textarea);
    wrefresh(g_window_form);

    pthread_mutex_unlock(&g_mutex);

}

void print_textarea()
{
    char** t_buffer;
    t_buffer = alloca(size_list_string(g_list_string) * sizeof(char*));



    pthread_mutex_lock(&g_mutex);

    for(int t_index; t_index < size_list_string(g_list_string); t_index++)
         t_buffer[t_index] = alloca(50 * sizeof(char));

    list_string_to_array(g_list_string, t_buffer, 0, size_list_string(g_list_string));

     wclear(g_window_textarea);

     for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
         mvwprintw(g_window_textarea,1 + t_index, 1, t_buffer[t_index]);

    pthread_mutex_unlock(&g_mutex);


    refresh_windows();
}

void adjust_list_string()
{
    pthread_mutex_lock(&g_mutex);

    if(size_list_string(g_list_string) > (LINES / 3) - 3)
        remove_first_element_list_string(g_list_string);

    pthread_mutex_unlock(&g_mutex);
}

void make_input_line(struct input_line* p_input_line_to_init)
{
    p_input_line_to_init->a_line = NULL;
    p_input_line_to_init->a_length = 0;
    p_input_line_to_init->a_capacity = 0;
    p_input_line_to_init->a_cursor = 0;
    p_input_line_to_init->a_last_rendered = 0;
}

void free_input_line(struct input_line* p_input_line_to_free)
{
    free(p_input_line_to_free->a_line);
}

void init_socket(int p_server_socket)
{
          if(p_server_socket == -1)
          {
                   exit_program();
          }

          struct sockaddr_in t_sockaddr_in_server;

          t_sockaddr_in_server.sin_family            = AF_INET;
          t_sockaddr_in_server.sin_addr.s_addr = INADDR_ANY;
          t_sockaddr_in_server.sin_port               = htons(g_port);

          if(bind(p_server_socket,(struct sockaddr *)&t_sockaddr_in_server , sizeof(t_sockaddr_in_server)) < 0)
                    exit_program();

          listen(p_server_socket , 10);
}

struct SERVICE* create_service()
{
    struct SERVICE* r_service = malloc(sizeof(struct SERVICE));

    r_service->a_service_name = malloc(255 * sizeof(char));

    return r_service;
}

struct OPTION* create_option()
{
    struct OPTION* r_option = malloc(sizeof(struct SERVICE));

    r_option->a_option_title    = malloc(20 * sizeof(char));
    r_option->a_option_value = malloc(20 * sizeof(char));

    return r_option;
}

void foo()
{
    initialize_windows();

    refresh_windows();

    g_list_string = create_list_string();

    initialize_services();

    initialize_connections();

    if(pthread_create(&g_command_thread, NULL, (void*) command_handler, NULL) == -1)
    exit_program();

    g_list = create_list_int();

    int t_server_socket = socket(AF_INET , SOCK_STREAM , 0);

    if(t_server_socket == -1)
        exit_program();

    init_socket(t_server_socket);

    struct sockaddr_in t_sockaddr_in_client;

    int t_index;

    while(1)
    {
        pthread_mutex_lock(&g_mutex);

        t_index = 0;
        //t_index = size_list_int(g_list);

/*
        if(t_index == 0)
            t_index = g_count_client;
        else
        {
            t_index = get_element_list_int(g_list, 0);
            remove_element_list_int(g_list, 0);
        }
        */

        pthread_mutex_unlock(&g_mutex);


        int c = sizeof(struct sockaddr_in);

        fd_set set, settmp ;
        FD_ZERO(&set) ; FD_SET(server_socket, &set) ;
        int max = server_socket ;
        while(1)
        {
            settmp = set ;
            select(max+1, &settmp, NULL, NULL, NULL) ;
            for(int df= 2 ; df <= max ; df++)
            {
                if (!FD_ISSET(df, &settmp))
                continue;
                if (df == server_socket)
                {
                    g_connections[t_index]->a_socket = accept(t_server_socket, (struct sockaddr*) &t_sockaddr_in_client, (socklen_t*) &c);
                    if (g_connections[t_index]->a_socket < 0)
                        error("accept failed");

                    printf("nouveau client connecté: %d\n", dSC);
                    FD_SET(dSC, &set) ;
                    if (max < g_connections[t_index]->a_socket)
                    max = g_connections[t_index]->a_socket ;
                    continue ;
                }
                if (recv(df, &message, MSG_LENGTH, 0) <= 0)
                {
                    FD_CLR(df, &set) ;
                    close(df);
                    continue ;
                }
            }
        }

        if(g_connections[t_index]->a_socket == -1)
            exit_program();

        char t_receive_buffer[BUFSIZ];

        ssize_t read_size = recv(g_connections[t_index]->a_socket, t_receive_buffer, BUFSIZ, 0);

        if(read_size == 0)
        {
            //fprintf(stdout, "Connection lost : %d (%zu)\n", g_count_client, read_size);
            add_first_element_list_int(g_list, g_count_client);

            g_count_client--;

            //(g_connections[g_count_client]->a_socket);

            //pthread_exit(NULL);
        }
        else if(read_size == -1)
        {
            fprintf(stdout, "Connection lost : %d (%zu)\n", g_count_client, read_size);

            //add_first_element_list_int(g_list, g_count_client);

            g_count_client--;

            //(g_connections[g_count_client]->a_socket);

            //pthread_exit(NULL);
        }
        else
        {
            char t_buffer[BUFSIZ];
            char t_buffer_int[BUFSIZ];

            pthread_mutex_lock(&g_mutex);

            sprintf(t_buffer_int, "%d", t_index);

            strcpy(t_buffer, "New connection (");
            strcat(t_buffer, t_buffer_int);
            strcat(t_buffer, ") ");
            strcat(t_buffer, " -> ");
            strcat(t_buffer, t_receive_buffer);

            add_element_list_string(g_list_string, t_buffer);

            pthread_mutex_unlock(&g_mutex);

            adjust_list_string();

            print_textarea();

            memset(t_buffer, 0, BUFSIZ);
            memset(t_receive_buffer, 0, BUFSIZ);

            pthread_create(&g_threads[t_index], NULL, (void*) g_services[0]->a_service_handler, &t_index);
        }

        pthread_mutex_lock(&g_mutex);

        g_count_client++;

        pthread_mutex_unlock(&g_mutex);
    }
}

void help()
{
    pthread_mutex_lock(&g_mutex);
    add_first_element_list_string(g_list_string, "help : print this message\n");
    pthread_mutex_unlock(&g_mutex);


    print_textarea();

    exit_program();
}

void read_command_parameters(char* p_command_to_read)
{

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
    g_window_form     = subwin(stdscr, 3,  COLS - 1,  LINES - 3, 0);

    box(g_window_textarea, ACS_VLINE, ACS_HLINE);
    box(g_window_form, ACS_VLINE, ACS_HLINE);
}

void exit_program()
{
    werase(g_window_textarea);
    werase(g_window_form);

    free(g_window_textarea);
    free(g_window_form);

    //for(int t_index = 0; t_index < g_count_client; t_index++)
    //    //(g_connections[t_index]->a_socket);

    exit(1);
}

void initialize_services()
{
    for(int t_index = 0; t_index < 10; t_index++)
      g_services[t_index] = create_service();

    g_services[0]->a_service_handler = tchat_handler;
}

void initialize_connections()
{
          for(int t_index = 0; t_index < 10; t_index++)
               g_connections[t_index] = create_connection();
}

int main(int argc , char* argv[])
{
          foo();

          return 0;
}
