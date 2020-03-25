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

#include "../log/log.h"
#include "../parser/parser.h"
#include "worker.h"


void worker(int skt)
{
    int client_skt;
    char buf[1024];
    c_request *req;
    c_config *config;

    log_info("Worker successfuly started.");
    config = new_config();

    while(1) {
        log_info("Worker ready to accept connection");
        client_skt = accept(skt, NULL, NULL);
        log_info("New client connection accepted");
        if (client_skt < 0) {
            perror("accept failed");
            log_error("Failed to accept connection");
            exit(1);
        }

        memset(buf, '\0', 1024);
        int read = recv(client_skt, buf, 1024, 0);
        if (read < 0) {
            log_error("Unable to read data");
            perror("Client read failed\n");
        }

        req = parse(strdup(buf));

        resolve_http_decision_diagram(config, req);
        int res_len = build_response(req->response);

        int err = send(client_skt, req->response->raw, res_len, 0);
        if (err < 0) {
            perror("Client write failed\n");
        }

        if (req->body != NULL) {
            log_info("HTTP/%d.%d %s %s (%d) Sent %d bytes (%d)", req->version.major, req->version.minor, methodToStr(req->method), req->url, strlen(req->body), req->response->status.code);
        } else {
            log_info("HTTP/%d.%d %s %s (%d)", req->version.major, req->version.minor, methodToStr(req->method), req->url, req->response->status.code);
        }

        free_request(req);
        close(client_skt);
    }

    log_error("Worker exiting");
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

    log_info("Spawning %d workers", nb_workers);

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
