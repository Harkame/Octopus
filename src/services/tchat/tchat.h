#ifndef TCHAT_H
#define TCHAT_H

#include "../../server/server.h"

void* tchat_handler(void* p_client_number);

extern int g_count_client;
extern pthread_mutex_t g_mutex;
extern LIST g_list;
extern CONNECTION g_connections[];

#endif
