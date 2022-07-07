#!/bin/bash

GCC='gcc'
DEL='rm -f'
WRN='-Wall -Wextra'
LIBS='-lm -ldl'

$GCC -fPIC -c math_funcs.c $WRN
$GCC -shared -o libmath_funcs.so math_funcs.o
$GCC homework.c -o calc $WRN $LIBS
$DEL *.o
