/*
** process.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

pid_t create_process(void)
{
    pid_t pid;

    pid = fork();
    while ((pid == -1) && (errno == EAGAIN))
    {
        pid = fork();
    }
    return pid;
}
