#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    struct stat statBuf;
    char ch;
    int filesize;
    fd = open("./file.txt", O_CREAT | O_WRONLY);
    write(fd, "my file content", 15);
    close(fd);
    fd = open("./file.txt", O_RDONLY);
    stat("./file.txt", &statBuf);
    filesize = statBuf.st_size;
    lseek(fd, filesize+1, SEEK_SET);
    while(filesize > 0)
    {
        lseek(fd, -2, SEEK_CUR);
        read(fd, &ch, 1);
        printf("%c", ch);
        filesize --;
    }
    close(fd);
    return 0;
}
