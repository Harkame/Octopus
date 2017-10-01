#include "./tchat.h"

void* tchat_handler(void* p_client_number)
{
     int t_client_number = (int) (intptr_t) p_client_number;

     extern int g_count_client;
     extern pthread_mutex_t g_mutex;
     extern struct LIST_STRING g_list_string;
     extern struct CONNECTION* g_connections[];

     char t_receive_buffer[BUFSIZ];

     char t_buffer[BUFSIZ] = {'\0'};


     while(1)
     {
          fd_set t_set;
          fd_set t_set_save;

          FD_ZERO(&t_set);
          FD_SET(g_connections[t_client_number]->a_socket, &t_set);

          int t_maximum_position = g_connections[t_client_number]->a_socket;

          ssize_t t_receved_bytes = 1;

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

                         goto end;

                         FD_SET(g_connections[t_index]->a_socket, &t_set);

                         FD_CLR(t_index, &t_set);
                    }
               }
          }

          end:

          sprintf(t_buffer, "%d", t_client_number);
          strcat(t_buffer, " : ");

          if(t_receved_bytes <= 0)
          {
               if(t_receved_bytes == 0)
                    strcat(t_buffer, ERROR_RECV_CONNECTION_LOST);
               else
                    strcat(t_buffer, ERROR_RECV_CONNECTION_OTHER);

               pthread_mutex_lock(&g_mutex);

               g_count_client--;

               close(g_connections[t_client_number]->a_socket);

               add_element_list_string(&g_list_string, t_buffer);

               pthread_mutex_unlock(&g_mutex);

               adjust_list_string();

               print_textarea();

               refresh_windows();

               pthread_exit(NULL);
          }
          else
          {
               strcat(t_buffer, t_receive_buffer);

               pthread_mutex_lock(&g_mutex);

               add_element_list_string(&g_list_string,t_buffer);

               pthread_mutex_unlock(&g_mutex);

               adjust_list_string();

               print_textarea();

               refresh_windows();

               memset(t_buffer, 0, strlen(t_buffer));
               memset(t_receive_buffer, 0, strlen(t_receive_buffer));
          }
     }
     return NULL;
}
