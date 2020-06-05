#ifndef __SERVER__H
#define __SERVER__H
#include<stdio.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<stdint.h>
#include<stdlib.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include<fcntl.h>
#include<pthread.h>
#define N_BACKLOG 64
#define LIST_ADD(data,list) \
        tmp__ = (list_t *)malloc(sizeof(list_t));\
        tmp__->next = list;\
        list->prev->next = tmp__;\
        list->prev=tmp__;\
        list = tmp;

typedef enum { INITIAL_ACK, WAIT_FOR_MSG, IN_MSG } processing_state;

typedef struct fd_state__ {
    processing_state state;
    char sendbuf[SEND_BUF_SIZE];
    int sendbuf_ptr;
    int sendbuf_end;
}fd_state_t;

typedef struct request__ {
    int fd;
    char inputbuffer[4096];
    fd_state_t fdstate;
}request_t;

typedef struct list__ {
    void *data;
    struct list__ *next;
    struct list__ *prev;
}list_t;

list_t *tmp__;

typedef struct queue__ {
    pthread_mutex_t qmutex;
    pthread_cond_t cond_t;
    list_t *list_head;
    uint64_t max_qlen;
    uint64_t current_count;
}queue_t;
