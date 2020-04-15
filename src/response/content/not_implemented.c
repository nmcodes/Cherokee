/*
** not_implemented.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "content.h"

int not_implemented(__attribute__((unused)) c_config *config, c_request *req) {
    req->response->body->content = "Method Not Allowed";
    req->response->body->is_binary = 0;

    Http_Status s;
    s.code = 405;
    s.hint = "Method Not Allowed";
    req->response->status = s;
    return HTTPDD_END;
}
