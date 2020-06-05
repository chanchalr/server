#include "server.h"
#include "utils.h"
int main(int argc, char **argv) {

    int portnum = 0,sockfd;
    int epollfd = -1;
    pthread_t *threads;
    struct epoll_event accept_event = {0};

    if (argc < 2) {
        printf("usage ./server <portnum>\n");
        exit(-1);
    }
    
    portnum = atoi(argv[1]);
    sockfd = list_inet_socket(portnum);
    set_nonblocking(sockfd);
    epollfd = epoll_create1(0);
    if( epollfd == -1 ) {
        perror_die("Failed to create epollfd");
    }
    accept_event.data.fd = sockfd;
    accept_event.events = EPOLLIN;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&accept_event)) {
        perror_die("Failed to add epoll ");
    }

    while(1) {

    }
    

}
