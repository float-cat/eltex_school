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
#include "windows.h"

WINDOWS wnds[2];

int main(void)
{
    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0);
    refresh();
    wnds[0] = createWindow(2, 0);
    wnds[1] = createWindow(2, 1);
    printFileList(&(wnds[0]));
    printFileList(&(wnds[1]));
    delwin(wnds[0].subwnd);
    delwin(wnds[0].wnd);
    delwin(wnds[1].subwnd);
    delwin(wnds[1].wnd);
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}
