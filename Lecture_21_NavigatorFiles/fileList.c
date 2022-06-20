#ifndef _FILE_LIST_C_
#define _FILE_LIST_C_

#include "fileList.h"

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

void getFileList(struct fileList *list, const char *path)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    clearFileList(list);
    if (d) {
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".")==0)
                continue;
            addNewItem(list, dir->d_name, dir->d_type);
        }
        closedir(d);
    }
}

#endif /* _FILE_LIST_C_ */
