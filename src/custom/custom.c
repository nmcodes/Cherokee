/*
** custom.c for Cherokee
**
** Made by BOURDALE Jules
** Login   <bourda_j@etna-alternance.net>
**
*/

#include "custom.h"
#include "../log/log.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

c_router *new_router() {
    c_router *router;

    router = malloc(sizeof(c_router));
    router->path = NULL;
    router->has_get = 0;
    router->has_post = 0;
    router->has_put = 0;
    router->has_delete = 0;
    router->next = NULL;
    return router;
}

void listdir(const char *name, int depth, c_router *r)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

            if (depth == 1) {
                if (r->path == NULL) {
                    r->path = malloc(strlen(entry->d_name) + 2);
                    sprintf(r->path, "/%s", entry->d_name);
                    listdir(path, depth + 1, r);
                } else {
                    r->next = new_router();
                    r->next->path = malloc(strlen(entry->d_name) + 2);
                    sprintf(r->next->path, "/%s", entry->d_name);
                    listdir(path, depth + 1, r->next);
                }
            }
        } else {
            if (r->path != NULL) {
                if (strcmp(entry->d_name, "get.py") == 0) {
                    r->has_get = 1;
                }
                if (strcmp(entry->d_name, "post.py") == 0) {
                    r->has_post = 1;
                }
                if (strcmp(entry->d_name, "put.py") == 0) {
                    r->has_put = 1;
                }
                if (strcmp(entry->d_name, "delete.py") == 0) {
                    r->has_delete = 1;
                }
            }
        }
    }
    closedir(dir);
}

void log_router(c_router *r) {
    c_router *i;

    if (r == NULL || r->path == NULL) {
        log_info("No custom router found");
        return ;
    }

    log_info("Custom router configuration : ");
    i = r;
    while (i != NULL) {
        char *log_r;
        log_r = malloc(strlen(r->path) + 26 ); // r->path (GET, POST, PUT, DELETE)
        strcpy(log_r, r->path);
        strcat(log_r, " (");
        if (!i->has_get && !i->has_post && !i->has_put && !i->has_delete) {
            strcat(log_r, "NONE");
        } else {
            if (i->has_get)
                strcat(log_r, "GET ");
            if (i->has_post)
                strcat(log_r, "POST ");
            if (i->has_put)
                strcat(log_r, "PUT ");
            if (i->has_delete)
                strcat(log_r, "DELETE");
        }
        if (log_r[strlen(log_r)-1] == ' ') {
            log_r[strlen(log_r)-1] = ')';
        } else {
            strcat(log_r, ")");
        }

        log_info("%s", log_r);
        i = i->next;
    }
}

c_router *get_router_from_url(c_config *config, char *url) {
    c_router *r;

    if (url == NULL)
        return NULL;

    r = config->router;
    while (r != NULL && r->path != NULL) {
        if (strcmp(url, r->path) == 0) {
            return r;
        }
        r = r->next;
    }
    return NULL;
}

c_router *get_custom_router(c_config *config) {
    c_router *r;
    r = new_router();

    listdir(config->customdir, 1, r);

    return r;
}
