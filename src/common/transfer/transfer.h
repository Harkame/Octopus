#ifndef __COMMON__TRANSFER__H__
#define __COMMON__TRANSFER__H__

#include "../../header.h"

#define MESSAGE_FILE_SIZE "File size : %d\n"
#define MESSAGE_REMAINING "Remaining : %d\n"

/*
 * Send while sended bytes < p_bytes_to_send
 */
int send_complete(int p_socket, void** p_buffer, int p_bytes_to_send);

/*
 * Recv with flag : MSG_WAITALL
 */
int receive_complete(int p_socket, void** p_buffer, int p_bytes_to_receive);

/*
 * Send p_file_to_send with p_socket
 */
int send_file(int p_socket, FILE* p_file_to_send);

/*
 * Receive p_file_to_receive with p_socket
 */
int receive_file(int p_socket, FILE* p_file_to_send);

/*
 * Try bind with port between p_port_mininimum to p_port_maximum
 */
int bind_range(int p_socket, struct sockaddr_in* p_sockaddr_in, int p_port_mininimum,
					int p_port_maximum);

#endif
