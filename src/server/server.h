#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <features.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <features.h>
#include <curses.h>
#include <errno.h>
#include <error.h>

#include "../struct/list/list.h"
#include "../struct/input_line/input_line.h"
#include "../struct/connection/connection.h"
#include "../struct/options/options.h"

#include "../services/tchat/tchat.h"
#include "../services/system/system.h"
#include "../services/transfer/transfer.h"

#include "../transfer/file_transfer.h"

#define DEFAULT_VALUE_PORT 6666

#define PROMPT_MESSAGE "> "

#define MESSAGE_NEW_CONNEXION "New connection (%d)\n"

#define HELP_OPTIONS_PORT "-p port (default : 6666)\n"

#define ERROR_RECV_CONNECTION_LOST "connection lost"
#define ERROR_RECV_CONNECTION_OTHER "error on recv"

#define PARAMETERS_HELP "help"
#define PARAMETERS_PORT "port"

#define NO_ERROR 0

typedef struct SERVICE
{
     char* a_service_name;

     void* (*a_service_handler)(void*);
} SERVICE;

extern int g_port;

extern CONNECTION g_connections[];

extern WINDOW* g_window_textarea;
extern WINDOW* g_window_form;

extern pthread_mutex_t g_mutex;

extern pthread_t g_command_thread;

extern pthread_t g_threads [];

extern LIST g_list;

extern LIST g_list_int;

extern LIST g_list_options;

extern SERVICE* g_services[10];

extern int g_count_client;

/*
* (Begin) initializations
*/
void initialize_windows();

void initialize_services();

void initialize_connections();

void initialize_options(struct OPTIONS*);

void initialize_server_socket(int p_server_socket_to_initialize);

/*
* /!\ Protected by g_mutex
*
* Used for resize windows
*
*/
void re_initialize_windows();

void close_windows();

void close_sockets();

void parse_command(struct OPTIONS*, char*);

/*
* (End) initializations
*/

/*
* /!\ Protected by g_mutex
*/
void refresh_windows();

/*
* /!\ Protected by g_mutex
*/
void add_message(char* p_message);

/*
* /!\ Protected by g_mutex
*/
void adjust_list();

/*
* /!\ Protected by g_mutex
*/
void print_textarea();

void read_command_parameters();

void help();
void exit_program();

void* command_handler();

void print_grapical_error();

/*
* /!\ Protected by g_mutex
*/
int close_connection(int p_number_client);

int main(int p_count_arguments, char** p_arguments_values);

#endif
