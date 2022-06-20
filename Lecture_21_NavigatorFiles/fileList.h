#ifndef _FILE_LIST_H_
#define _FILE_LIST_H_

#include <malloc.h>
#include <string.h>
#include <dirent.h>

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

void addNewItem(struct fileList *list, char *buf, unsigned char type);

void clearFileList(struct fileList *list);

void getFileList(struct fileList *list, const char *path);

#endif /* _FILE_LIST_H_ */
