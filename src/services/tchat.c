#include "./tchat.h"

void tchat_handler(int* p_client_number)
{
    int t_client_number = *p_client_number;

    extern int g_count_client;
    extern pthread_mutex_t g_mutex;
    extern struct LIST_STRING* g_list_string;
    extern struct CONNECTION* g_connections[];

    char t_receive_buffer[BUFSIZ];

    while(1)
    {
        ssize_t t_receved_bytes = recv(g_connections[t_client_number]->a_socket, t_receive_buffer, BUFSIZ, 0);

        if(t_receved_bytes <= 0)
        {
            pthread_mutex_init(&g_mutex, NULL);

            pthread_mutex_lock(&g_mutex);

            g_count_client--;

            pthread_mutex_unlock(&g_mutex);

            close(g_connections[t_client_number]->a_socket);

            pthread_exit(NULL);
        }
        else
        {
            char t_buffer[BUFSIZ];

            sprintf(t_buffer, "%d", t_client_number);
            strcat(t_buffer, " : ");
            strcat(t_buffer, t_receive_buffer);

            pthread_mutex_init(&g_mutex, NULL);

            pthread_mutex_lock(&g_mutex);

            add_element_list_string(g_list_string, t_buffer);

            pthread_mutex_unlock(&g_mutex);

            adjust_list_string();

            print_textarea();

            move(LINES - 2, 1);
            clrtoeol();

            memset(t_receive_buffer, 0, BUFSIZ);
        }
    }
}
