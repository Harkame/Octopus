#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
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
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ncurses.h>
#include <ctype.h>

#include "../transfer/file_transfer.h"
#include "../struct/list_string.h"
#include "../struct/list_int.h"
#include "../struct/input_line.h"

#define DEFAULT_PORT            6666
#define DEFAULT_IP                  "127.0.0.1"
#define DEFAULT_DIRECTORY ".test"

#define ERROR_MESSAGE_SOCKET    "socket"
#define ERROR_MESSAGE_CONNECT "connect"
#define ERROR_MESSAGE_FOPEN      "Error : fopen\n"

#define MESSAGE_REMAINING                "%d remaining\n"
#define MESSAGE_FILE_DOWNLOADED "%s downloaded\n"

#define PROMPT_MESSAGE "> "

#define HELP_OPTION_IP                 "-i ip_address\n"
#define HELP_OPTION_DIRECTORY "-d directory\n"
#define HELP_OPTION_PORT             "-p port\n"

#define EXIT_MESSAGE "exit"

int g_socket;

pthread_t g_read_thread;
pthread_t g_write_thread;

int  g_port = DEFAULT_PORT;
char g_ip[] = {DEFAULT_IP};
char g_directory[BUFSIZ] = {DEFAULT_DIRECTORY};

char g_file_name[BUFSIZ];

FILE* g_downloaded_file;

WINDOW* g_window_textarea;
WINDOW* g_window_form;

struct LIST_STRING* g_list_string;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void initialize_windows();

/*
* /!\ Protected by g_mutex
*
* Used for resize windows
*
*/
void re_initialize_windows();

void refresh_windows();

void exit_program();

void print_textarea();

void adjust_list_string();

int main();

#endif
