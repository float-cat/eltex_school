#ifndef _NAVIGATOR_C_
#define _NAVIGATOR_C_

#include "navigator.h"

WINDOWS wnds[2];

void process(void)
{
    char ch;
    int wndidx;
    wndidx = 0;
    while((ch = getch()) != 113)
    {
        if(ch == 115 || ch == 66)
        {
            wmove(wnds[wndidx].subwnd, 0, 0);
            wnds[wndidx].position++;
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 119 || ch == 65)
        {
            wmove(wnds[wndidx].subwnd, 0, 0);
            wnds[wndidx].position--;
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 10)
        {
            struct fileListNode *p;
            p = getItem(&(wnds[wndidx].list), wnds[wndidx].position);
            if(p->type == 4)
            {
                openDirectory(&(wnds[wndidx]), p->name);
                getFileList(&(wnds[wndidx].list), wnds[wndidx].path);
                printFileList(&(wnds[wndidx]));
            }
        }
        else if(ch == 9)
        {
            wndidx = (wndidx + 1) % 2;
        }
        printf("[%d]", ch);
    }
}

void init(void)
{
    initscr();
    noecho();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0);
    refresh();
    wnds[0] = createWindow(2, 0);
    wnds[1] = createWindow(2, 1);
    printFileList(&(wnds[0]));
    printFileList(&(wnds[1]));
    process();
    delwin(wnds[0].subwnd);
    delwin(wnds[0].wnd);
    delwin(wnds[1].subwnd);
    delwin(wnds[1].wnd);
    endwin();
}

#endif /* _NAVIGATOR_C_ */
