#include "server.h"
#include "utils.h"

void perror_die(char *msg) {
    perror(msg);
    exit(-1);
}

int list_inet_socket(int portnum) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    struct sockaddr_in server_addr;
    if( sockfd < 1 ) {
        perror_die("Couldnt allocate socket\n");
    }

    if( setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,&sizeof(opt)) ) {
        perror_die("Couldnt set socket option\n");
    }

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portnum);

    if( bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) ) {
        perror_die("Couldnt bind to port %d\n",portnum);
    }

    if( listen(sockfd,N_BACKLOG) ){
        perror_die("Couldnt listen on port %d\n",portnum);
    }
    return sockfd;
}

void set_nonblocking(int sockfd ) {
    int flags = 0;
    flags = fcntl(sockfd,F_GETFLi,0);
    if( flags == -1 ) {
        perror_die("Failed to get flags from socket");
    }
    flags = fcntl(sockfd,F_SETFL,flags|O_NOBLOCKING);
    if( flags == -1 ) {
        perror_die("couldnt set nonblocking call\n");
    }

}
