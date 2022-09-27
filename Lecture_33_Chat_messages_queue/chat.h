#ifndef _CHAT_H_
#define _CHAT_H_

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

#define MAX_CHAT_MESSAGE 255

void process(void);
void init(void);

#endif /* _CHAT_H_ */
