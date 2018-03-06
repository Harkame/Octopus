#ifndef __SERVER__H__
#define __SERVER__H__

#include "../header.h"

#include "../services/tchat/tchat.h"
#include "../services/system/system.h"
#include "../services/transfer/transfer.h"

#include "../struct/input_line/input_line.h"
#include "../common/transfer/transfer.h"
#include "../struct/options/options.h"
#include "../struct/connection/connection.h"
#include "../struct/list/list.h"

#define DEFAULT_VALUE_PORT 10000
#define DEFAULT_NUMBER_SERVICES 10

#define PROMPT_MESSAGE "> "

#define HELP_OPTIONS_PORT "-p port (default : 6666)\n"

#define ERROR_RECV_CONNECTION_LOST "connection lost"
#define ERROR_RECV_CONNECTION_OTHER "error on recv"

#define PARAMETERS_HELP "help"
#define PARAMETERS_PORT "port"

#define MESSAGE_ASK_PRESS_ENTER "Please, press enter to close this connexion\n"
#define MESSAGE_ASK_PEER_NUMBER "Please, enter the peer number\n"

#define MESSAGE_NEW_CONNEXION "[New connexion]\n"
#define MESSAGE_AVAILABLE_UPLOAD "%d upload disponibles\n"
#define MESSAGE_CONNECTED "[Connected]\n"
#define MESSAGE_PEER_DESCRIPTION "PEER [%d] - IP [%u] - PORT [%d] - NUMBER FILES [%d]\n"
#define MESSAGE_PEER_FILE_NAME "\t  %s\n"
#define MESSAGE_RETRY "retry...\n"
#define MESSAGE_FILES_NAMES_SENDED "Files names sended\n"
#define MESSAGE_PEERS_SENDED "Peers sended\n"
#define MESSAGE_FILES_NAMES_RECEIVED "Files names received\n"
#define MESSAGE_PEERS_RECEIVED "Peer received\n"
#define MESSAGE_EXIT_PROGRAM "\n~~~ EXIT PROGRAM ~~~\n"
#define MESSAGE_NUMBER_OF_PEERS "Number of peers : %d\n"

#define ERROR_MESSAGE_SOCKET    "socket "
#define ERROR_MESSAGE_ACCEPT "accept "
#define ERROR_MESSAGE_CONNECT "connect "
#define ERROR_MESSAGE_BIND "bind "
#define ERROR_MESSAGE_LISTEN "listen "
#define ERROR_MESSAGE_CLOSE "close "
#define ERROR_MESSAGE_PTHREAD_CREATE "pthread_create "
#define ERROR_MESSAGE_PTHREAD_JOIN "pthread_join "
#define ERROR_MESSAGE_REALLOC "realloc "
#define ERROR_MESSAGE_MALLOC "malloc "
#define ERROR_MESSAGE_RECV_COMPLETE "recv_complete "
#define ERROR_MESSAGE_PTHREAD_MUTEX_INIT "pthread_mutex_init : %s\n"
#define ERROR_MESSAGE_PTHREAD_MUTEX_LOCK "pthread_mutex_lock : %s\n"
#define ERROR_MESSAGE_PTHREAD_MUTEX_UNLOCK "pthread_mutex_unlock : %s\n"
#define ERROR_MESSAGE_PTHREAD_MUTEX_DESTROY "pthread_mutex_destroy : %s\n"
#define ERROR_MESSAGE_CONNEXION_LOST "error connexion lost\n"
#define ERROR_MESSAGE_SEND_COMPLETE "send_complete "
#define ERROR_MESSAGE_FOPEN "error fopen "
#define ERROR_MESSAGE_FCLOSE "error fclose "
#define ERROR_MESSAGE_SEM_INIT "error sem_init "
#define ERROR_MESSAGE_SEM_WAIT "error sem_wait "
#define ERROR_MESSAGE_SEM_POST "error sem_post "
#define ERROR_MESSAGE_SEM_GETVALUE "error sem_getvalue "
#define ERROR_MESSAGE_SEM_DESTROY "error sem_destroy "
#define ERROR_MESSAGE_RECEIVE_FILE_TRACES "error receive_file_traces "
#define ERROR_MESSAGE_SEND_FILE_TRACES "error send_files_traces "
#define ERROR_MESSAGE_CONNECTION_LOST "error connection lost\n"
#define ERROR_MESSAGE_SIGACTION "error sigaction"

typedef struct HANDLER
{
	void* (*a_service_handler)(void*);
} HANDLER;

extern int g_port;

extern CONNECTION* g_connections;

extern WINDOW* g_window_textarea;
extern WINDOW* g_window_form;

extern pthread_mutex_t g_mutex;

extern pthread_t g_command_thread;

extern LIST* g_list;

extern HANDLER* g_services;

extern sem_t g_semaphore;

extern int g_number_services;

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

/*
 * /!\ Protected by g_mutex
 */
int close_connection(int p_number_client);

void print_message(char* p_message_to_print);

int main(int p_count_arguments, char** p_arguments_values);

#endif
