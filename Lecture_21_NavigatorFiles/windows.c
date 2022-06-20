#ifndef _WINDOWS_C_
#define _WINDOWS_C_

#include "windows.h"

WINDOWS createWindow(int count, int number)
{
    struct winsize size;
    ssize_t len;
    WINDOWS windows;
    char *p;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    windows.wnd = newwin(size.ws_row, size.ws_col/count, 0, size.ws_col/count * number);
    box(windows.wnd, '|', '-');
    windows.subwnd = derwin(windows.wnd, size.ws_row-2, size.ws_col/count-2, 1, 1);
    wrefresh(windows.wnd);
    len = readlink("/proc/self/exe", windows.path, PATH_MAX);
    windows.path[len] = 0;
    p = strrchr(windows.path, '/');
    if(p) *(p + 1) = 0;
    else windows.path[0] = 0;
    windows.list.root = NULL;
    windows.list.prev = NULL;
    windows.list.count = 0;
    getFileList(&(windows.list), windows.path);
    return windows;
}

WINDOWS resizewnds(WINDOWS *wnds, int count, int number)
{
    struct winsize size;
    delwin(wnds->subwnd);
    delwin(wnds->wnd);
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    wnds->wnd = newwin(size.ws_row, size.ws_col/count, 0, size.ws_col/count * number);
    box(wnds->wnd, '|', '-');
    wnds->subwnd = derwin(wnds->wnd, size.ws_row-2, size.ws_col/count-2, 1, 1);
    wrefresh(wnds->subwnd);
    printFileList(wnds);
    wrefresh(wnds->wnd);
    return *wnds;
}

void printFileList(WINDOWS *wnds)
{
    struct fileListNode *p = wnds->list.root;
    while(p!=NULL)
    {
        wprintw(wnds->subwnd, "%c%s\n", (p->type == 4)?'/':' ', p->name);
        p = p->next;
    }
    wrefresh(wnds->subwnd);
}

void sig_winch(int signo)
{
    struct winsize size;
    signo = signo;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    resizewnds(&wnds[0], 2, 0);
    resizewnds(&wnds[1], 2, 1);
}

#endif /* _WINDOWS_C_ */
