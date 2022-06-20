#ifndef _WINDOWS_H_
#define _WINDOWS_H_

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

#include "fileList.h"

struct windows
{
    WINDOW * wnd;
    WINDOW * subwnd;
    char path[PATH_MAX+1];
    struct fileList list;
    int position;
};

typedef struct windows WINDOWS;

extern WINDOWS wnds[2];

WINDOWS createWindow(int count, int number);

WINDOWS resizewnds(WINDOWS *wnds, int count, int number);

void printFileList(WINDOWS *wnds);

void sig_winch(int signo);

#endif /* _WINDOWS_H_ */
