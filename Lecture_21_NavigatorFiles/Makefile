BIN := nf
SOURCES := *.c
HEADERS := *.h
OBJS := *.o
GCC := gcc
DEL := rm -f
C90 := -std=gnu90 -pedantic
WRN := -Wall -Wextra
LIBS := -lncurses

$(BIN): $(SOURCES) $(HEADERS)
		$(GCC) -c $(SOURCES) $(C90) $(WRN)
		$(GCC) $(OBJS) -o $(BIN) $(C90) $(WRN) $(LIBS)
		$(DEL) $(OBJS)
