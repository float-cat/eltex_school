#ifndef _CHAT_C_
#define _CHAT_C_

#include "chat.h"

WINDOWS wnds[3];
pthread_mutex_t mtx;

void print_message(char *buffer)
{
    pthread_mutex_lock(&mtx);
    wprintw(wnds[0].subwnd, "%s\n", buffer);
    wrefresh(wnds[0].subwnd);
    pthread_mutex_unlock(&mtx);
}
void print_int(int a)
{
    /* DBG */
    pthread_mutex_lock(&mtx);
    wprintw(wnds[0].subwnd, "%d\n", a);
    wrefresh(wnds[0].subwnd);
    pthread_mutex_unlock(&mtx);
}

void process(void)
{
    char buffer[MAX_CHAT_MESSAGE];
    int bufferidx;
    int ch;
    bufferidx = 0;
    buffer[bufferidx] = 0;
    wmove(wnds[2].subwnd, 0, 0);
    while((ch = wgetch(stdscr)) != 27)
    {
        if(ch == 92 || ch == 124 || ch == 47)
        {
            buffer[bufferidx] = 0;
            send_message(buffer);
            bufferidx = 0;
            buffer[0] = 0;
            pthread_mutex_lock(&mtx);
            wclear(wnds[2].subwnd);
            pthread_mutex_unlock(&mtx);
        }
        else
        {
    	    wprintw(wnds[2].subwnd, "%c", ch);
            buffer[bufferidx] = ch;
            bufferidx++;
            buffer[bufferidx] = 0;
        }
        pthread_mutex_lock(&mtx);
    	wrefresh(wnds[2].subwnd);
        pthread_mutex_unlock(&mtx);
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
    wnds[0] = createWindow(0);
    wnds[1] = createWindow(1);
    wnds[2] = createWindow(2);
    process();
    delwin(wnds[0].subwnd);
    delwin(wnds[0].wnd);
    delwin(wnds[1].subwnd);
    delwin(wnds[1].wnd);
    delwin(wnds[2].subwnd);
    delwin(wnds[2].wnd);
    endwin();
}

#endif /* _CHAT_C_ */
