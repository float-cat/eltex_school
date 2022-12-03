BIN1 := server
SOURCES1 := server.c
HEADERS1 := server.h
BIN2 := client
SOURCES2 := main.c chat.c client.c windows.c
HEADERS2 := chat.h client.h windows.h
OBJS2 := *.o
GCC := gcc
DEL := rm -f
C90 := -std=gnu90 -pedantic -fno-stack-protector
WRN := -Wall -Wextra
LIBS := -lncurses -lpthread

all: $(BIN1) $(BIN2)

$(BIN1): $(SOURCES1) $(HEADERS1)
		$(GCC) $(SOURCES1) -o $(BIN1) $(C90) $(WRN) $(LIBS)
		
$(BIN2): $(SOURCES2) $(HEADERS2)
		$(GCC) -c $(SOURCES2) $(C90) $(WRN)
		$(GCC) $(OBJS2) -o $(BIN2) $(C90) $(WRN) $(LIBS)
		$(DEL) $(OBJS2)
