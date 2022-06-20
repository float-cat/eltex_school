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
    char ch;
    int wndidx;
    initscr();
    noecho();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0);
    refresh();
    wndidx = 0;
    wnds[0] = createWindow(2, 0);
    wnds[1] = createWindow(2, 1);
    printFileList(&(wnds[0]));
    printFileList(&(wnds[1]));
    while((ch = getch()) != 113)
    {
        if(ch == 115)
        {
            wmove(wnds[wndidx].subwnd, 0, 0);
            wnds[wndidx].position++;
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 119)
        {
            wmove(wnds[wndidx].subwnd, 0, 0);
            wnds[wndidx].position--;
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 9)
        {
            wndidx = (wndidx + 1) % 2;
        }
    }
    delwin(wnds[0].subwnd);
    delwin(wnds[0].wnd);
    delwin(wnds[1].subwnd);
    delwin(wnds[1].wnd);
    endwin();
    printf("[%d]\n", ch);
    exit(EXIT_SUCCESS);
}
