/*
** is_static_directory.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/
#include <sys/stat.h>

#include "./httpdd.h"
#include "../../log/log.h"

int is_static_directory(c_config *config, c_request *req) {
    char *dir_path;
    struct stat sb;
    int dir_exist;
    config = config;

    if (req->url == NULL) {
        return HTTPDD_FALSE;
    }

    if (strlen(req->url) == 0) {
        return HTTPDD_FALSE;
    }

    dir_path = get_file_path(config->root_path, req->url);
    dir_exist = stat(dir_path, &sb);
    free(dir_path);

    if (dir_exist == 0 && S_ISDIR(sb.st_mode)) {
        log_debug("IS STATIC DIR YES");
        return HTTPDD_TRUE;
    } else {
        return HTTPDD_FALSE;
    }
}
