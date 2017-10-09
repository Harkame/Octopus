#ifndef FILE_TRANSFER_H
#define FILE_TRANSFER_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>

/*
 * Send file (p_file_to_send) by ready socket (p_socket)
 *
 * PROTOCOL :
 * 1. Send file size
 * 2. Send file name
 * 3. Send file content
 *
 * MODIFICATION :
 * fwrite on p_file_to_send
 */
void send_file(const int p_socket, FILE* p_file_to_send);

/*
 * Send file (p_file_to_send) by ready socket (p_socket)
 *
 * PROTOCOL :
 * 1. Send file size
 * 2. Send file content
 *
 * MODIFICATION :
 * fwrite on p_file_to_send
 */
void send_file_unamed(const int p_socket, FILE* p_file_to_send);

/*
 * Receive file in directory (p_directory) by ready socket (p_socket)
 *
 * PROTOCOL :
 * 1. Read file size
 * 2. Read file name
 * 3. Read file content
 */
void receive_file(const int p_socket, FILE* p_file_to_receive);

/*
 * Receive file in directory (p_directory) by ready socket (p_socket)
 *
 * PROTOCOL :
 * 1. Read file size
 * 2. Read file content
 */
void receive_file_unamed(const int p_socket, FILE* p_file_to_receive);

/*
 * TODO
 *
 */
void send_directory(const int p_socket, const char* p_directory_path_to_send);

#endif
