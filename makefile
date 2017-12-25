MKDIR                              = mkdir -p
GCC                                  = gcc -ansi -Wpedantic -pedantic -pedantic-errors -W -Wall -Wextra -Werror -Wfatal-errors  -std=gnu99 -O3
OPTIONS                         = -pthread -D_GNU_SOURCE -lncurses
LIBRARY_OPTIONS        = -c
LIBRARY_STRUCTURES = ./bin/struct/list/list.o ./bin/struct/input_line/input_line.o ./bin/struct/connection/connection.o ./bin/struct/options/options.o
LIBRARY_SERVICES       = ./bin/services/tchat/tchat.o ./bin/services/system/system.o ./bin/services/common/transfer/common/transfer/transfer.o

all: directory file clean

directory:
	${MKDIR} ./bin/server;
	${MKDIR} ./bin/client;
	${MKDIR} ./bin/common/transfer;
	${MKDIR} ./bin/struct;
	${MKDIR} ./bin/struct/list;
	${MKDIR} ./bin/struct/input_line;
	${MKDIR} ./bin/struct/connection;
	${MKDIR} ./bin/struct/options;
	${MKDIR} ./bin/services;
	${MKDIR} ./bin/services/system;
	${MKDIR} ./bin/services/tchat;
	${MKDIR} ./bin/
	${MKDIR} ./bin/services/common/transfer;

file: clean library services server client test clean

services:
	${GCC} ./src/services/tchat/tchat.c ${OPTIONS} ${LIBRARY_OPTIONS} -o ./bin/services/tchat/tchat.o;
	${GCC} ./src/services/system/system.c ${OPTIONS} ${LIBRARY_OPTIONS} -o ./bin/services/system/system.o;
	${GCC} ./src/services/transfer/transfer.c ${OPTIONS} ${LIBRARY_OPTIONS} ./bin/common/transfer/transfer.o -o ./bin/services/transfer/transfer.o;

server:
	${GCC} ./src/server/server.c ${OPTIONS} ${LIBRARY_STRUCTURES} ./bin/common/transfer/common/transfer/transfer.o ${LIBRARY_SERVICES} -o ./bin/server/server.out ;

client:
	${GCC} ./src/client/client.c ${OPTIONS} ./bin/common/transfer/common/transfer/transfer.o ${LIBRARY_STRUCTURES} -o ./bin/client/client.out;

library: file_common/transfer struct

file_common/transfer:
	${GCC} ./src/common/transfer/transfer.c ${LIBRARY_OPTIONS} -o ./bin/common/transfer/transfer.o -Wno-unused-result;

struct:
	gcc ./src/struct/list/list.c ${LIBRARY_OPTIONS} ${OPTIONS} -o ./bin/struct/list/list.o;
	${GCC} ./src/struct/input_line/input_line.c ${LIBRARY_OPTIONS} ${OPTIONS} -o ./bin/struct/input_line/input_line.o;
	${GCC} ./src/struct/connection/connection.c ${LIBRARY_OPTIONS}  -o ./bin/struct/connection/connection.o;
	${GCC} ./src/struct/options/options.c ${LIBRARY_OPTIONS}  -o ./bin/struct/options/options.o;

test:
	${GCC} ./test/struct/list/test_list.c ./bin/struct/list/list.o -o ./test/struct/list/test_list.out;

clean:
	find . -name "*.gch" -type f -delete
