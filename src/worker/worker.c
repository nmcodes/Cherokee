/*
** worker.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "../parser/parser.h"
#include "worker.h"


void worker(int skt)
{
    int client_skt;
    char buf[1024];

    printf("I'm a worker! My PID is %d, my PPID is %d. I received skt : %d\n", (int) getpid(), (int) getppid(), skt);

    while(1) {
        printf("Worker (pid=%d) start accepting...\n", (int) getpid());
        client_skt = accept(skt, NULL, NULL);
        printf("Worker (pid=%d) accepted connection\n", (int) getpid());
        if (client_skt < 0) {
            perror("accept failed");
            printf("[ERROR] Worker (pid = %d) failed to accept connection", (int) getpid());
            continue;
        }

        memset(buf, '\0', 1024);
        int read = recv(client_skt, buf, 1024, 0);
        if (read < 0) {
            perror("Client read failed\n");
        }
        printf("Worker (pid=%d) read %d byte(s)\n", (int) getpid(), read);
        printf("GOT REQUEST:\n%s\n", buf);
        parse(strdup(buf));

        int err = send(client_skt, buf, read, 0);
        if (err < 0) {
            perror("Client write failed\n");
        }
        printf("Worker (pid=%d) echoed back %d byte(s)\n", (int) getpid(), read);
        close(client_skt);
    }

    printf("Worker (pid=%d) exiting...\n", (int)getpid());
    exit(0);
}

pid_t spawn_worker(int skt)
{
    pid_t pid = create_process();

    if (pid == -1)
    {
        perror("fork");
        return -1;
    } else if (pid == 0)
    {
        worker(skt);
    }

    return pid;
}

void spawn_multiple_workers(int nb_workers, pid_t *pids, int skt) {
    int i;
    pid_t pid;

    for (i = 0; i < nb_workers; i++)
    {
        pid = spawn_worker(skt);
        if (pid == 0) {
            break;
        } else {
            pids[i] = pid;
        }
    }
}
