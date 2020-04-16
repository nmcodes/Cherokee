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
#include "./config/config.h"
#include "./custom/custom.h"

static volatile int skt;

void sigint_handler(__attribute__((unused)) int i) {
    close(skt);
}

int main(void){
    struct sockaddr_in server;
<<<<<<< HEAD
    int nb_workers = 1;
    pid_t *pids = malloc(nb_workers * sizeof(pid_t));
=======
    // int nb_workers = 4;
    // pid_t *pids = malloc(nb_workers * sizeof(pid_t));
    c_config *config;
>>>>>>> edabd87ad8d559e490c70bd4306b9dcf9178e58f

    config = new_config();
    log_set_fp(fopen("access.log", "a+"));
    log_set_level(0);

    config->router = get_custom_router(config);

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
    server.sin_port = htons(config->port);

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

<<<<<<< HEAD
    int i;
    for (i = 0; i < nb_workers; i++) {
        waitpid(pids[i], NULL, 0);
    }

    free(pids);
=======
    // int i;
    // for (i = 0; i < nb_workers; i++) {
    //     waitpid(pids[i], NULL, 0);
    // }
>>>>>>> edabd87ad8d559e490c70bd4306b9dcf9178e58f
    log_info("Closing Cherokee");
}
