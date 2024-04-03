#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define WRONG "Wrong number of arguments\n"
#define FATAL "Fatal error\n"
#define BUF   200000
#define PORT  65000

int maxfd, id , sockfd = 0;
int arr[PORT];
int buff[BUF + 100];
fd_set aset, wset, rset;

void    fatal( char * error)
{
    if (sockfd > 2)
        close(sockfd);
    write(2, error, strlen(error));
    exit(1);
}

void    send_all(int connfd)
{
    for(int fd = 2; fd <= maxfd; fd++)
    {
        if(fd != connfd && FD_ISSET(fd, &wset))
            if (send(fd, buff, strlen(buff), 0) < 0)
                fatal(FATAL);
    }
}