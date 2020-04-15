/*
** serve_custom_location.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include "../../log/log.h"
#include "content.h"

int serve_custom_location(c_config *config, c_request *req) {



    req->response->status = STATUS_200_OK;
    return HTTPDD_END;
}
