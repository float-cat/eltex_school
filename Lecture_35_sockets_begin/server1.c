#include <sys/types.h>
#include <sys/socket.h>

int main(void)
{
    char buf[25];
    struct sockaddr_un serv, client;
    int fd, fdnew;
    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    serv.sun_family = AF_LOCAL;
    serv.sun_pa.th = "/tmp/connect";
    bind(fd, serv, sizeof(struct sockaddr_un));
    listen(fd, 5);
    fdnew = accept(fd, client, sizeof(struct sockaddr_un));
    recv(fdnew, buf, 4, 0);
    printf("%s\n", buf);
    strcopy(buf, "Hello!");
    send(fdnew, buf, 7, 0);
    close(fdnew);
    close(fd);
    return 0;
}
