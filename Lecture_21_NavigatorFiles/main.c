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

struct fileListNode
{
    char name[255];
    unsigned char type;
    struct fileListNode *next;
};

struct fileList
{
    struct fileListNode *root;
    struct fileListNode *prev;
    int count;
};

struct windows
{
    WINDOW * wnd;
    WINDOW * subwnd;
    char path[PATH_MAX+1];
    struct fileList list;
};

typedef struct windows WINDOWS;

WINDOWS wnds[2];

void addNewItem(struct fileList *list, char *buf, unsigned char type)
{
    struct fileListNode *newNode;
    newNode = malloc(sizeof(struct fileListNode));
    strcpy(newNode->name, buf);
    newNode->type = type;
    newNode->next = NULL;
    if(list->root == NULL)
    {
        list->root = newNode;
        list->prev = newNode;
    }
    else
    {
        list->prev->next = newNode;
        list->prev = newNode;
    }
    list->count++;
}

void clearFileList(struct fileList *list)
{
    struct fileListNode *p = list->root;
    struct fileListNode *n;
    while(p!=NULL)
    {
        n = p->next;
        free(p);
        p = n;
    }
}

void getFileList(WINDOWS *wnds);
void printFileList(WINDOWS *wnds);

WINDOWS createWindow(int count, int number)
{
    struct winsize size;
    ssize_t len;
    WINDOWS windows;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    windows.wnd = newwin(size.ws_row, size.ws_col/count, 0, size.ws_col/count * number);
    box(windows.wnd, '|', '-');
    windows.subwnd = derwin(windows.wnd, size.ws_row-2, size.ws_col/count-2, 1, 1);
    wrefresh(windows.wnd);
    len = readlink("/proc/self/exe", windows.path, PATH_MAX);
    windows.path[len] = 0;
    char* p = strrchr(windows.path, '/');
    if(p) *(p + 1) = 0;
    else windows.path[0] = 0;
    windows.list.root = NULL;
    windows.list.prev = NULL;
    windows.list.count = 0;
    getFileList(&windows);
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

void getFileList(WINDOWS *wnds)
{
    clearFileList(&(wnds->list));
    DIR *d;
    struct dirent *dir;
    d = opendir(wnds->path);
    if (d) {
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".")==0)
                continue;
            addNewItem(&(wnds->list), dir->d_name, dir->d_type);
        }
        closedir(d);
    }
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
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    resizewnds(&wnds[0], 2, 0);
    resizewnds(&wnds[1], 2, 1);
}

int main(int argc, char ** argv)
{
    WINDOW * wnd;
    WINDOW * subwnd;
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
