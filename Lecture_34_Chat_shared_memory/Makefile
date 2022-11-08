BIN := client
SOURCES := main.c chat.c client.c windows.c
HEADERS := chat.h client.h windows.h
OBJS := *.o
GCC := gcc
DEL := rm -f
C90 := -std=gnu90 -pedantic
WRN := -Wall -Wextra
LIBS := -lncurses -lpthread -lrt

all: $(BIN)
		
$(BIN): $(SOURCES) $(HEADERS)
		$(GCC) -c $(SOURCES) $(C90) $(WRN)
		$(GCC) $(OBJS) -o $(BIN) $(C90) $(WRN) $(LIBS) -g
		$(DEL) $(OBJS)
