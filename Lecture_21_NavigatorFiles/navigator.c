#ifndef _NAVIGATOR_C_
#define _NAVIGATOR_C_

#include "navigator.h"

WINDOWS wnds[2];

void process(void)
{
    int ch;
    int wndidx;
    int newPosition;
    int oldY;
    MEVENT event;
    wndidx = 0;
    oldY = 100000;
    while((ch = wgetch(stdscr)) != 113)
    {
        if(ch == 115 || ch == 258)
        {
            if(wnds[wndidx].list.count - 1 > wnds[wndidx].position)
                wnds[wndidx].position++;
            if((wnds[wndidx].page+1) * wnds[wndidx].pageSize <= wnds[wndidx].position)
            {
                wclear(wnds[wndidx].subwnd);
                wnds[wndidx].page++;
            }
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 119 || ch == 259)
        {
            if(wnds[wndidx].position > 0)
                wnds[wndidx].position--;
            if(wnds[wndidx].page * wnds[wndidx].pageSize > wnds[wndidx].position)
            {
                wclear(wnds[wndidx].subwnd);
                wnds[wndidx].page--;
            }
            printFileList(&(wnds[wndidx]));
        }
        else if(ch == 10)
        {
            struct fileListNode *p;
            p = getItem(&(wnds[wndidx].list), wnds[wndidx].position);
            if(p->type == 4)
            {
                wclear(wnds[wndidx].subwnd);
                openDirectory(&(wnds[wndidx]), p->name);
                getFileList(&(wnds[wndidx].list), wnds[wndidx].path);
                wnds[wndidx].position = 0;
                printFileList(&(wnds[wndidx]));
            }
        }
        else if(ch == 9)
        {
            wndidx = (wndidx + 1) % 2;
        }
        else if(ch == KEY_MOUSE)
        {
            getmouse(&event);
            move(event.y, event.x);
            if(event.x > wnds[0].rowStart + wnds[0].rowWidth)
                wndidx = 1;
            else
                wndidx = 0;
            newPosition = wnds[wndidx].page * wnds[wndidx].pageSize + event.y - 1;
            if(newPosition >= 0 && newPosition < wnds[wndidx].list.count)
            {
                struct fileListNode *p;
                wnds[wndidx].position = newPosition;
                if(event.y == oldY)
                {
                    p = getItem(&(wnds[wndidx].list), wnds[wndidx].position);
                    if(p->type == 4)
                    {
                        wclear(wnds[wndidx].subwnd);
                        openDirectory(&(wnds[wndidx]), p->name);
                        getFileList(&(wnds[wndidx].list), wnds[wndidx].path);
                        wnds[wndidx].position = 0;
                        printFileList(&(wnds[wndidx]));
                    }
                }
                else                    
                    printFileList(&(wnds[wndidx]));
                oldY = event.y;
            }
        }
    }
}

void init(void)
{
    initscr();
    noecho();
    signal(SIGWINCH, sig_winch);
    cbreak();
    keypad(stdscr, 1); /* DBG */
    mousemask(BUTTON1_CLICKED, NULL); /* DBG */
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
