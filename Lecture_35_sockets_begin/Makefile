GCC := gcc
DEL := rm -f
C90 := -std=gnu90 -pedantic
WRN := -Wall -Wextra
LIBS :=

all: server1 client1 server2 client2 server_udp client_udp server_tcp client_tcp

server1: server1.c
		$(GCC) server1.c -o server1 $(C90) $(WRN) $(LIBS)

client1: client1.c
		$(GCC) client1.c -o client1 $(C90) $(WRN) $(LIBS)

server2: server2.c
		$(GCC) server2.c -o server2 $(C90) $(WRN) $(LIBS)

client2: client2.c
		$(GCC) client2.c -o client2 $(C90) $(WRN) $(LIBS)

server_udp: server_udp.c
		$(GCC) server_udp.c -o server_udp $(C90) $(WRN) $(LIBS)

client_udp: client_udp.c
		$(GCC) client_udp.c -o client_udp $(C90) $(WRN) $(LIBS)

server_tcp: server_tcp.c
		$(GCC) server_tcp.c -o server_tcp $(C90) $(WRN) $(LIBS)

client_tcp: client_tcp.c
		$(GCC) client_tcp.c -o client_tcp $(C90) $(WRN) $(LIBS)
