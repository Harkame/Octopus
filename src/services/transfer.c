#include "./transfer.h"

void* transfer_handler(void* p_client_number)
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
          ssize_t t_receved_bytes = recv(g_connections[t_client_number]->a_socket, t_receive_buffer, BUFSIZ, 0);

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

               add_element_list_string(&g_list_string, t_buffer);

               pthread_mutex_unlock(&g_mutex);

               adjust_list_string();

               print_textarea();

               refresh_windows();

               FILE* p_file = fopen(t_receive_buffer, "r+");
               send_file(g_connections[t_client_number]->a_socket, p_file);
               fclose(p_file);

               memset(t_buffer, 0, strlen(t_buffer));
               memset(t_receive_buffer, 0, strlen(t_receive_buffer));
          }
     }
     return NULL;
}
