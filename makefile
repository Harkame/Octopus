MKDIR                       = mkdir -p
GCC                           = gcc -Wall -ansi -std=gnu99
OPTIONS                  = -pthread -D_GNU_SOURCE -lncurses
LIBRARY_OPTIONS = -shared -fPIC
LIBRARY_FILES        = ./bin/transfer/file_transfer.so ./bin/struct/list_int.so ./bin/struct/list_string.so ./bin/struct/input_line.so ./bin/struct/connection.so
SERVICES_FILES        = ./bin/services/tchat.so

all: directory file clean

directory:
	${MKDIR} ./bin/server;
	${MKDIR} ./bin/client;
	${MKDIR} ./bin/transfer;
	${MKDIR} ./bin/struct;
	${MKDIR} ./bin/services;

file: library services server client test

services:
	${GCC} ./src/services/tchat.c ${OPTIONS} ${LIBRARY_OPTIONS} -o ./bin/services/tchat.so;

server:
	${GCC} ./src/server/server.c ${OPTIONS} ${LIBRARY_FILES} ${SERVICES_FILES} -o ./bin/server/server.o ;

client:
	${GCC} ./src/client/client.c ${OPTIONS}  ${LIBRARY_FILES} -o ./bin/client/client.o;

library: file_transfer struct

file_transfer:
	${GCC} ./src/transfer/file_transfer.c ${LIBRARY_OPTIONS} -o ./bin/transfer/file_transfer.so;

# BEGIN STRUCT
struct: list input_line connection
# BEGIN LIST
list: list_int list_string

list_int:
	${GCC} ./src/struct/list_int.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list_int.so;

list_string:
	${GCC} ./src/struct/list_string.c ${LIBRARY_OPTIONS}  -o ./bin/struct/list_string.so;
# END LIST

input_line:
	${GCC} ./src/struct/input_line.c ${LIBRARY_OPTIONS} ${OPTIONS} -o ./bin/struct/input_line.so;

connection:
	${GCC} ./src/struct/connection.c ${LIBRARY_OPTIONS}  -o ./bin/struct/connection.so;
# END STRUCT

test:
	${GCC} ./test/struct/test_list_string.c ${LIBRARY_FILES} -o ./test/struct/test_list_string.o;

clean:
	rm -rf ./src/*/*.gch;
	rm -rf ./test/*/*.gch;
