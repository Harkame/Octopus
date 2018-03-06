#ifndef _COMMON_TRANSFER_H_
#define _COMMON_TRANSFER_H_

#include "../../header.h"

#define MESSAGE_FILE_SIZE "File size : %d\n"
#define MESSAGE_REMAINING "Remaining : %d\n"

typedef struct TRANSFER
{
     int a_socket;

     FILE* a_file;

} TRANSFER;

/*
* Send while sended bytes < p_bytes_to_send
*/
int send_complete(int p_socket, void** p_buffer, int p_bytes_to_send);

/*
* Recv with flag : MSG_WAITALL
*/
int receive_complete(int p_socket, void** p_buffer, int p_bytes_to_receive);

/*
* Send p_file_to_send with p_socket, print traces
*/
int send_file_traces(int p_socket, FILE* p_file_to_send);

/*
* Receive p_file_to_receive with p_socket, print traces
*/
int receive_file_traces(int p_socket, FILE* p_file_to_send);

/*
* Try bind with port between p_port_mininimum to p_port_maximum
*/
int bind_range(int p_socket, struct sockaddr_in* p_sockaddr_in, int p_port_mininimum, int p_port_maximum);

#endif
