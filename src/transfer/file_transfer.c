#include "file_transfer.h"

void exit_program();

void send_file(const int p_socket, FILE* p_file_to_send)
{
          struct stat t_stat;

          int fd = fileno(p_file_to_send);

          if(fstat(fd, &t_stat) == -1)
               exit_program();

          char t_file_size[BUFSIZ];

          sprintf(t_file_size, "%ld", t_stat.st_size);

          if(send(p_socket, t_file_size, strlen(t_file_size), 0) == -1)
               exit_program();

          int t_rest_to_send = t_stat.st_size;
          int t_bytes_sended;

          char t_buffer[BUFSIZ];

          while(t_rest_to_send > 0)
          {
                    memset(t_buffer, 0, BUFSIZ);
                    fread(t_buffer, 1, BUFSIZ, p_file_to_send);

                    t_bytes_sended = send(p_socket, t_buffer, BUFSIZ, 0);

                    t_rest_to_send -= t_bytes_sended;
          }
}

void receive_file(const int p_socket, FILE* p_file_to_receive)
{
     extern int g_count_client;
     extern pthread_mutex_t g_mutex;
     extern struct LIST_STRING g_list_string;
     extern struct CONNECTION* g_connections[];

     char t_buffer[BUFSIZ];
     pthread_mutex_lock(&g_mutex);

     add_element_list_string(&g_list_string, "Attend taille");

     pthread_mutex_unlock(&g_mutex);

     adjust_list_string();

     print_textarea();

     refresh_windows();

     recv(p_socket, t_buffer, BUFSIZ, 0);



     int t_file_size = atoi(t_buffer);

     if(t_file_size <= 0)
          exit_program();

          pthread_mutex_lock(&g_mutex);

          add_element_list_string(&g_list_string, "g la taille");

          pthread_mutex_unlock(&g_mutex);

          adjust_list_string();

          print_textarea();

          refresh_windows();

     size_t t_rest_to_receive = t_file_size;
     size_t t_receved_length;

     while(t_rest_to_receive > 0)
     {
          t_receved_length = recv(p_socket, t_buffer, BUFSIZ, 0);

          switch(t_receved_length)
          {
               case 0:
                    exit_program();
               break;

               case -1:
                    exit_program();
               break;
          }

          fwrite(t_buffer, sizeof(char), t_receved_length, p_file_to_receive);

          t_rest_to_receive -= t_receved_length;
     }
}

void send_directory(const int p_socket, const char* p_directory_path_to_send)
{
     DIR* t_directory_to_send = opendir(p_directory_path_to_send);

     if(t_directory_to_send == NULL)
     {
          //errno = 1;
          return;
     }

     struct dirent* t_directory_entry;

     while ((t_directory_entry = readdir(t_directory_to_send)) != NULL)
     {
          char t_buffer[255];
          strcpy(t_buffer, p_directory_path_to_send);

          if((strcmp(t_directory_entry->d_name, ".") != 0) && (strcmp(t_directory_entry->d_name, "..") != 0))
          {
               strcat(t_buffer, t_directory_entry->d_name);

               if(t_directory_entry->d_type == DT_DIR)
               {
                    strcat(t_buffer, "/");
                    send(p_socket, t_buffer, strlen(t_buffer) * sizeof(char), 0);

                    send_directory(p_socket, t_buffer);
               }
               else
               {
                    strcat(t_buffer, t_directory_entry->d_name);
                    send(p_socket, t_buffer, strlen(t_buffer) * sizeof(char), 0);
                    FILE* p_file_to_receive = fopen(t_buffer, "w");

                    if(p_file_to_receive == NULL)
                    {
                         //errno = 1;
                         return;
                    }

                    send_file(p_socket, p_file_to_receive);
               }
          }
     }

     send(p_socket, "-1", 2 * sizeof(char), 0);

     closedir(t_directory_to_send);
}
