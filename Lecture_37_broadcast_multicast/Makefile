GCC := gcc
DEL := rm -f
WRN := -Wall -Wextra
LIBS := 

broadcast: serverb clientb

serverb: broadcast_server.c
		$(GCC) broadcast_server.c -o server $(WRN) $(LIBS)

clientb: broadcast_client.c
		$(GCC) broadcast_client.c -o client $(WRN) $(LIBS)
		
multicast: serverm clientm

serverm: multicast_server.c
		$(GCC) multicast_server.c -o server $(WRN) $(LIBS)

clientm: multicast_client.c
		$(GCC) multicast_client.c -o client $(WRN) $(LIBS)
