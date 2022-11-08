#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

struct windows
{
    WINDOW * wnd;
    WINDOW * subwnd;
};

typedef struct windows WINDOWS;

extern WINDOWS wnds[3];

WINDOWS createWindow(int number);

WINDOWS resizewnds(WINDOWS *wnds, int number);

void sig_winch(int signo);

#endif /* _WINDOWS_H_ */
