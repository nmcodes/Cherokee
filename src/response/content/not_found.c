/*
** not_found.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "content.h"

int not_found(__attribute__((unused)) c_config *config, c_request *req) {
    req->response->body->content = "Not found";
    req->response->body->is_binary = 0;

    Http_Status s;
    s.code = 404;
    s.hint = "Not found";
    req->response->status = s;
    return HTTPDD_END;
}
