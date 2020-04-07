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
#include "./log/log.h"

static volatile int skt;

void sigint_handler(__attribute__((unused)) int dummy) {
    close(skt);
}

int main(void){
    struct sockaddr_in server;
    // int nb_workers = 4;
    // pid_t *pids = malloc(nb_workers * sizeof(pid_t));
    c_config *config;

    config = new_config();
    log_set_fp(fopen("access.log", "a+"));
    log_set_level(0);

    signal(SIGINT, sigint_handler);
    log_info("Starting Cherokee");

    // Creating the socket
    skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt == -1)
    {
        close(skt);
        log_error("socket creation");
        exit(-1);
    }
    int reuse = 1;
    if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0) {
        log_error("setsockopt(SO_REUSEADDR) failed");
        exit(-1);
    }

    if (setsockopt(skt, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0)  {
        log_error("setsockopt(SO_REUSEPORT) failed");
        exit(-1);
    }


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
    listen(skt, config->backlog);
    worker(skt, config);
    // spawn_multiple_workers(pids, skt, config);

    // int i;
    // for (i = 0; i < nb_workers; i++) {
    //     waitpid(pids[i], NULL, 0);
    // }
    log_info("Closing Cherokee");
}
