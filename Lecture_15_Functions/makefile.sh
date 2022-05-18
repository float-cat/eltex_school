#!/bin/bash

GCC='gcc'
DEL='rm -f'
WRN='-Wall -Wextra'
LIBS='-lm'

$GCC -c *.c $WRN
$GCC *.o -o calc $WRN $LIBS
$DEL *.o
