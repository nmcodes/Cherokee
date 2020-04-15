/*
** is_method.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./httpdd.h"

int has_method_implemented(c_config *config, c_request *req) {
    c_router *r;

    if (req->url == NULL)
        return HTTPDD_FALSE;

    r = get_router_from_url(config, req->url);
    if (r == NULL)
        return HTTPDD_FALSE;

    int implemented = 0;
    switch (req->method) {
        case GET:
            implemented = r->has_get;
            break;
        case POST:
            implemented = r->has_post;
            break;
        case PUT:
            implemented = r->has_put;
            break;
        case DELETE:
            implemented = r->has_delete;
            break;
    }

    if (implemented) {
        return HTTPDD_TRUE;
    }
    return HTTPDD_FALSE;
}
