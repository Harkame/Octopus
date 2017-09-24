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

#include "../struct/list.h"
#include "../struct/list_int.h"
#include "../struct/list_string.h"
#include "../struct/input_line.h"
#include "../struct/connection.h"
#include "../struct/options.h"

#include "../services/tchat.h"

#include "../transfer/file_transfer.h"


#define DEFAULT_VALUE_PORT 6666

#define PROMPT_MESSAGE "> "

#define MESSAGE_NEW_CONNEXION "New connection (%d)\n"

#define HELP_OPTIONS_PORT "-p port (default : 6666)\n"

#define PARAMETERS_HELP "help"
#define PARAMETERS_PORT "port"

typedef struct SERVICE
{
     char* a_service_name;

     void* (*a_service_handler)(void*);
} SERVICE;

int g_port = DEFAULT_VALUE_PORT;

struct CONNECTION* g_connections[10];

WINDOW* g_window_textarea;
WINDOW* g_window_form;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t g_command_thread;;

pthread_t g_threads [10];

struct LIST_STRING g_list_string;

struct LIST_INT g_list;

struct LIST g_list_options;

struct SERVICE* g_services[10];

int g_count_client = 0;

/*
* (Begin) initializations
*/
void initialize_windows();

void initialize_services();

void initialize_connections();

void initialize_server_socket(int p_server_socket_to_initialize);

/*
* /!\ Protected by g_mutex
*
* Used for resize windows
*
*/
void re_initialize_windows();

void initialize_options(struct OPTIONS*);

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
void adjust_list_string();

/*
* /!\ Protected by g_mutex
*/
void print_textarea();

void read_command_parameters();

void help();
void exit_program();

void* command_handler();

int main(int p_count_arguments, char** p_arguments_values);

#endif
