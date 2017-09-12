#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdlib.h>

typedef struct CONNECTION
{
     struct socket* a_socket;

     int a_state;

} CONNECTION;

struct CONNECTION* create_connection();

#endif
