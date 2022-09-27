#ifndef _WINDOWS_C_
#define _WINDOWS_C_

#include "windows.h"

WINDOWS createWindow(int number)
{
    struct winsize size;
    ssize_t len;
    WINDOWS windows;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    if(number == 0)
    {
        windows.wnd = newwin(size.ws_row - 3, size.ws_col - 30, 0, 0);
        box(windows.wnd, '|', '-');
        windows.subwnd = derwin(windows.wnd, size.ws_row-5, size.ws_col-32, 1, 1);
        wrefresh(windows.wnd);
    }
    else if(number == 1)
    {
        windows.wnd = newwin(size.ws_row - 3, 30, 0, size.ws_col - 30);
        box(windows.wnd, '|', '-');
        windows.subwnd = derwin(windows.wnd, size.ws_row-5, 28, 1, 1);
        wrefresh(windows.wnd);
    }
    else if(number == 2)
    {
        windows.wnd = newwin(3, size.ws_col, size.ws_row - 3, 0);
        box(windows.wnd, '|', '-');
        windows.subwnd = derwin(windows.wnd, 1, size.ws_col - 2, 1, 1);
        wrefresh(windows.wnd);
    }
    return windows;
}

WINDOWS resizewnds(WINDOWS *wnds, int number)
{
    struct winsize size;
    delwin(wnds->subwnd);
    delwin(wnds->wnd);
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    if(number == 0)
    {
        wnds->wnd = newwin(size.ws_row - 3, size.ws_col - 30, 0, 0);
        box(wnds->wnd, '|', '-');
        wnds->subwnd = derwin(wnds->wnd, size.ws_row-5, size.ws_col-32, 1, 1);
        wrefresh(wnds->wnd);
    }
    else if(number == 1)
    {
        wnds->wnd = newwin(size.ws_row - 3, 30, 0, size.ws_col - 30);
        box(wnds->wnd, '|', '-');
        wnds->subwnd = derwin(wnds->wnd, size.ws_row-5, 28, 1, 1);
        wrefresh(wnds->wnd);
    }
    else if(number == 2)
    {
        wnds->wnd = newwin(3, size.ws_col, size.ws_row - 3, 0);
        box(wnds->wnd, '|', '-');
        wnds->subwnd = derwin(wnds->wnd, 1, size.ws_col - 2, 1, 1);
        wrefresh(wnds->wnd);
    }
    return *wnds;
}

void sig_winch(int signo)
{
    struct winsize size;
    signo = signo;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    resizewnds(&wnds[0], 0);
    resizewnds(&wnds[1], 1);
    resizewnds(&wnds[2], 2);
    nodelay(stdscr, 1);
    while (wgetch(stdscr) != ERR);
    nodelay(stdscr, 0);
}

#endif /* _WINDOWS_C_ */
