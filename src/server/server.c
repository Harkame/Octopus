#include "server.h"

void* command_handler()
{
    struct input_line linep_bufferfer;
    make_input_line(&linep_bufferfer);

    int lines_read = 0;
    while(1)
    {
        move(46, 1);
        mvwprintw(g_window_form, 1, 1, PROMPT_MESSAGE);
        char t_readed_command[BUFSIZ];
        int len = get_line_non_blocking(&linep_bufferfer, t_readed_command, BUFSIZ);
        if(len > 0)
        {
            if(strcmp(t_readed_command, "exit") == 0)
                exit_program();

            pthread_mutex_init(&g_mutex, NULL);

            pthread_mutex_lock(&g_mutex);
            add_element_list_string(g_list_string, t_readed_command);

            if(size_list_string(g_list_string) > 10)
                remove_first_element_list_string(g_list_string);
            pthread_mutex_unlock(&g_mutex);

            read_command_parameters(t_readed_command);

            /*
            if(send(g_sockets[0], line, strlen(line), 0) == -1)
            {
                perror("send");

                exit_program();
            }
            */

            print_textarea();

            lines_read ++;

            move(46, 1);
            clrtoeol();
        }

        render_line(&linep_bufferfer);

        pthread_mutex_lock(&g_mutex);
        wrefresh(g_window_textarea);
        wrefresh(g_window_form);
        refresh();
        pthread_mutex_unlock(&g_mutex);
    }
}

void print_textarea()
{
    if(size_list_string(g_list_string) > 10)
        remove_first_element_list_string(g_list_string);

    char** t_buffer;
    t_buffer = alloca(10 * sizeof(char*));

    for(int t_index; t_index < 10; t_index++)
         t_buffer[t_index] = alloca(50 * sizeof(char));

    pthread_mutex_init(&g_mutex, NULL);

    pthread_mutex_lock(&g_mutex);

    list_string_to_array(g_list_string, t_buffer, 0, 10);

     for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
     {
         move(1 + t_index, 1);
         clrtoeol();
     }

     for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
         mvwprintw(g_window_textarea,1 + t_index, 1, t_buffer[t_index]);

     box(g_window_textarea, ACS_VLINE, ACS_HLINE);

    wrefresh(g_window_textarea);
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
          {
                    exit(1);
          }

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

          g_window_textarea = subwin(stdscr, LINES / 3, COLS, 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
          g_window_form = subwin(stdscr, LINES / 16, COLS,  45, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent


          box(g_window_textarea, ACS_VLINE, ACS_HLINE);
          box(g_window_form, ACS_VLINE, ACS_HLINE);

          wrefresh(g_window_textarea);
          wrefresh(g_window_form);
          refresh();

          wmove(g_window_form, 1, 1);
          mvwprintw(g_window_form, 1, 1, PROMPT_MESSAGE);

          g_list_string = create_list_string();

          initialize_services();

          if(pthread_create(&g_command_thread, NULL, (void*) command_handler, NULL) == -1)
            exit_program();

          g_list = create_list_int();

          int t_server_socket = socket(AF_INET , SOCK_STREAM , 0);

          if(t_server_socket == -1)
          {
                    perror("socket");
                   exit_program();
          }

          init_socket(t_server_socket);

          struct sockaddr_in t_sockaddr_in_client;

          int t_index;

          while(1)
          {
                    t_index = size_list_int(g_list);

                    //if(t_index == 0)
                    t_index = 0;
                    //else
                    //          t_index = remove_first_element_list_int(g_list);

                    int c = sizeof(struct sockaddr_in);

                    g_sockets[t_index] = accept(t_server_socket, (struct sockaddr*) &t_sockaddr_in_client, (socklen_t*) &c);

                    if(g_sockets[t_index] == -1)
                    {
                             exit_program();
                    }

                    char t_buffer[BUFSIZ];

                    ssize_t read_size = recv(g_sockets[g_count_client], t_buffer, BUFSIZ, 0);

                    char toto[255];
                    sprintf(toto, "%d", g_count_client);
                    strcat(toto, " -> ");
                    strcat(toto, t_buffer);

                     add_first_element_list_string(g_list_string, toto);

                    if(read_size == 0)
                    {
                              fprintf(stdout, "Connection lost : %d (%zu)\n", g_count_client, read_size);
                              add_first_element_list_int(g_list, g_count_client);

                              g_count_client--;

                              close(g_sockets[g_count_client]);

                              pthread_exit(NULL);
                    }
                    else if(read_size == -1)
                    {
                              fprintf(stdout, "Connection lost : %d (%zu)\n", g_count_client, read_size);

                              add_first_element_list_int(g_list, g_count_client);

                              g_count_client--;

                              close(g_sockets[g_count_client]);

                              pthread_exit(NULL);
                    }
                    else
                    {
                        pthread_mutex_lock(&g_mutex);
                        add_element_list_string(g_list_string, t_buffer);

                        if(size_list_string(g_list_string) > 10)
                            remove_first_element_list_string(g_list_string);
                        pthread_mutex_unlock(&g_mutex);

                        print_textarea();

                        memset(t_buffer, 0, BUFSIZ);

                        move(46, 1);
                        clrtoeol();

                        if(pthread_create(&g_threads[t_index], NULL, (void*) g_services[0]->a_service_function, &t_index) == -1)
                        {
                                 exit_program();
                        }

                      memset(t_buffer, 0, BUFSIZ);
                    }

                    g_count_client++;
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
    print_textarea();

    int t_count_command_parameters = 0;

    for(int t_index = 0; p_command_to_read[t_index] != '\0'; t_index++)
        if(p_command_to_read[t_index] == ' ')
            t_count_command_parameters++;

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
}

void exit_program()
{
    endwin();

    free(g_window_textarea);
    free(g_window_form);

    close(g_sockets[0]);

    exit(0);
}

void initialize_services()
{
    g_services = malloc(10 * sizeof(struct SERVICE));

    for(int t_index = 0; t_index < 10; t_index++)
      g_services[t_index] = create_service();

    g_services[0]->a_service_function = &(tchat_handler);
}

int main(int argc , char *argv[])
{
          foo();

          return 0;
}
