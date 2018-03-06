#ifndef __CLIENT__H__
#define __CLIENT__H__

#include "../header.h"

#include "../struct/list/list.h"
#include "../common/transfer/transfer.h"
#include "../struct/input_line/input_line.h"
#include "../struct/options/options.h"

#define DEFAULT_PORT      10000
#define DEFAULT_IP        "127.0.0.1"
#define DEFAULT_DIRECTORY ".test"

#define ERROR_MESSAGE_SOCKET  "socket"
#define ERROR_MESSAGE_CONNECT "connect"
#define ERROR_MESSAGE_FOPEN   "Error : fopen\n"

#define MESSAGE_FILE_DOWNLOADED "%s downloaded\n"

#define PROMPT_MESSAGE "> "

#define HELP_OPTION_IP        "-i ip_address\n"
#define HELP_OPTION_DIRECTORY "-d directory\n"
#define HELP_OPTION_PORT      "-p port\n"

#define PARAMETERS_HELP "help"
#define PARAMETERS_PORT "port"
#define PARAMETERS_IP   "ip"

#define EXIT_MESSAGE "exit"

int g_socket;

pthread_t g_read_thread;
pthread_t g_write_thread;

int g_port  = DEFAULT_PORT;
char g_ip[] = {DEFAULT_IP};
char g_directory[BUFSIZ] = {DEFAULT_DIRECTORY};

char g_file_name[BUFSIZ];

FILE* g_downloaded_file;

WINDOW* g_window_textarea;
WINDOW* g_window_form;

extern LIST* g_list;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void initialize_windows();

/*
 * /!\ Protected by g_mutex
 *
 * Used for resize windows
 *
 */
void re_initialize_windows();

void close_windows();

void initialize_options(struct OPTIONS*);

void refresh_windows();

void exit_program();

void print_textarea();

void adjust_list();

int main(int, char**);

#endif
