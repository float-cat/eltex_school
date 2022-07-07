GCC := gcc
DEL := rm -f
WRN := -Wall -Wextra
LIBS := -lm -ldl

all: libmath_funcs.so homework

libmath_funcs.so: math_funcs.*
		$(GCC) -fPIC -c math_funcs.c $(WRN)
		$(GCC) -shared -o libmath_funcs.so math_funcs.o

homework: homework.c
		$(GCC) homework.c -o calc $(WRN) $(LIBS)
		$(DEL) *.o
