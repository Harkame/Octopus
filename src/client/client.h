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

void init_screen();

void exit_program();

void print_textarea();

#endif
