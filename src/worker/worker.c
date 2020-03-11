/*
** worker.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"


void worker(void)
{
    printf("I'm a worker! My PID is %d, my PPID is %d\n", (int) getpid(), (int) getppid());
    printf("Worker (pid=%d) sleep for 5 sec...\n", (int) getpid());

    sleep(5);

    printf("Worker (pid=%d) exiting...\n", (int)getpid());
    exit(0);
}

pid_t spawn_worker()
{
    pid_t pid = create_process();

    if (pid == -1)
    {
        perror("fork");
        return -1;
    } else if (pid == 0)
    {
        worker();
    }

    return pid;
}

void spawn_multiple_workers(int nb_workers, pid_t *pids) {
    int i;
    pid_t pid;

    for (i = 0; i < nb_workers; i++)
    {
        pid = spawn_worker();
        if (pid == 0) {
            break;
        } else {
            pids[i] = pid;
        }
    }
}
