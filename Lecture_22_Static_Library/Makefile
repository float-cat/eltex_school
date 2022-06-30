GCC := gcc
DEL := rm -f
WRN := -Wall -Wextra
LIBS := -lm -L. -lmath_funcs

all: libmath_funcs.a homework

libmath_funcs.a: math_funcs.*
		$(GCC) -c math_funcs.c $(WRN)
		ar rc libmath_funcs.a math_funcs.o

homework: homework.c
		$(GCC) homework.c -o calc $(WRN) $(LIBS)
		$(DEL) *.o
