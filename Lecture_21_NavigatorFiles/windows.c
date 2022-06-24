#ifndef _WINDOWS_C_
#define _WINDOWS_C_

#include "windows.h"


void openDirectory(WINDOWS *wnds, const char *name)
{
    int len;
    int lenOfName;
    int idx;
    char *p;
    len = strlen(wnds->path);
    if(strcmp("..", name) == 0)
    {
        if(len > 1)
        {
            wnds->path[len-1] = 0;
            p = strrchr(wnds->path, '/');
            if(p) *(p + 1) = 0;
        }
    }
    else
    {
        idx = len;
        lenOfName = strlen(name);
        for(; idx < len + lenOfName; idx++)
        {
            wnds->path[idx] = name[idx - len];
        }
        wnds->path[idx] = '/';
        wnds->path[idx+1] = 0;
    }
}

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
    windows.position = 0;
    windows.page = 0;
    windows.pageSize = size.ws_row - 2;
    windows.list.root = NULL;
    windows.list.prev = NULL;
    windows.list.count = 0;
    windows.rowWidth = size.ws_col/count - 2;
    windows.rowStart = size.ws_col/count * number + 1;
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
    wnds->rowWidth = size.ws_col/count - 2;
    wnds->rowStart = size.ws_col/count * number + 1;
    wnds->pageSize = size.ws_row - 2;
    wnds->page = wnds->position / wnds->pageSize;
    printFileList(wnds);
    wrefresh(wnds->wnd);
    return *wnds;
}

void printFileList(WINDOWS *wnds)
{
    int idx, i;
    struct stat statBuf;
    int filesize;
    char path[PATH_MAX + 1];
    int len, lenOfName;
    int start;
    struct fileListNode *p = wnds->list.root;
    wmove(wnds->subwnd, 0, 0);
    idx = 0;
    start = wnds->page * wnds->pageSize;
    while(p!=NULL)
    {
        if(idx < start)
        {
            p = p->next;
            idx++;
            continue;
        }
        if(idx >= start + wnds->pageSize)
            break;
        if(wnds->position == idx)
            wattron(wnds->subwnd, A_REVERSE);
        wprintw(wnds->subwnd, "%c%s", (p->type == 4)?'/':' ', p->name);
        if(p->type == 8)
        {
            strcpy(path, wnds->path);
            len = strlen(path);
            i = len;
            lenOfName = strlen(p->name);
            for(; i < len + lenOfName; i++)
            {
                path[i] = p->name[i - len];
            }
            path[i] = 0;    
            stat(path, &statBuf);
            filesize = statBuf.st_size;
            wprintw(wnds->subwnd, "\t(%d)\n", filesize);
        }
        else
            wprintw(wnds->subwnd, "\n");
        if(wnds->position == idx)
            wattroff(wnds->subwnd, A_REVERSE);
        p = p->next;
        idx++;
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
    nodelay(stdscr, 1);
    while (wgetch(stdscr) != ERR);
    nodelay(stdscr, 0);
}

#endif /* _WINDOWS_C_ */
