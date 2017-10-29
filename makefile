MKDIR                              = mkdir -p
GCC                                  = gcc -ansi -Wpedantic -pedantic -pedantic-errors -W -Wall -Wextra -Werror -Wfatal-errors  -std=gnu99 -O3
OPTIONS                         = -pthread -D_GNU_SOURCE -lncurses
LIBRARY_OPTIONS        = -shared -fPIC
LIBRARY_STRUCTURES = ./bin/struct/list/list.so ./bin/struct/input_line/input_line.so ./bin/struct/connection/connection.so ./bin/struct/options/options.so
LIBRARY_SERVICES       = ./bin/services/tchat/tchat.so ./bin/services/system/system.so ./bin/services/transfer/transfer.so

all: directory file clean

directory:
	${MKDIR} ./bin/server;
	${MKDIR} ./bin/client;
	${MKDIR} ./bin/transfer;
	${MKDIR} ./bin/struct;
	${MKDIR} ./bin/struct/list;
	${MKDIR} ./bin/struct/input_line;
	${MKDIR} ./bin/struct/connection;
	${MKDIR} ./bin/struct/options;
	${MKDIR} ./bin/services;
	${MKDIR} ./bin/services/system;
	${MKDIR} ./bin/services/tchat;
	${MKDIR} ./bin/services/transfer;

file: library services server client

services:
	${GCC} ./src/services/tchat/tchat.c ${OPTIONS} ${LIBRARY_OPTIONS} -o ./bin/services/tchat/tchat.so;
	${GCC} ./src/services/system/system.c ${OPTIONS} ${LIBRARY_OPTIONS} -o ./bin/services/system/system.so;
	${GCC} ./src/services/transfer/transfer.c ${OPTIONS} ${LIBRARY_OPTIONS} ./bin/transfer/file_transfer.so -o ./bin/services/transfer/transfer.so;

server:
	${GCC} ./src/server/server.c ${OPTIONS} ${LIBRARY_STRUCTURES} ./bin/transfer/file_transfer.so ${LIBRARY_SERVICES} -o ./bin/server/server.o ;

client:
	${GCC} ./src/client/client.c ${OPTIONS} ./bin/transfer/file_transfer.so ${LIBRARY_STRUCTURES} -o ./bin/client/client.o;

library: file_transfer struct

file_transfer:
	${GCC} ./src/transfer/file_transfer.c ${LIBRARY_OPTIONS} -o ./bin/transfer/file_transfer.so -Wno-unused-result;

struct:
	${GCC} ./src/struct/list//list.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list/list.so;
	${GCC} ./src/struct/input_line/input_line.c ${LIBRARY_OPTIONS} ${OPTIONS} -o ./bin/struct/input_line/input_line.so;
	${GCC} ./src/struct/connection/connection.c ${LIBRARY_OPTIONS}  -o ./bin/struct/connection/connection.so;
	${GCC} ./src/struct/options/options.c ${LIBRARY_OPTIONS}  -o ./bin/struct/options/options.so;

test:
	${GCC} ./test/struct/list/list.c ./bin/struct/list/list.so -o ./test/struct/list/list.o;

clean:
	rm -rf ./src/*/*.gch;
	rm -rf ./test/*/*.gch;
