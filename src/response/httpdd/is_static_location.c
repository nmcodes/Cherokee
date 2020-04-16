/*
** is_static_location.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./httpdd.h"
#include "../../log/log.h"

int is_static_location(c_config *config, c_request *req) {
    c_router *r;

    if (req->url == NULL) {
        return HTTPDD_TRUE;
    }

    r = get_router_from_url(config, req->url);
    if (r != NULL) {
        return HTTPDD_FALSE;
    }
    return HTTPDD_TRUE;
}
