/*
** main.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>

#include "./worker/worker.h"
#include "./parser/parser.h"

static volatile int skt;

void sigint_handler(int dummy) {
    printf("dummy : %d\n", dummy);

    close(skt);
}

int main(void){
    struct sockaddr_in server;
    int nb_workers = 4;
    pid_t *pids = malloc(nb_workers * sizeof(pid_t));

    printf("I'm the master, my PID is %d\n", (int) getpid());

    signal(SIGINT, sigint_handler);

    // Creating the socket
    skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt == -1)
    {
        close(skt);
        perror("socket creation");
        exit(-1);
    }
    printf("Socket created in master process: %d\n", skt);

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8000);

    //Bind
    if(bind(skt, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed");
        close(skt);
        exit(-1);
    }

    // start listening on socket
    listen(skt, 3);

    printf("Starting spawning %d workers\n", nb_workers);

    spawn_multiple_workers(nb_workers, pids, skt);

    printf("Master done spawning workers\n");

    int i;
    for (i = 0; i < nb_workers; i++) {
        waitpid(pids[i], NULL, 0);
    }
    printf("Master finished.\n");
}
