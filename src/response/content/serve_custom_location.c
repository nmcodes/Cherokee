/*
** serve_custom_location.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../log/log.h"
#include "../../utils/method.h"
#include "content.h"

int serve_custom_location(c_config *config, c_request *req) {
    char *file, *method;
    c_router *r;

    r = get_router_from_url(config, req->url);

    file = malloc(strlen(config->customdir) + strlen(r->path));
    log_debug("custom dir : %s", config->customdir);
    log_debug("path : %s", r->path);

    strcpy(file, config->customdir);
    strcat(file, r->path);

    log_debug("file path : %s", file);

    switch(req->method) {
        case GET:
            method = "get";
            break;
        case POST:
            method = "post";
            break;
        case PUT:
            method = "put";
            break;
        case DELETE:
            method = "delete";
            break;
        case OPTIONS:
        case HEAD:
        case NONE:
            method = NULL;
    }
    if (method == NULL) {
        return HTTPDD_END;
    }
    log_debug("method : %s", method);

    call_python_module(req->response, file, method);

    req->response->status = STATUS_200_OK;
    return HTTPDD_END;
}
