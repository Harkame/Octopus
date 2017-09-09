MKDIR      = mkdir -p
GCC           = gcc -Wall -ansi -std=gnu99
OPTIONS  = -pthread -D_GNU_SOURCE -lncurses
LIBRARY   = -shared -fPIC
SHARED    = ./bin/transfer/file_transfer.so ./bin/struct/list_int.so ./bin/struct/list_string.so ./bin/struct/input_line.so
SERVICE    = ./bin/services/tchat.so

all: directory file clean

directory:
	${MKDIR} ./bin/server;
	${MKDIR} ./bin/client;
	${MKDIR} ./bin/transfer;
	${MKDIR} ./bin/struct;
	${MKDIR} ./bin/services;

file: shared services server client test

services:
	${GCC} ./src/services/tchat.c ${OPTIONS} ${LIBRARY} -o ./bin/services/tchat.so;

server:
	${GCC} ./src/server/server.c ${OPTIONS} ${SHARED} ${SERVICE} -o ./bin/server/server.o ;

client:
	${GCC} ./src/client/client.c ${OPTIONS}  ${SHARED} -o ./bin/client/client.o;

shared: file_transfer struct

file_transfer:
	${GCC} ./src/transfer/file_transfer.c -shared -fPIC -o ./bin/transfer/file_transfer.so;

struct: list input_line

list: list_int list_string

input_line:
	${GCC} ./src/struct/input_line.c ${LIBRARY} ${OPTIONS} -o ./bin/struct/input_line.so;

list_int:
	${GCC} ./src/struct/list_int.c ${LIBRARY}  -o ./bin/struct/list_int.so;

list_string:
	${GCC} ./src/struct/list_string.c ${LIBRARY}  -o ./bin/struct/list_string.so;

test:
	${GCC} ./test/struct/test_list_string.c ${SHARED} -o ./test/struct/test_list_string.o;

clean:
		rm -rf ./src/*.gch;
		rm -rf ./test/*.gch;
