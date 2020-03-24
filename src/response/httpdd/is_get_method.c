/*
** is_get_method.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./httpdd.h"

int is_get_method(c_config *config, c_request *req) {
    config = config;

    if (req->method == GET)
        return HTTPDD_TRUE;
    return HTTPDD_FALSE;
}
