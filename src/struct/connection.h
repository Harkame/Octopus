#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdlib.h>

typedef struct CONNECTION
{
     int a_socket;

     int a_state;

} CONNECTION;

struct CONNECTION* create_connection();

#endif
