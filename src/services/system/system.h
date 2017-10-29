#ifndef SYSTEM_H
#define SYSTEM_H

#include "../../server/server.h"

#define ERROR_SYSTEM "Error system : %s \n"

void* system_handler(void* p_client_number);

extern int g_count_client;
extern pthread_mutex_t g_mutex;
extern LIST g_list;
extern CONNECTION g_connections[];

#endif
