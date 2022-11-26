GCC := gcc
DEL := rm -f
WRN := -Wall -Wextra
LIBS := 

all: server client

server: echo_server.c
		$(GCC) echo_server.c -o server $(WRN) $(LIBS)

client: raw_socket_client.c
		$(GCC) raw_socket_client.c -o client $(WRN) $(LIBS)
