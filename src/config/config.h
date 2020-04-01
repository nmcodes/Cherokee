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

typedef struct cherokee_config
{
    int port;
    const char* loglevel;
    const char* logfile;
    const char* rootpath; 
} c_config;

c_config *new_config();
int      test_config();


#endif
