MKDIR           = mkdir -p
GCC             = gcc -ansi -Wpedantic -pedantic -pedantic-errors -W -Wall -Wextra -Werror -Wfatal-errors  -std=gnu99 -O3
OPTIONS         = -pthread -D_GNU_SOURCE -lncurses
LIBRARY_OPTIONS = -shared -fPIC
LIBRARY_FILES   = ${LIBRARY_FILES_STRUCTURES}
LIBRARY_FILES_STRUCTURES = ./bin/struct/list.so ./bin/struct/list_int.so ./bin/struct/list_string.so ./bin/struct/input_line.so ./bin/struct/connection.so ./bin/struct/options.so
SERVICES_FILES  = ./bin/services/tchat/tchat.so ./bin/services/system/system.so ./bin/services/transfer/transfer.so

all: directory file clean

directory:
	${MKDIR} ./bin/server;
	${MKDIR} ./bin/client;
	${MKDIR} ./bin/transfer;
	${MKDIR} ./bin/struct;
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
	${GCC} ./src/server/server.c ${OPTIONS} ${LIBRARY_FILES} ./bin/transfer/file_transfer.so ${SERVICES_FILES} -o ./bin/server/server.o ;

client:
	${GCC} ./src/client/client.c ${OPTIONS} ./bin/transfer/file_transfer.so ${LIBRARY_FILES} -o ./bin/client/client.o;

library: file_transfer struct

file_transfer:
	${GCC} ./src/transfer/file_transfer.c ${LIBRARY_OPTIONS} -o ./bin/transfer/file_transfer.so -Wno-unused-result;

# BEGIN STRUCT
struct: list input_line connection options
# BEGIN LIST
list: list_generic list_int list_string

list_generic:
	${GCC} ./src/struct/list.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list.so;

list_int:
	${GCC} ./src/struct/list_int.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list_int.so;

list_string:
	${GCC} ./src/struct/list_string.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list_string.so;
# END LIST

input_line:
	${GCC} ./src/struct/input_line.c ${LIBRARY_OPTIONS} ${OPTIONS} -o ./bin/struct/input_line.so;

connection:
	${GCC} ./src/struct/connection.c ${LIBRARY_OPTIONS}  -o ./bin/struct/connection.so;

options:
	${GCC} ./src/struct/options.c ${LIBRARY_OPTIONS}  -o ./bin/struct/options.so;

# END STRUCT

test:
	${GCC} ./test/struct/test_list_string.c ${LIBRARY_FILES} -o ./test/struct/test_list_string.o;

clean:
	rm -rf ./src/*/*.gch;
	rm -rf ./test/*/*.gch;
