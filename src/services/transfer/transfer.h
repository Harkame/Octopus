#ifndef TRANSFER_H
#define TRANSFER_H

#include "../../server/server.h"

void* transfer_handler(void* p_client_number);

extern int g_count_client;
extern pthread_mutex_t g_mutex;
extern LIST g_list;
extern CONNECTION g_connections[];

#endif
