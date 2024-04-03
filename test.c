#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define WRONG "Wrong number of arguments\n"
#define FATAL "Fatal error\n"
#define BUF 200000
#define PORT 65000

int maxfd, id, sockfd = 0;
int buff[BUF + 100];
int arr[PORT];
fd_set aset, rset, wset;

void    fatal(char * error)
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
        {
            if(send(fd, buff, strlen(buff), 0) < 0)
                fatal(FATAL);
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        fatal(WRONG);
    int connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
		fatal(FATAL);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1])); 
  
	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		fatal(FATAL);
	} 
	if (listen(sockfd, 10) != 0) {
		fatal(FATAL); 
	}
    len = sizeof(cli);
    id = 0;
    maxfd = sockfd;
    FD_ZERO(&aset);
    FD_SET(sockfd, &aset);
}