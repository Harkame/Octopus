#include "./connection.h"

struct CONNECTION* create_connection()
{
     struct CONNECTION* r_connection = malloc(sizeof(struct CONNECTION));

     r_connection->a_state = 0;

     return r_connection;
}
