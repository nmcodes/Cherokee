/*
** config.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../custom/custom.h"

typedef struct cherokee_router c_router;

typedef struct cherokee_config
{
    int     port;
    char*   loglevel;
    char*   logfile;
    char*   root_path;
    int     workers;
    int     headermaxsize;
    int     backlog;
    char    *customdir;
    c_router *router;
} c_config;

c_config *new_config();
int      test_config();
void     default_config(c_config* pconfig);


#endif
