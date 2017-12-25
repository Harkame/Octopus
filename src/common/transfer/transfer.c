#include "./transfer.h"

int send_complete(int p_socket, void** p_buffer, int p_bytes_to_send)
{
  int t_total_sended_bytes = 0;

  while(p_bytes_to_send > 0)
  {
  int t_sended_bytes = send(p_socket, p_buffer + t_total_sended_bytes, p_bytes_to_send, 0);

  switch(t_sended_bytes)
  {
  case -1:
    return -1;

  case 0:
    return 0;
  }

  p_bytes_to_send -= t_sended_bytes;
  t_total_sended_bytes += t_sended_bytes;
}

return t_total_sended_bytes;
}

int recv_complete(int p_socket, void** p_buffer, int p_bytes_to_receive)
{
  int t_received_bytes = recv(p_socket,  p_buffer, p_bytes_to_receive, MSG_WAITALL);

  switch(t_received_bytes)
  {
    case -1:
      return -1;

    case 0:
      return 0;
  }

  return t_received_bytes;
}

int send_file_traces(int p_socket, FILE* p_file_to_send)
{
  int t_file_descriptor = fileno(p_file_to_send);

          if(t_file_descriptor == -1)
          return -1;

          struct stat t_stat;

          if(fstat(t_file_descriptor, &t_stat) == -1)
          return -1;

          int t_file_size =  t_stat.st_size;

          fprintf(stdout, MESSAGE_FILE_SIZE, t_file_size);

          switch(send_complete(p_socket, (void*) &t_file_size, sizeof(int)))
          {
                    case -1:
                              return -1;

                    case 0:
                              return 0;
          }

          char t_buffer[BUFSIZ];
          int t_remaining_bytes_to_send = t_stat.st_size;

          while(t_remaining_bytes_to_send > 0)
          {
            memset(t_buffer, 0, BUFSIZ);

                    int t_readed_bytes = fread(t_buffer, sizeof(char), BUFSIZ, p_file_to_send);

                    switch(send_complete(p_socket, (void*) &t_readed_bytes, sizeof(int)))
                    {
                              case -1:
                                        return -1;

                              case 0:
                                        return 0;
                    }

                    switch(send_complete(p_socket, (void*) t_buffer, t_readed_bytes))
                    {
                              case -1:
                                        return -1;

                              case 0:
                                        return 0;
                    }

                    fprintf(stdout, MESSAGE_REMAINING, t_remaining_bytes_to_send);

                    t_remaining_bytes_to_send -= t_readed_bytes;
          }

return t_file_size;
}


int receive_file_traces(int p_socket, FILE* p_file_to_receive)
{
  int t_file_size;

  switch(recv_complete(p_socket, (void*) &t_file_size, sizeof(int)))
  {
    case -1:
      return -1;

    case 0:
      return 0;
  }

  fprintf(stdout, MESSAGE_FILE_SIZE, t_file_size);

  int t_remaining_bytes_to_receive = t_file_size;

  char t_buffer[BUFSIZ];

  while(t_remaining_bytes_to_receive > 0)
  {
    memset(t_buffer, 0, BUFSIZ);

    int t_received_size;

    switch(recv_complete(p_socket, (void*) &t_received_size, sizeof(int)))
    {
      case -1:
        return -1;

      case 0:
        return 0;
    }

    switch(recv_complete(p_socket, (void*) t_buffer, t_received_size))
    {
      case -1:
        return -1;

      case 0:
        return 0;
    }

    fwrite(t_buffer, sizeof(char), t_received_size, p_file_to_receive);

    fprintf(stdout, MESSAGE_REMAINING, t_remaining_bytes_to_receive);

    t_remaining_bytes_to_receive -= t_received_size;
  }

  return t_file_size;
}

int bind_range(int p_socket, struct sockaddr_in* p_sockaddr_in, int p_port_mininimum, int p_port_maximum)
{
  for(int t_index = p_port_mininimum; t_index < p_port_maximum; t_index++)
  {
    p_sockaddr_in->sin_port = htons(t_index);

      if(bind(p_socket, (struct sockaddr *) p_sockaddr_in , sizeof(struct sockaddr_in)) == 0)
        return 0;
  }

  return -1;
}
