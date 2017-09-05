#include "./tchat.h"

void tchat_handler(int* p_number)
{
    int t_number = *p_number;

    extern int g_count_client;
    extern pthread_mutex_t g_mutex;
    extern struct LIST_STRING* g_list_string;
    extern struct LIST_INT* g_list;
    extern int g_sockets[];

    char t_buffer[BUFSIZ];

    while(1)
    {
            ssize_t read_size = recv(g_sockets[t_number], t_buffer, BUFSIZ, 0);

            if(read_size == 0)
            {
                      fprintf(stdout, "Connection lost : %d (%zu)\n", t_number, read_size);
                      add_first_element_list_int(g_list, t_number);

                      g_count_client--;

                      close(g_sockets[t_number]);

                      pthread_exit(NULL);
            }
            else if(read_size == -1)
            {
                      fprintf(stdout, "Connection lost : %d (%zu)\n", t_number, read_size);

                      add_first_element_list_int(g_list, t_number);

                      g_count_client--;

                      close(g_sockets[t_number]);

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

              memset(t_buffer, 0, BUFSIZ);
            }
    }
}
