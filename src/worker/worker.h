/*
** worker.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/


#ifndef __WORKER_H__
#define __WORKER_H__

#include <unistd.h>
#include "../utils/process.h"

pid_t spawn_worker();
void spawn_multiple_workers(int nb_workers, pid_t *pids);

#endif
