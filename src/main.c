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
#include "./worker/worker.h"


int main(void){
    int nb_workers = 4;
    pid_t *pids = malloc(nb_workers * sizeof(pid_t));

    printf("I'm the master, my PID is %d\n", (int) getpid());
    printf("Starting spawning %d workers\n", nb_workers);

    spawn_multiple_workers(nb_workers, pids);

    printf("Master done spawning workers\n");

    int i;
    for (i = 0; i < nb_workers; i++) {
        waitpid(pids[i], NULL, 0);
    }
    printf("Master finished.\n");
}
