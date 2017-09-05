#include "file_transfer.h"

void send_file(const int p_socket, FILE* p_file_to_send)
{
          struct stat t_stat;

          if(stat((char*) p_file_to_send, &t_stat) == -1)
          {
                    //errno = 1;

                    return;
          }

          char t_file_size[BUFSIZ];

          if(send(p_socket, t_file_size, t_stat.st_size, 0) == -1)
          {
                    //errno = 1;

                    return;
          }

          int t_rest_to_send = t_stat.st_size;
          int t_bytes_sended;

          char t_buffer[BUFSIZ];

          while(t_rest_to_send > 0)
          {
                    memset(t_buffer, 0, BUFSIZ);
                    fread(t_buffer,BUFSIZ,1, p_file_to_send);

                    t_bytes_sended = send(p_socket, t_buffer, BUFSIZ, 0);

                    t_rest_to_send -= t_bytes_sended;
          }
}

void receive_file(const int p_socket, const char* p_directory)
{
     char t_buffer[BUFSIZ];
     memset(t_buffer, 0, BUFSIZ);

     strcpy(t_buffer, p_directory);

     FILE* t_file_to_receive = fopen(t_buffer, "w");

     if(t_file_to_receive == NULL)
     {
          //errno = 1;

          return;
     }

     freopen(NULL, "w+", t_file_to_receive);

     memset(t_buffer, 0, BUFSIZ);

     recv(p_socket, t_buffer, BUFSIZ, 0);

     int t_file_size = atoi(t_buffer);

     recv(p_socket, t_buffer, BUFSIZ, 0);

     char t_file_name[BUFSIZ];

     strcpy(t_buffer, t_file_name);

     if(t_file_size == -1)
     {
          //errno = 1;
          return;
     }
     else if(t_file_size == 0)
     {
          //errno = 1;
          return;
     }

     int t_rest_to_receive = t_file_size;
     ssize_t len;

     while(t_rest_to_receive > 0)
     {
          len = recv(p_socket, t_buffer, BUFSIZ, 0);

          switch(len)
          {
               case 0:
                    //errno = 1;
                    return;
               break;
               case -1:
                    //errno = 1;
                    return;
               break;
          }

          if(fwrite(t_buffer, sizeof(char), len, t_file_to_receive) != len)
                    fprintf(stderr, "error fwrite\n");

          t_rest_to_receive -= len;
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

                    memset(t_buffer, 0, BUFSIZ);
               }
               else
               {
                    strcat(t_buffer, t_directory_entry->d_name);
                    send(p_socket, t_buffer, strlen(t_buffer) * sizeof(char), 0);
                    FILE* t_file_to_receive = fopen(t_buffer, "w");

                    if(t_file_to_receive == NULL)
                    {
                         //errno = 1;
                         return;
                    }

                    send_file(p_socket, t_file_to_receive);

                    memset(t_buffer, 0, BUFSIZ);
               }
          }
     }

     send(p_socket, "-1", 2 * sizeof(char), 0);

     closedir(t_directory_to_send);
}
