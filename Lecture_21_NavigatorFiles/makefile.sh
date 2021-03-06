#!/bin/bash

GCC='gcc'
DEL='rm -f'
C90='-std=gnu90 -pedantic'
WRN='-Wall -Wextra'
LIBS='-lncurses'

$GCC -c *.c $C90 $WRN
$GCC *.o -o nf $C90 $WRN $LIBS
$DEL *.o
