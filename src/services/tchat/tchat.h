#ifndef __TCHAT__H__
#define __TCHAT__H__

#include "../../header.h"

#include "../../struct/list/list.h"
#include "../../server/server.h"

extern LIST* g_tchat_socket;

void* tchat_handler(void* p_client_number);

#endif
