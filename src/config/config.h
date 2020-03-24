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

typedef struct  cherokee_config {
    char        *root_path;
}               c_config;

c_config *new_config();

#endif
