GCC := gcc
DEL := rm -f
WRN := -Wall -Wextra
LIBS := -lpthread

all: clients server1 server2 server3

clients: clients.c
		$(GCC) clients.c -o clients $(WRN) $(LIBS)

server1: server1.c
		$(GCC) server1.c -o server1 $(WRN) $(LIBS)

server2: server2.c
		$(GCC) server2.c -o server2 $(WRN) $(LIBS)

server3: server3.c
		$(GCC) server3.c -o server3 $(WRN) $(LIBS)
