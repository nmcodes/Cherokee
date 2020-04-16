/*
** custom.h for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#ifndef __CUSTOM_H__
#define __CUSTOM_H__

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "../config/config.h"

typedef struct cherokee_config c_config;
typedef struct cherokee_response c_response;

typedef struct                      cherokee_router {
    char                            *path;
    int                             has_get;
    int                             has_post;
    int                             has_put;
    int                             has_delete;
    struct cherokee_router          *next;
}                                   c_router;

void log_router(c_router *r);
c_router *get_custom_router(c_config *config);
void call_python_module(c_response *res, char *folder, char *method);
c_router *get_router_from_url(c_config *config, char *url);

#endif
