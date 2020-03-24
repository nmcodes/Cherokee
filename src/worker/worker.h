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
#include "../config/config.h"
#include "../response/httpdd/httpdd.h"

pid_t spawn_worker(int skt);
void spawn_multiple_workers(int nb_workers, pid_t *pids, int skt);

#endif
