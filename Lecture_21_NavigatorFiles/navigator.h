#ifndef _NAVIGATOR_H_
#define _NAVIGATOR_H_

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

#include "windows.h"

void process(void);
void init(void);

#endif /* _NAVIGATOR_H_ */
