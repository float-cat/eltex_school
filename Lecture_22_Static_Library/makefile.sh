#!/bin/bash

GCC='gcc'
DEL='rm -f'
WRN='-Wall -Wextra'
LIBS='-lm -L. -lmath_funcs'

$GCC -c math_funcs.c $WRN
ar rc libmath_funcs.a math_funcs.o
$GCC homework.c -o calc $WRN $LIBS
$DEL *.o
