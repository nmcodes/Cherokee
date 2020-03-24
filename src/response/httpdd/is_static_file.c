/*
** is_static_file.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "./httpdd.h"

int is_static_file(c_config *config, c_request *req) {
    char *file_path;
    int file_exist;
    config = config;

    if (req->url == NULL) {
        return HTTPDD_FALSE;
    }

    if (strlen(req->url) == 0) {
        return HTTPDD_FALSE;
    }


    file_path = get_file_path(config->root_path, req->url);
    file_exist = access(file_path, F_OK);
    free(file_path);

    if(file_exist != -1) {
        return HTTPDD_TRUE;
    } else {
        return HTTPDD_FALSE;
    }
}
