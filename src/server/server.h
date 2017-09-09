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


#include "../transfer/file_transfer.h"
#include "../struct/list_int.h"
#include "../struct/list_string.h"
#include "../struct/input_line.h"

#include "../services/tchat.h"

#define DEFAULT_VALUE_IP "127.0.0.1"
#define DEFAULT_VALUE_PORT 6666

#define PROMPT_MESSAGE "> "

#define MESSAGE_NEW_CONNEXION "New connection (%d)\n"

typedef struct SERVICE
{
     char* a_service_name;

     void (*a_service_function)(int*);
} SERVICE;

typedef struct OPTION
{
     char* a_option_title;

     char* a_option_value;
} OPTION;

int g_port = DEFAULT_VALUE_PORT;

char g_services_names[10];
void* g_services_handler[10];

WINDOW* g_window_textarea;
WINDOW* g_window_form;

struct LIST_STRING* g_list_string;

pthread_mutex_t g_mutex;

pthread_t g_command_thread;;

pthread_t g_threads [10];

struct LIST_INT* g_list;

int g_sockets[10];

struct SERVICE** g_services;

int g_count_client = 0;

void initialize_windows();

void initialize_services();

/*
* Protected by g_mutex
*/
void refresh_windows();

/*
* Protected by g_mutex
*/
void adjust_list_string();

/*
* Protected by g_mutex
*/
void print_textarea();

void read_command_parameters();

void help();

void exit_program();

#endif
