#ifndef __UTILS__H
#define __UTILS__H
#include "server.h"
int listen_inet_socket( int portnum );
void set_nonblocking( int sockfd );
void perror_die(char *msg);
static inline int queue_push(queue_t *q,void *data);
static inline void * queue_pop(queue_t *q);
