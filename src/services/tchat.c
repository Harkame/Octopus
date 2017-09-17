#include "./tchat.h"

void* tchat_handler(void* p_client_number)
{
     int t_client_number = (int) (intptr_t) p_client_number;

     extern int g_count_client;
     extern pthread_mutex_t g_mutex;
     extern struct LIST_STRING* g_list_string;
     extern struct CONNECTION* g_connections[];

     char t_receive_buffer[BUFSIZ];

     while(1)
     {
          fd_set t_set;
          fd_set t_set_save;

          FD_ZERO(&t_set);
          FD_SET(g_connections[t_client_number]->a_socket, &t_set);

          int t_maximum_position = g_connections[t_client_number]->a_socket;

          ssize_t t_receved_bytes;

          while(1)
          {
               t_set_save = t_set;

               select(t_maximum_position + 1, &t_set_save, NULL, NULL, NULL);

               for(int t_index = 2; t_index <= t_maximum_position; t_index++)
               {
                    if(!FD_ISSET(t_index, &t_set_save))
                         continue;

                    if(t_index == g_connections[t_client_number]->a_socket)
                    {
                         t_receved_bytes = recv(g_connections[t_client_number]->a_socket, t_receive_buffer, BUFSIZ, 0);

                         if(g_connections[t_index]->a_socket == -1)
                         exit_program();

                         goto end;

                         FD_SET(g_connections[t_index]->a_socket, &t_set);

                         FD_CLR(t_index, &t_set);
                    }

                    if(recv(g_connections[t_index]->a_socket, t_receive_buffer, BUFSIZ, 0) < 0)
                    {
                         FD_CLR(t_index, &t_set);
                         continue;
                    }
               }
          }

          end:

          if(t_receved_bytes <= 0)
          {
               pthread_mutex_lock(&g_mutex);

               g_count_client--;

               pthread_mutex_unlock(&g_mutex);

               close(g_connections[t_client_number]->a_socket);

               pthread_exit(NULL);
          }
          else
          {
               char t_buffer[BUFSIZ] = {'\0'};

               sprintf(t_buffer, "%d", t_client_number);

               strcat(t_buffer, " : ");
               strcat(t_buffer, t_receive_buffer);

               pthread_mutex_lock(&g_mutex);

               add_element_list_string(g_list_string,t_buffer);

               pthread_mutex_unlock(&g_mutex);

               adjust_list_string();

               print_textarea();

               refresh_windows();
          }
     }
     return NULL;
}
